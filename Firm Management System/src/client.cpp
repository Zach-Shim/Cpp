#include "client.h"

//----------------------------------------------------------------------------
// Default Constructor
// defaults the account pointers in array to null
Client::Client() {
   for(int i = 0; i < MAXACCOUNTS; i++) {
      accounts[i] = nullptr;
   }
}

//----------------------------------------------------------------------------
// Destructor
// frees the memory from the Account pointers in the funds array
//
Client::~Client() {
   makeEmpty();
}

//----------------------------------------------------------------------------
// makeEmpty
// frees the memory from the Account pointers in the funds array
//
void Client::makeEmpty() {
   // delete accounts array
   for(int i = 0; i < MAXACCOUNTS; i++) {
      if(accounts[i] == nullptr) break;
      else {
         delete accounts[i];
         accounts[i] = nullptr;
      }
   }
   
   // delete the transaction history vector
   if(transactionHistory.empty()) return;
   for(unsigned int i = 0; i < transactionHistory.size(); i++) {
      // delete vector
      delete transactionHistory[i];
      transactionHistory[i] = nullptr;
   }
}

//----------------------------------------------------------------------------
// setData
// Reads in data from a Client Stream txt file containing Client data
// Reads in command, clientID, and ten account values
//
bool Client::setData(ifstream& infile) {
   infile >> lastName >> firstName >> clientID;   // client information
   
   // error checking clientID
   if(infile.eof()) {
      return false;
   }
   else if(clientID <= 1000 || clientID >= 9999) {
      cout << "Invalid Client ID " <<  clientID << " from File" << endl;
      return false;
   }
   
   // read in money for accounts and set data in account object
   int accountValue;
   for(int i = 0; i < MAXACCOUNTS; i++) {
      infile >> accountValue;
      accounts[i] = new Account;
      bool success = accounts[i]->setData(i, accountValue);
      if(!success) return false;
   }
   return true;
}

//----------------------------------------------------------------------------
// setID
// set the ID for a client
bool setID(int clientNum) {
   
}

//----------------------------------------------------------------------------
// deposit
// deposit money into an account
//
bool Client::deposit(int accountNum, int amount) {
   bool success = accounts[accountNum]->deposit(amount);
   return success;

}

//----------------------------------------------------------------------------
// withdraw
// withdraws money from an account
//
bool Client::withdraw(int accountNum, int amount) {
   // withdraw money from account
   int withdrawn = accounts[accountNum]->withdraw(amount);
   bool sufficient = true;
   int secondWithdraw = 0;
   
   if(withdrawn < amount) {
      // if there is an insufficient balance, take money from another account
      // only applies to market and fund accounts
      switch(accountNum) {
         case 0:
            secondWithdraw = accounts[accountNum+1]->
                                                withdraw(amount - withdrawn);
            break;
         case 1:
            secondWithdraw = accounts[accountNum-1]->
                                                withdraw(amount - withdrawn);
            break;
         case 2:
            secondWithdraw = accounts[accountNum+1]->
                                                withdraw(amount - withdrawn);
            break;
         case 3:
            secondWithdraw = accounts[accountNum-1]->
                                                withdraw(amount - withdrawn);
            break;
         default:
            sufficient = false;
      }
   }
   
   // if there is still an insufficient balance, print error statement
   if((secondWithdraw + withdrawn) != amount) sufficient = false;
   if(!sufficient) {
      cout << "Withdrawal not performed on " << accounts[accountNum]->getType()
      << " for client " << clientID << ";" << endl;
      cout << "       insufficient funds" << endl << endl;
      return false;
   }
   
   return true;
}

//----------------------------------------------------------------------------
// addTransaction
// add a new transaction to the history
//
void Client::updateHistory(Transaction* t) {
   transactionHistory.push_back(t);
}

//----------------------------------------------------------------------------
// showHistory
// print the transaction history of the client
//
void Client::showHistory() {
   int amount;
   int accountNum;
   
   // print out heading for history of transactions
   cout << "History of transaction for client ";
   cout << firstName << " " << lastName;
   cout << ", client ID = " << clientID << ";" << endl;
   cout.setf(ios::left);
   cout << setw(10) << "Type" << setw(8) << "Amount" << "Detail" << endl;
   cout << "--------- ------- --------------------------------------" << endl;

   // print out history
   cout << "size " << transactionHistory.size() << endl;
   for(unsigned int i = 0; i < transactionHistory.size(); i++) {
      
      // initialize amount moved and transaction account number
      amount = transactionHistory[i]->getAmount();
      accountNum = transactionHistory[i]->getFirstAccount();
      
      // print out history depending on command
      switch(transactionHistory[i]->getCommand()) {
         case 'D':
            cout << setw(10) << "deposit" << "$" << setw(7) << amount;
            cout << "into " << accounts[accountNum]->getType() << endl;
            break;
         case 'W':
            cout << setw(10) << "withdraw" << "$" << setw(7) << amount;
            cout << "from " << accounts[accountNum]->getType() << endl;
            break;
         case 'M':
            // from first account
            cout << setw(10) << "move" << "$" << setw(7) << amount;
            cout << "from " << accounts[accountNum]->getType();
            
            // to second account
            accountNum = transactionHistory[i]->getSecondAccount();
            cout << " to " << accounts[accountNum]->getType() << " for client "
            << transactionHistory[i]->getSecondClient() << endl;
            break;
         case 'H':
            cout << "history" << endl;
            break;
      }
   }
   cout << endl;
   cout.unsetf(ios::left);
}

//----------------------------------------------------------------------------
// getID
// return the client ID
//
int Client::getID() {
   return clientID;
}

//----------------------------------------------------------------------------
// getName
// return the name of a client
//
string Client::getName() {
   string name = firstName + " " + lastName;
   return name;
}

//----------------------------------------------------------------------------
// getBaseValue
// return the starting balance of an account
// parameter is account number
//
int Client::getBaseValue(int accountNum) {
   return accounts[accountNum]->getBase();
}

//----------------------------------------------------------------------------
// getCurrentValue
// return the current balance of an account
// parameter is account number
//
int Client::getCurrentValue(int accountNum) {
   return accounts[accountNum]->getCurrent();
}
 
//----------------------------------------------------------------------------
// operator==
// overloaded operator for ==
// tests two client ID's for equality
//
bool Client::operator==(const Client& right) const {
   return (clientID == right.clientID);
}

//----------------------------------------------------------------------------
// operator!=
// overloaded operator for !=
// tests two client ID's for inequality
//
bool Client::operator!=(const Client& right) const{
   return !(clientID == right.clientID);
}

//----------------------------------------------------------------------------
// operator<
// overloaded operator for <
// tests if one client ID's is less than another's
//
bool Client::operator<(const Client& right) const {
   return clientID < right.clientID;
}

//----------------------------------------------------------------------------
// operator>
// overloaded operator for >
// tests if one client ID's is less than another's
//
bool Client::operator>(const Client& right) const {
   return clientID > right.clientID;
}

