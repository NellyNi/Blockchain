#include <iostream>
#include <string>

#include "transaction.h"
using namespace std;

int main(){
  int p=0;
  string k;
  Transaction user;
  while (p==0){
    cout<<"Welcome to the transaction-chain application..."<<endl;
    cout<<"1) Add a transaction to the chain."<<endl;
    cout<<"2) Find a transaction with name of receiver or sender."<<endl;
    cout<<"3) Verify and print the chain."<<endl;
    cout<<"Which operation do you want to make? (1,2,3):"<<endl;
    int operation;
    cin>>operation;
    int flag=1;
    while (flag==1){
      if (operation==1){
        cout<<"Please input amount, name of the sender and the receiver:"<<endl;
        int a;
        string s;
        string r;
        cout<<"Amount: ";
        cin>>a;
        flag=0;
        int tIn=0;
        while (tIn==0){
          if(cin.fail()){
            cerr<<"Error! Please input an integer amount:"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"Amount: ";
            cin>>a;

          } else {
            tIn=1;
          }
        }
      
        cout<<"Sender: ";
        cin>>s;
        cout<<"Receiver: ";
        cin>>r;
        cout<<endl;
        user.addTrans(a,s,r);
        
      } else if (operation==2){
        cout<<"Please input the name of a sender:"<<endl;
        string s;
        cin>>s;
        cout<<endl;
        flag=0;
        user.find(s);
        
      } else if (operation==3){
        flag=0;
        cout<<user.checkchain()<<endl;
        
      }else{
        cout<<"wrong operation!";
        cout<<"Which operation do you want to make? (1,2,3):"<<endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin>>operation;
      }	
    }
    cout<<"Do you want to keep doing? y/n"<<endl;
    bool yn=false;
    while (!yn){
      cin>>k;
      if (k=="y"){
        p=0;
        yn=true;
      } else if (k=="n"){
        p=1;
        yn=true;
      } else {
        cout<<"Error! y/n"<<endl;
        cout<<"Please enter again:"<<endl;
      }
    }
  }
  cout<<"Thank you!"<<endl;
  return 0;
}
