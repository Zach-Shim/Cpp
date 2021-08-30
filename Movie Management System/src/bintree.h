// -------------------------------- BinTree.h --------------------------------

// CSS 343
// Created: June 5th, 2020
// Last Modified: August 21st, 2020

// ---------------------------------------------------------------------------

// BinTree class:    A binary search tree is a special type of binary tree.
//                   - For each node n in a binary search tree, the value of
//                     n is > all of the values in the left subtree and < all
//                     values in the right subtree.
//                   - All subtrees are binary search trees.
//                   - Useful for performing fast lookup (like binary search)
//                     and can be used to sort arrays/lists

// ---------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

//   -- operator<< dislplays the nodes of the BinTree in an inorder fashion
//   -- all functions use recursive helpers except the default constructor and
//      isEmpty
//   -- getHeight is implemented in a way works for both Binary Search Trees
//      and general Binary Trees where data could be stored anywhere.
//    - getHeight is implemented using this height definition:
//          The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.
//   -- An empty tree has 0 nodes
//   -- Keep the templated class inside the .h file
//   -- BinTree does not allow duplicate data

// ---------------------------------------------------------------------------

#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <string>
#include <iomanip>
#include "classic.h"
#include "comedy.h"
#include "drama.h"
using namespace std;

template<typename Item>
class BinTree {
//--------------------------- operator<< ------------------------------------
// Description:     displays the tree using inorder traversal
//                  Uses inorderHelper to print out all nodes in an inorder
//                  traversal of the binary tree
//
// Preconditions:   Item class is responsible for displaying its own data
//
// Postconditions:  each node in *this BSTree is output onto the screen
//
friend ostream& operator<<(ostream& output, const BinTree<Item>& treeDisplay) {
   typename BinTree<Item>::Node* current = treeDisplay.root;
   
   // display heading
   cout << setw(5) << "Genre" << setw(8) << "Media";
   cout << setw(34) << "Title" << setw(20) << "Director";
   cout << setw(7) << "Year" << setw(7) << "Stock" << endl;
   
   treeDisplay.inorderHelper(output, current);
   output << endl;
   return output;
}
   
public:
   //----------------------- default constructor ------------------------------
   // Description:     root is set to nullptr
   // Preconditions:   none
   // Postconditions:  root is set to nullptr
   BinTree() {
      root = nullptr;
   }
   
   //---------------------------- destructor ----------------------------------
   // Description:     deallocates all memory in *this
   //                  uses helper function makeEmpty
   // Preconditions:   this* BinTree is a Binary Search Tree
   // Postconditions:  *this is deallocated
   //                  root is null
   ~BinTree() {
      makeEmpty();
   }
   
   //------------------------- Copy Constructor -------------------------------
   // Description:     deep copies a Binary Search Tree into *this
   // Preconditions:   BinTree right is a Binary Search Tree
   // Postconditions:  *this is a copy of BinTree right
   BinTree(const BinTree& right) {
      copyHelper(root, right.root);          // private helper
   }
   
   //----------------------------- operator= ----------------------------------
   // Description:     deep copies a Binary Search Tree into *this
   // Preconditions:   BinTree right is a Binary Search Tree
   // Postconditions:  *this is a copy of BinTree right
   BinTree<Item>& operator=(const BinTree<Item>& right) {
      if(this != &right) {
         copyHelper(root, right.root);       // private helper
      }
      return *this;
   }

   //------------------------------ makeEmpty ---------------------------------
   // Description:
   // deallocates all memory in *this
   // Preconditions:   this* BinTree is a Binary Search Tree
   //                  current is pointing to the root of *this BSTree
   // Postconditions:  *this is deallocated
   //                  root is null
   void makeEmpty() {
      makeEmptyHelper(root);           // private helper
   }
   
   // ------------------------------ isEmpty ----------------------------------
   // Description:     tests whether a tree object (this) is empty
   //
   // Preconditions:   none
   //
   // Postconditions:  return true if tree is empty
   //                  return false otherwise
   //
   bool isEmpty() const {
      return (root == nullptr);
   }
   
   // ------------------------------ insert -----------------------------------
   // Description:     inserts a new node into the binary search tree
   //
   // Preconditions:   NodeData newData has been allocated and holds a string
   //
   // Postconditions:  the binary search tree has inserted a new leaf
   //
   bool insert(Item* newData) {
      if(newData == nullptr) return false;
      return insertHelper(newData, root);          // private helper
   }
   
   //------------------------------- retrieve ---------------------------------
   // Description:
   // retrieve a node based on NodeData from the BSTree
   // Preconditions:   p is NULL and
   //                  target is a NodeData object with string data
   // Postconditions:  return true if the target NodeData was found and p is
   //                  pointing to the target data in the tree
   //                  return false otherwise
   bool retrieve(const Item& target, Item*& p) const {
      return retrieveHelper(target, p, root);         // private helper
   }
   
   //------------------------------- retrieve ---------------------------------
   // Description:
   // retrieve a node based on NodeData from the BSTree
   // Preconditions:   p is NULL and
   //                  target is a NodeData object with string data
   // Postconditions:  return true if the target NodeData was found and p is
   //                  pointing to the target data in the tree
   //                  return false otherwise
   bool retrieveClassic(const Item& target, Item*& p) const {
      const Classic& targetMovie = static_cast<const Classic &>(target);
      return retrieveClassicHelper(targetMovie, p, root);    // private helper
   }
   
private:
   struct Node {
      Item* data;                      // pointer to data object
      Node* left;                      // left subtree pointer
      Node* right;                     // right subtree pointer
   };
   Node* root;                         // root of the tree

   
   //   ----------------------------------------------
   //                 helper functions
   //   ----------------------------------------------
   
   //---------------------------- copyHelper ----------------------------------
   // Description:     deep copies a Binary Search Tree into *this
   //                  recursive preorder traversal of the tree
   // Preconditions:   copyNode is pointing to right is a Binary Search Tree
   //                  Node current is pointing to *this root node
   //                  Node rightCurrent is pointing to the root of the the
   //                  BSTree to copy
   // Postconditions:  *this is a copy of BinTree right
   //
   void copyHelper(Node* &current, const Node* rightCurrent) {
      // create node, then recurisvely move through the left and right subtrees
      // the right BSTree in a preorder traversal
      if(rightCurrent != nullptr) {
         // create new node
         current = new Node;
         switch(rightCurrent->key) {
            case 'C':
               current->data = new Classic(*rightCurrent->data);
               break;
            case 'F':
               current->data = new Comedy(*rightCurrent->data);
               break;
            case 'D':
               current->data = new Drama(*rightCurrent->data);
               break;
         }
         current->left = current->right = nullptr;
         
         // recursively traverse left and right subtrees
         copyHelper(current->left, rightCurrent->left);
         copyHelper(current->right, rightCurrent->right);
      }
   }
   
   //----------------------------- makeEmpty ----------------------------------
   // Description:
   // deallocates all memory in *this BSTree
   // uses helper function makeEmptyHelper for recursion
   // Preconditions:   this* BinTree is a Binary Search Tree
   // Postconditions:  *this is deallocated
   //                  root is null
   void makeEmptyHelper(Node*& current) {
      if(current == nullptr) {
         return;
      }
      // recursively move down tree and delete nodes in a postorder traversal
      makeEmptyHelper(current->left);
      makeEmptyHelper(current->right);
      
      // delete node
      delete current->data;
      current->data = nullptr;
      current->right = current->left = nullptr;
      delete current;
      current = nullptr;
   }
   
   //--------------------------- insertHelper ---------------------------------
   // Description:     inserts a new node into the binary search tree
   //
   // Preconditions:   NodeData newData has been allocated and holds a string
   //                  current is pointing to the root of *this BSTree
   //
   // Postconditions:  the binary search tree has inserted a new leaf
   //
   // DOES NOT ALLOW DUPLICATE OBJECTS
   bool insertHelper(Item* newData, Node *& current) {
      // once we hit a leaf (bottom of the tree), insert the data
      if(current == nullptr) {
         current = new Node;
         current->data = newData;
         current->left = current->right = nullptr;
         return true;
      }
      // if item is less than current item, insert in left subtree
      else if(*current->data > *newData) {
         return insertHelper(newData, current->left);
      }
      // otherwise insert in right subtree
      else if(*current->data < *newData) {
         return insertHelper(newData, current->right);
      }
      else {
         return false;
      }
      return true;
   }
   
   //---------------------------- retrieveHelper ------------------------------
   // Description:
   // retrieve a node based on Item from the BSTree
   // Preconditions:   p is NULL and
   //                  target is a NodeData object with string data
   //                  Node current is pointing to the root of *this tree
   // Postconditions:  return true if the target NodeData was found and p is
   //                  pointing to the target data in the tree
   //                  return false otherwise
   //
   bool retrieveHelper(const Item& target, Item*& p, Node* current) const {
      // base case
      if(current == nullptr) {
         return false;
      }
      // if target is found, assign p to data
      else if(*current->data == target) {
         p = current->data;
         return true;
      }
      // move right if the target data is greater than the current nodes data
      else if(*current->data < target) {
         return retrieveHelper(target, p, current->right);
      }
      // move left is the target data is less than the current nodes data
      return retrieveHelper(target, p, current->left);
   }
   
   //---------------------------- retrieveHelper ------------------------------
   // Description:
   // retrieve a Node with Classic data based on Item from the BSTree
   // Preconditions:   p is NULL and
   //                  target is a NodeData object with string data
   //                  Node current is pointing to the root of *this tree
   // Postconditions:  return true if the target NodeData was found and p is
   //                  pointing to the target data in the tree
   //                  return false otherwise
   bool retrieveClassicHelper(const Classic& target, Item*& p, Node* current)
                                                                        const {
      // base case
      if(current == nullptr) {
         return false;
      }
      // if target is found, assign p to data
      else if(target.isEqual(*current->data)) {
         p = current->data;
         return true;
      }
      // move right if the target data is greater than the current nodes data
      else if(*current->data < target) {
         return retrieveHelper(target, p, current->right);
      }
      // move left is the target data is less than the current nodes data
      return retrieveHelper(target, p, current->left);
   }
   
   //----------------------------- inorderHelper ------------------------------
   // Description:     helper for operator<< (output operator)
   //                  displays the tree using inorder traversal
   //
   // Preconditions:   current is pointing to the root of the *this BSTree
   //                  NodeData class is responsible for displaying its
   //                  own data
   //
   // Postconditions:  each node in *this BSTree is output onto the screen
   //
   void inorderHelper(ostream& output, Node* current) const {
      if(current == nullptr) {
         return;
      }
      
      inorderHelper(output, current->left);     // walk through left subtree
      (*current->data).display();               // ouput data
      inorderHelper(output, current->right);    // walk through right subtree
   }
   
};

#endif
