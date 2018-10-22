//transaction.h
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;
class Transaction{
 public:
  Transaction();
  ~Transaction();
  void gen_random(char *s, const int len);
  string sha256(const string str);
  void addTrans(int am, string s, string r);
  void find(string s);
  string checkchain();
 private:
  Transaction *previous;
  Transaction *head;
  Transaction *last;
  int amount;
  string sender;
  string receiver;
  string nonce;
  string hash;

};

#endif