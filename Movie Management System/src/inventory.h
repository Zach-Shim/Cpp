// ------------------------------ inventory.h ---------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Inventory Class: A class that represents an operation to display all items
//                  (movies) currently in a Store object

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Derived class from Transaction
// - Prints out Genre, Media, Title, Director, and Year of every Movie
//   (every movie has atleast this information)

//

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "transaction.h"
using namespace std;

class Inventory : public Transaction {
public:
   Inventory();
   virtual ~Inventory();
   
   virtual bool setData(stringstream&);        // set data from a transaction
   virtual bool executeTransaction(Store*);   // execute the transaction
   virtual void display();                    // displays Inventory data
};
#endif
