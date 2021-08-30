#include "inventory.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
Inventory::Inventory() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
Inventory::~Inventory(){}

//-------------------------------- setData ------------------------------------
// Description:     Sets the data members of a Inventory Transaction
//
// Preconditions:   infile holds information about a Inventory Transaction
//
// Postconditions:  return true
//
bool Inventory::setData(stringstream& in_stream) {
   return true;
}

//--------------------------- executeTransaction ------------------------------
// Description:     Executes an Inventory transaction
//
// Preconditions:   Store* shop is pointing to a store object
//
// Postconditions:  displays the stock of every movie according to genre
//                  returns false
//
bool Inventory::executeTransaction(Store* shop) {

   cout << "Comedy Inventory:" << endl;
   cout << shop->getComedyTree();
   
   cout << "Classic Inventory:" << endl;
   cout << shop->getClassicTree();
   
   cout << "Drama Inventory:" << endl;
   cout << shop->getDramaTree();
   
   // return false (delete object since we do not store it in customer history)
   return false;
}

//-------------------------------- display ------------------------------------
// Description:     Displays Inventory data
//
// Preconditions:   none
//
// Postconditions:  Inventory Transaction data is displayed
//
void Inventory::display() {
   cout << "Inventory" << endl;
}
