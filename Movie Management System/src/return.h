// -------------------------------- return.h ----------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Return Class: A class that represents an operation to add copies a movies
//               to a Store

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Dervied class from Transaction

//

#ifndef RETURN_H
#define RETURN_H

#include <iostream>
#include <sstream>
#include "transaction.h"
#include "movie.h"

using namespace std;

class Return : public Transaction {
public:
   Return();                        // default constructor
   virtual ~Return();               // destructor
   
   virtual bool setData(stringstream&);        // set data from a transaction
   virtual bool executeTransaction(Store*);    // execute the transaction
   virtual void display();          // displays Borrow data
private:
   int clientID;
   char mediaType;
   string movieData;
   
   Movie* findMovie(Store*);
};
#endif
