#include "transaction.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "openssl/sha.h"
using namespace std;
Transaction::Transaction(){
    head=0;
    last=0;
}

Transaction::~Transaction(){
    Transaction* n=head;
    Transaction *temp;
    while ((n!=NULL)&&(n->previous!=0)){
        temp=n->previous;
        delete n;
        n=temp;
    }
    delete n;
}

void Transaction::gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
}

string Transaction::sha256(const string str)
{
    unsigned char h[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(h, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)h[i];
    }
    return ss.str();
}

void Transaction::addTrans(int am, string s, string r){
    if (last==0){
        last=new Transaction;
        last->amount=am;
        last->sender=s;
        last->receiver=r;
        last->hash="";
        cout<<"Add Block:"<<endl<<"Amount:"<<last->amount<<endl;
        cout<<"Sender:"<<last->sender<<endl;
        cout<<"Receiver:"<<last->receiver<<endl;
        int flag=0;
        while (flag==0){
            char *last_n = new char[31]; 
            gen_random(last_n, 30);
            last->nonce=last_n;
            string t = sha256(to_string(am)+s+r+last->nonce);
            if ((t[t.size()-1]=='0')||(t[t.size()-1]=='1')||(t[t.size()-1]=='2')||(t[t.size()-1]=='3')||(t[t.size()-1]=='4')){
                flag=1;
            }
        }
        cout<<"Nonce:"<<last->nonce<<endl;
        cout<<"Hash value: NULL"<<endl;
        last->previous=0;
        head=last;    
        

    } else {
        head->previous=new Transaction;
        int flag=0;
        string mdString,nstr;
        nstr=sha256(to_string(head->amount)+head->sender+head->receiver+head->nonce);
        head=head->previous;
        head->amount=am;
        head->sender=s;
        head->receiver=r;
        head->hash=nstr;
        cout<<"Amount:"<<head->amount<<endl;
        cout<<"Sender:"<<head->sender<<endl;
        cout<<"Receiver:"<<head->receiver<<endl;
        while (flag==0){
            char *head_n = new char[31]; 
            gen_random(head_n, 30);
            head->nonce=head_n;
            mdString = sha256(to_string(head->amount)+head->sender+head->receiver+head->nonce);
            if ((mdString[mdString.size()-1]=='0')||(mdString[mdString.size()-1]=='1')||(mdString[mdString.size()-1]=='2')||(mdString[mdString.size()-1]=='3')||(mdString[mdString.size()-1]=='4')){
                flag=1;    
            }
        }
        cout<<"Nonce:"<<head->nonce<<endl;       
        cout<<"Hash value:"<<head->hash<<endl;
        head->previous=0;
    }
}

void Transaction::find(string s){
    Transaction* n=last;

    while((n->previous!=0)&&(n->sender!=s)){
        n=n->previous;
    }
    if (n->sender==s){
        cout<<"Amount:"<<n->amount<<endl;
        cout<<"Sender:"<<n->sender<<endl;
        cout<<"Receiver:"<<n->receiver<<endl;
        cout<<"Nonce:"<<n->nonce<<endl;
        cout<<"Hash:"<<n->hash<<endl;
    } else{
        cout<<"Not exist!"<<endl;
    }
}

string Transaction::checkchain(){

    Transaction* n = last;
    
    if (n->previous==0){
        cout<<"Block"<<1<<endl;
        cout<<"Amount:"<<n->amount<<endl;
        cout<<"Sender:"<<n->sender<<endl;
        cout<<"Receiver:"<<n->receiver<<endl;
        cout<<"Nonce:"<<n->nonce<<endl;
        cout<<"Hash: NULL"<<endl<<endl;
        return "true";
    }
    
    while ((n->previous!=0)){
        string mdString= sha256(to_string(n->amount)+n->sender+n->receiver+n->nonce);
        
        if (n->previous->hash!=mdString){
            cout<<"This block:"<<endl;
            cout<<"Amount:"<<n->amount<<endl;
            cout<<"Sender:"<<n->sender<<endl;
            cout<<"Receiver:"<<n->receiver<<endl;
            cout<<"Nonce:"<<n->nonce<<endl;
            cout<<"Hash:"<<n->hash<<endl;
            cout<<"Previous block:"<<endl;
            cout<<"Amount:"<<n->previous->amount<<endl;
            cout<<"Sender:"<<n->previous->sender<<endl;
            cout<<"Receiver:"<<n->previous->receiver<<endl;
            cout<<"Nonce:"<<n->previous->nonce<<endl;
            cout<<"Hash:"<<n->previous->hash<<endl;
            return "false";
        }
        n=n->previous;
    }
    Transaction* p = last;
    int i(1);
    cout<<"Print chain:"<<endl;
    while((p!=0)){
        cout<<"Block"<<i<<endl;
        cout<<"Amount:"<<p->amount<<endl;
        cout<<"Sender:"<<p->sender<<endl;
        cout<<"Receiver:"<<p->receiver<<endl;
        cout<<"Nonce:"<<p->nonce<<endl;
        cout<<"Hash:"<<p->hash<<endl<<endl;
        i++;
        p=p->previous;
    }
    return "true";
}

