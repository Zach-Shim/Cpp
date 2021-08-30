#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include queue.h
#include "account.h"
#include "transaction.h"
using namespace std;

// ----------------------------------------------------------------------------
// Client ADT: Client is a class that represents a specific client's accounts
//             within the firm.
//
// Imlementation and Assumptions:
//   -- The Client is represented by a four-digit numerical ID
//   -- Uses a vector to hold the history of transactions for current client
//   -- Uses an array to hold the ten accounts a Client owns
//   -- A client can either deposit or withdraw money from any account
//   -- The Client keeps track of a transaction history of all transactions
//      that concern it's accounts.
//   -- There are ten accounts in a given client:
//       0  - The money market
//       1  - The prime money market
//       2  - The long-term bond
//       3  - The short-term bond
//       4  - The 500 index fund
//       5  - The capital value fund
//       6  - The growth equity fund
//       7  - The growth index fund
//       8  - The value fund
//       9  - The value stock index
//   -- These accounts are specified by an additional digit following the
//      numeric ID of the Client.
//   -- Client allows no arguments during Object delcaration
// ----------------------------------------------------------------------------

const int MAXACCOUNTS = 10;

class Client {
public:
   Client();                      // construct the client
   ~Client();                     // destruct the client
   
   void makeEmpty();
   
   bool setData(ifstream&);
   bool setID(int);
   
   bool deposit(int, int);        // deposit money into an account
   bool withdraw(int, int);       // withdraw money from an account
   
   void updateHistory(Transaction*);  // add a new transaction to history
   void showHistory();            // print the transaction history of a client
   
   string getName();              // return the name of the client
   int getID();                   // return the client ID
   int getBaseValue(int);         // return the starting value of an account
   int getCurrentValue(int);      // return the current value of an account
   
   bool operator>(const Client&) const;      // overloaded operator >
   bool operator<(const Client&) const;      // overloaded operator <
   bool operator==(const Client&) const;     // overloaded operator ==
   bool operator!=(const Client&) const;     // overloaded operator !=
   
private:
   string firstName;           // first name
   string lastName;            // last name
   int clientID;               // four digit numeric ID
   
   Queue transactionHistory;  // holds the transaction history
   Account* accounts[MAXACCOUNTS];           // holds 10 different accounts
};

#endif
