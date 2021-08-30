#ifndef FIRM_H
#define FIRM_H

#include <iostream>
#include <fstream>
#include "queue.h"
#include "client.h"
#include "transaction.h"
#include "bstree.h"
using namespace std;

//----------------------------------------------------------------------------
// Firm ADT: Firm is a class that represents a set of clients within a
// banking firm.
//
// Implementation and Assumptions:
//   -- Takes a client text file of these clients, store
//      them, and subsequently queue up transactions from a text file that
//      concern those clients.
//   -- Prints out the starting and ending balances of the clients
//      within the firm at the end of the day.
//
//----------------------------------------------------------------------------

class Firm {
public:
   Firm();                          // default constructor
   ~Firm();                         // destructor
   
   void addClients(ifstream&);      // reads clients from a file
   void addTransactions(ifstream&); // processes each transaction from the queue
   void processTransactions();      // process each transaction
   void displayReport();           // display starting and ending balances
   
private:
   BSTree clientsTree;              // stores clients
   Queue transQ;       // stores transactions
};

#endif


