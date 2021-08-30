#include "history.h"
#include "customer.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
History::History() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
History::~History(){}

//-------------------------------- setData ------------------------------------
// Description:     Sets the data members of a History Transaction
//
// Preconditions:   string data holds information about a History Transaction
//
// Postconditions:  return true if valid data was initailized to data members
//                  return false otherwise
//
bool History::setData(stringstream& in_stream) {
   in_stream >> clientID;
   
   // check transaction type data
   if(clientID > 9999 || clientID < 1000) {
      cout << "ERROR: Transaction Failed: ";
      cout << "Customer " << clientID << " does not exist" << endl;
      return false;
   }
   
   return true;
}

//--------------------------- executeTransaction ------------------------------
// Description:     Executes a History transaction
//
// Preconditions:   Store* shop is pointing to a store object
//
// Postconditions:  displays the stock of every movie according to genre
//
// NOTE: History and Inventory transactions are omitted from a client's
//       Transaction history (Only Borrow and Return Trans. are showed)
//
bool History::executeTransaction(Store* shop) {
   // retrieve client from hashtable databse; return false if not found
   Customer* client = shop->getCustomerInfo().retrieve(clientID);
   if(client == nullptr) {
      cout << "ERROR: History Display Failed: ";
      cout << "Customer" << clientID << "Not Found" << endl;
      return false;
   }
   
   cout << "History for " << client->getFirstName();
   cout << " " << client->getLastName() << ":" << endl;
   client->displayHistory();
   cout << endl;
   
   // return false (delete object since we do not store it in customer history)
   return false;
}

//-------------------------------- display ------------------------------------
// Description:     Displays History data
//
// Preconditions:   none
//
// Postconditions:  History Transaction data is displayed
//
void History::display() {
   cout << "History";
}
