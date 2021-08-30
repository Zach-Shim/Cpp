#ifndef BSTREE_H
#define BSTREE_H

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "client.h"
using namespace std;

//---------------------------------------------------------------------------
// BSTree ADT:
//
// Implementation & Assumptions:
//---------------------------------------------------------------------------

class BSTree {
   
public:
   BSTree();
   ~BSTree(); // calls makeEmpty which deallocates all memory

   // insert object into the tree, parameter holds pointer to object to insert
   bool insert(Client*);

   bool retrieve(const Client& , Client*&) const;       // Retrieve object
   bool retrieve(const int& clientID, Client*&) const;  // Overloaded Retrieve

   void display() const;   // displays the contents of a tree to cout
   void makeEmpty();       // empties the current tree, deallocates all memory
   bool isEmpty() const;   // returns true if tree is empty

private:
   
   struct Node{            // glue that holds data properly
      Client* data;
      Node* right;
      Node* left;
   };

   Node* root;             // root of the tree

   // recursive helper functions
   void displayHelper(Node* current) const;
   void makeEmptyHelper(Node*& current);
   bool insertHelper(Node* dataptr, Node*& current);
   bool retrieveHelper(const Client& , Client*&, Node* current) const;
   bool retrieveHelper(const int& , Client*&, Node* current) const;
};

#endif
