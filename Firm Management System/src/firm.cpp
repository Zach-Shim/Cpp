#include "firm.h"

//----------------------------------------------------------------------------
// default constructor
// takes in no values
//
Firm::Firm() {}

//----------------------------------------------------------------------------
// destructor
// BSTree and Queue have own destructors
//
Firm::~Firm() {}

//----------------------------------------------------------------------------
// addClients
// add clients from a given data file into a binary search tree
//
void Firm::addClients(ifstream& infile) {
   Client* clientPtr;
   bool succesfulRead;
   for(;;) {
      clientPtr = new Client;
      succesfulRead = clientPtr->setData(infile);
      
      // reaches end of file
      if (infile.eof()) {
         delete clientPtr;
         clientPtr = nullptr;
         break;
      }
      
      // if insert was succesfull, then put Client in tree, otherwise invalid
      if(succesfulRead) {
         clientsTree.insert(clientPtr);
      }
      else {
         delete clientPtr;
         clientPtr = nullptr;
      }
   }
}

//----------------------------------------------------------------------------
// addTransactions
// adds transactions into the queue
//
void Firm::addTransactions(ifstream& infile) {
   Transaction* tPtr;
   bool succesfulRead;
   for(;;) {
      tPtr = new Transaction;
      
      succesfulRead = tPtr->setData(infile);       // set data of transaction
      
      if (infile.eof()) {                          // reaches end of file
         delete tPtr;
         tPtr = nullptr;
         break;
      }
      
      // if transaction data was succesfully set, push transaction into queue
      if(succesfulRead) {
         transQ.enqueue(tPtr);         // push transaction into queue
      }
      else {
         delete tPtr;                  // delete object
         tPtr = nullptr;
      }
   }
}

//----------------------------------------------------------------------------
// processTransactions
// processes every transaction held in the queue
//
void Firm::processTransactions() {
   Transaction* tPtr;
   Client* cPtr;
   bool success = false;
   for(;;) {
      // if the queue is empty, return
      if(transQ.isEmpty()) {
         return;
      }
      
      // dequeue transaction and retrieve it's Client from BSTree
      transQ.dequeue(tPtr);
      clientsTree.retrieve(tPtr->getFirstClient(), cPtr);
      
      // get transaction values
      char request = tPtr->getCommand();
      int account = tPtr->getFirstAccount();
      int amount = tPtr->getAmount();
      // process transaction based on request/command
      switch(request) {
         case 'D':
            success = cPtr->deposit(account, amount);
            break;
         case 'W':
            success = cPtr->withdraw(account, amount);
            break;
         case 'M':
            Client* secondClient;
            clientsTree.retrieve(tPtr->getSecondClient(), secondClient);
            tPtr->move(cPtr, secondClient);;
            break;
         case 'H':
            cPtr->updateHistory(tPtr);
            cPtr->showHistory();
            success = false;              // already updated history
            break;
      }
      
      if(success) cPtr->updateHistory(tPtr);    // update history
      
   }
}

//----------------------------------------------------------------------------
// displayReport
// displays an end of the day report for all clients in the BSTree
//
void Firm::displayReport() {
   cout << "REPORT" << endl << endl;
   clientsTree.display();
}


