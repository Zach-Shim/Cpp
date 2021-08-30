// -------------------------------- customer.h --------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Customer Class: Stores information about a Customer
//                 (i.e. first name, last name, ID, and transaction history)

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Customers can perform Transactions on Movies which is stored in their
//   transaction history

//

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "movie.h"
using namespace std;

class Transaction;

class Customer {
public:
   Customer();
   ~Customer();
   
   // setter functions
   bool setData(string);
   
   // getter functions
   int getID() const;
   string getFirstName() const;
   string getLastName() const;
   
   // transaction history
   void displayHistory();
   void updateHistory(Transaction*);
   void updateBorrowedMovies(Movie*);
   bool returnMovies(Movie*);
   
   // overloaded operators
   bool operator==(const Customer&);
   
private:
   int customerID = 0;
   string firstName = "";
   string lastName = "";
   vector<Movie*> borrowedMovies;
   vector<Transaction*> transactionHistory;
};
#endif
