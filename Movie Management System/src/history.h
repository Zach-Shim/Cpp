// ------------------------------- history.h ----------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// History Class: A class that represents an operation to display all
//                transaction history for each customer

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Dervied class from Transaction

//

#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include "transaction.h"
using namespace std;

class History : public Transaction {
public:
   History();              // default constructor
   History(int);           // constructor
   virtual ~History();     // destructor
   
   virtual bool setData(stringstream&);        // set data from a transaction
   virtual bool executeTransaction(Store*);   // execute the transaction
   virtual void display();                    // displays History data
private:
   int clientID;
};

#endif
