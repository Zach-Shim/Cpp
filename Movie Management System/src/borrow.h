// -------------------------------- borrow.h ----------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Borrow Class: A class that represents an operation to removed copies a
//               movies to a Store

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Dervied class from Transaction

//

#ifndef BORROW_H
#define BORROW_H

#include <iostream>
#include <sstream>
#include "transaction.h"
#include "customer.h"
#include "movie.h"

using namespace std;

class Borrow : public Transaction {
public:
   Borrow();                        // default constructor
   virtual ~Borrow();               // destructor
   
   virtual bool setData(stringstream&);        // set data from a transaction
   virtual bool executeTransaction(Store*);    // execute the transaction
   virtual void display();          // displays Borrow data
private:
   int clientID;
   char mediaType;
   string movieData;
   
   Movie* findMovie(Store*);
   bool borrowAlternative(Store*, Customer*, Movie*);
};
#endif
