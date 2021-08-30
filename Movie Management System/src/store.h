// ------------------------------ store.h ---------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Store Class: A management class in charge of building movies, customers, and
//              transactions
//              A store has an inventory of Movies, which Customers can perform
//              different Transactions on

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

//
//
//

//

#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <fstream>
#include "bintree.h"
#include "hashtable.h"
#include "moviefactory.h"
#include "transactionfactory.h"

using namespace std;

class Store {
public:
   Store();                                  // default constructor
   ~Store();                                 // destructor

   // build functions
   bool buildMovies(ifstream&);           
   bool buildCustomers(ifstream&);
   bool processTransactions(ifstream&);
   
   // getter functions
   BinTree<Movie>& getComedyTree();
   BinTree<Movie>& getClassicTree();
   BinTree<Movie>& getDramaTree();
   HashTable<int, Customer>& getCustomerInfo();

private:
   HashTable<int, Customer> customerStorage;
   BinTree<Movie> comedyTree;
   BinTree<Movie> classicTree;
   BinTree<Movie> dramaTree;
};
#endif
