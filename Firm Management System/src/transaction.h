#ifndef TRANSACTIONS_HPP
#define TRANSACTIONS_HPP

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ----------------------------------------------------------------------------
// Transaction ADT: Holds possible transactions a Client can use
//
// Imlementation and Assumptions:
//   -- This class has bad design, but due to the limitation of this lab
//      (cannot use inheritance) we are forced to make extra data members
//   -- firstClientID is used for all commands
//    - In the cases of 'Deposit' or "Withdraw' commands, it acts as a simple
//      default account number
//    - It is made this way to accomodate the 'Move' command, which requires a
//      second client ID
// ----------------------------------------------------------------------------
class Client;
class Transaction {
public:
   Transaction(char = '\0', int = 0, int = 0);     // default constructor
   ~Transaction();                                 // destructor
   
   // set the data of transaction object
   bool setData(ifstream&);
   // in case of 'M', move amount from one client to another
   void move(Client*, Client*);
   
   // getter functions
   char getCommand();
   int getAmount();
   int getFirstAccount();         // get first account number
   int getSecondAccount();        // get second account number (if necessary)
   Client* getFirstClient();     // get first ClientID
   Client* getSecondClient();    // get second ClientID (if necessary)
   
private:
   char command;                // Could be 'D', 'W', 'M', or 'H'
   //int firstClientID;           // in case of 'D', 'W', or 'H'
   //int secondClientID;          // in case of 'M'
   Client* firstClient;
   Client* secondClient;
   
   int firstAccountNum;         // in case of 'M', 'D', 'W', 'H'
   int secondAccountNum;        // in case of 'M'
   
   int amount;         // Amount of money to deposit or withdraw in Client
};

#endif
