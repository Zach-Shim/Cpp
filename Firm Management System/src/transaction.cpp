#include "transaction.h"
#include "client.h"
// ----------------------------------------------------------------------------
// default constructor
Transaction::Transaction(char request, int money, int firstAccountID) {
   // intended for creating a deposit object when there is a move command
   command = request;
   amount = money;
   firstAccountNum = firstAccountID;
   
   // initialize rest of variables to base value
   secondAccountNum = 0;
}

// ----------------------------------------------------------------------------
// destructor
Transaction::~Transaction() {}

// ----------------------------------------------------------------------------
// setData
// sets the data for a transaction object
//
// In the 'Move' command case:
// every data member is set to a value
//
// In 'Deposit' or 'Withdraw' command cases:
// command, firstClientID, firstAccountNum, secondAccountNum, and amount
// are all given values
//
//
bool Transaction::setData(ifstream& infile) {
   int firstClientID;
   int secondClientID;
   // read in command, clientID, and account number
   infile >> command;
   infile >> firstClientID;
   
   // in case of end of file, return
   if(infile.eof()) {
      return false;
   }
   
   // perform a transaction, defaults to error statement
   switch(command) {
      case 'D':
         // read client's clientID, account number to deposit in, and amount
         firstAccountNum = (firstClientID % 10);
         firstClientID /= 10;
         firstClient->setID(firstClientID);
         infile >> amount;
         break;
      case 'W':
         // read client's clientID, account number to withdraw from, and amount
         firstAccountNum = (firstClientID % 10);
         firstClientID /= 10;
         firstClient->setID(firstClientID);
         infile >> amount;
         break;
      case 'M':
         // read first client ID and amount to transfer
         firstAccountNum = (firstClientID % 10);
         firstClientID /= 10;
         firstClient->setID(firstClientID);
         infile >> amount;
         
         // read second client ID
         infile >> secondClientID;
         secondAccountNum = (secondClientID % 10);
         secondClient->setID(secondClientID);
         secondClientID /= 10;
         break;
      case 'H':
         break;
      default:
         // error is a unknown command is read from file
         string restOfLine;
         cout << "Unknown transaction type '" << command << "' requested" << endl;
         getline(infile, restOfLine);  // get rid of the rest of the line
         
         return false;
   }
   
   // error checking clientID's
   if(firstClientID <= 1000 || firstClientID >= 9999) {
      cout << "Unknown client ID " << firstClientID << " requested" << endl;
      return false;
   }
   else if(secondClientID != 0 && (secondClientID <= 1000 || secondClientID >= 9999)) {
   cout << "Unknown client ID " << firstClientID << " or " << secondClientID << " requested" << endl;
   }
   
   return true;
}

// ----------------------------------------------------------------------------
// getFirstAccount
//
// For the 'Move' command case:
// returns the first account number to perform a transaction on
//
// otherwise, firstAccountNum acts as the regular account number for 'Deposit'
// and 'Withdraw' and returns the account number to perform a transaction on
//
int Transaction::getFirstAccount() {
   return firstAccountNum;
}

// ----------------------------------------------------------------------------
// getSecondAccount
// returns the second account number to perform a transaction on
//
int Transaction::getSecondAccount() {
   return secondAccountNum;
}

// ----------------------------------------------------------------------------
// getFirstClient
// returns the first client ID to perform a transaction on
//
Client* Transaction::getFirstClient() {
   return firstClient;
}

// ----------------------------------------------------------------------------
// getSecondClient
// returns the first client ID to perform a transaction on
//
// Only used for the 'Move' command case
//
Client* Transaction::getSecondClient() {
   return secondClient;
}

// ----------------------------------------------------------------------------
// getCommand
// returns one of the commands: 'D', 'W', 'M', 'H'
// "Deposit" - "Withdraw" - "Move" - "History"
//
char Transaction::getCommand() {
   return command;
}

// ----------------------------------------------------------------------------
// getAmount
// returns the amount of money to use when performing a transaction
//
int Transaction::getAmount() {
   return amount;
}

// ----------------------------------------------------------------------------
// move
// withdraws money from one client and deposits the amount into another
//
void Transaction::move(Client* firstClient, Client* secondClient) {
   // create a deposit object to store in secondClient's history
   Transaction* depositTran = new Transaction('D', amount, secondAccountNum);
   
   // withdraw and deposit 'amount' from firstClient to secondClient
   // update history of second client
   bool success;
   success = firstClient->withdraw(firstAccountNum, amount);
   if(success) {
      secondClient->deposit(secondAccountNum, amount);
      secondClient->updateHistory(depositTran);
   }
}

