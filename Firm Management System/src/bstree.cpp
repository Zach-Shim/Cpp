#include "bstree.h"

//---------------------------------------------------------------------------
// Deafult Contrsuctor
BSTree::BSTree() {
   root = nullptr;
}

//---------------------------------------------------------------------------
// Destructor
// calls makeEmpty which deallocates all memory
BSTree::~BSTree() {
   makeEmpty();
}

//---------------------------------------------------------------------------
// makeEmpty
void BSTree::makeEmpty() {
   makeEmptyHelper(root);
   root = nullptr;
}

//---------------------------------------------------------------------------
// makeEmptyHelper
void BSTree::makeEmptyHelper(Node*& current) {
   if (current == nullptr)
   {
      return;
   }
   if (current->left != nullptr)
   {
      makeEmptyHelper(current->left);
   }
   if (current->right != nullptr)
   {
      makeEmptyHelper(current->right);
   }
   delete current->data;
   current->data = nullptr;
   current->right = nullptr;
   current->left = nullptr;
   delete current;
   current = nullptr;
}

//---------------------------------------------------------------------------
// insert
// insert object into the tree, parameter holds pointer to object to insert
bool BSTree::insert(Client* clientPtr) {
   Node* ptr = new Node;
   ptr->data = clientPtr;
   ptr->left = ptr->right = nullptr;
   return insertHelper(ptr, root);
}

//---------------------------------------------------------------------------
// insertHelper
bool BSTree::insertHelper(Node* ptr, Node*& current) {
   
   // Given root of the tree, it WILL insert the NodeData object into the tree
   // with current being the root of the tree or subtree
   if (current == nullptr) {
      current = ptr;
      return true;
   }
   
   // if smaller, insert in left subtree
   if (*ptr->data < *current->data) {
      return insertHelper(ptr, current->left);       // one step left

   }
   
   // (*ptr->data >= *current->data), insert in right subtree
   return insertHelper(ptr, current->right);         // one step right
}

//---------------------------------------------------------------------------
// retrieve
// retrieve object, first parameter is object to retrieve
// second parameter holds pointer to found object, nullptr if not found
//
bool BSTree::retrieve(const Client& target, Client*& cPtr) const {
   bool test = retrieveHelper(target, cPtr, root);
   if(test) return true;
   else return false;
}


//---------------------------------------------------------------------------
// retrieveHelper
// retrieve object depending on object ID, first parameter is objectID
// second parameter holds pointer to found object, nullptr if not found
//
bool BSTree::retrieveHelper(const Client& target, Client*& cPtr,
                                                Node* current) const {
   // base case
   if(current == nullptr) {
      return true;
   }

   // client is found, set cPtr equal to the current client object
   if(*current->data == target) {
      cPtr = current->data;
      return true;
   }
   // travel down the tree
   else if(*current->data > target) {
      return retrieveHelper(target, cPtr, current->left);   // travel left
   }
   else {
      return retrieveHelper(target, cPtr, current->right);  // travel right
   }
}

//---------------------------------------------------------------------------
// Overloaded Retrieve
// retrieve object depending on object ID, first parameter is objectID
// second parameter holds pointer to found object, nullptr if not found
//
bool BSTree::retrieve(const int& target, Client*& cPtr) const {
   bool test = retrieveHelper(target, cPtr, root);
   if(test) return true;
   else return false;
}


//---------------------------------------------------------------------------
// retrieveHelper
// retrieve object depending on object ID, first parameter is objectID
// second parameter holds pointer to found object, nullptr if not found
//
bool BSTree::retrieveHelper(const int& target, Client*& cPtr,
                                                Node* current) const {
   // base case
   if(current == nullptr) {
      return true;
   }

   // target found, set cPtr equal to current client object
   if(current->data->getID() == target) {
      cPtr = current->data;
      return true;
   }
   // travel down the tree
   else if((*current->data).getID() > target) {
      return retrieveHelper(target, cPtr, current->left);   // travel left
   }
   else {
      return retrieveHelper(target, cPtr, current->right);  // travel right
   }
}

//---------------------------------------------------------------------------
// display
// displays the contents of a tree to cout
//
void BSTree::display() const {
   displayHelper(root);
}

//---------------------------------------------------------------------------
// displayHelper
// displays a clients data
// displays client's name, ID, starting balance, and closing balance
//
void BSTree::displayHelper(Node* current) const {
   if(current != nullptr) {
      displayHelper(current->left);    // travel left
      
      // print out initial balance of each account
      cout << setw(4) << current->data->getID() << " " <<
                                          current->data->getName() << endl;
      cout << "Initial Balances:";
      for(int i = 0; i < MAXACCOUNTS; i++) {
         cout.width(6);
         cout << current->data->getBaseValue(i);
      }
      
      // print out final balances of each account
      cout << "\nFinal Balances:";
      cout.width(8);
      for(int i = 0; i < MAXACCOUNTS; i++) {
         cout << current->data->getCurrentValue(i);
         cout.width(6);
      }
      cout << endl << endl;
      displayHelper(current->right);      // travel right
   }
}

//---------------------------------------------------------------------------
// isEmpty
// returns true if tree is empty
//
bool BSTree::isEmpty() const {
   return (root == nullptr);
}


