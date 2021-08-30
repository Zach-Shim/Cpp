// ------------------------------ transaction.h -------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Transaction Class: Transaction represents a general type of Transaction
//                    based on different types of genres
//                    (i.e. Borrow, Return, Inventory, History)

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Transaction is an abstract class
// - Transaction is a base class for subclasses of genres
// - Transactions can be stored inside Customers
// - Transactions are performed on Movies

//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <sstream>
#include "store.h"
using namespace std;

class Store;

class Transaction {
friend ostream& operator<<(ostream&, const Transaction&);
public:
   Transaction();                   // default constructor
   virtual ~Transaction();          // destructor
   
   virtual bool setData(stringstream&) = 0;      // set data from a transaction
   virtual bool executeTransaction(Store*) = 0;  // execute the transaction
   virtual void display() = 0;                   // display the transaction
};
#endif
