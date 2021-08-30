// ------------------------------ transactionfactory.h ---------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// TransactionFactory Class: Creates Transactions based on it's type

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - createTransaction is static because a TransactionFactory object does not
//   need to be directly insantiated - Only class Store needs access to it to
//   create different types of Transactions

//

#ifndef TRANSACTIONFACTORY_H
#define TRANSACTIONFACTORY_H

#include <iostream>
#include <sstream>
#include "transaction.h"

using namespace std;

class TransactionFactory {
public:
   TransactionFactory();
   ~TransactionFactory();
   
   static Transaction* createTransaction(string);
};
#endif
