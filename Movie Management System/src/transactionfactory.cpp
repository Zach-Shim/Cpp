#include "transactionfactory.h"
#include "borrow.h"
#include "return.h"
#include "inventory.h"
#include "history.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
TransactionFactory::TransactionFactory() {
   
}

//------------------------------ destructor -----------------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
TransactionFactory::~TransactionFactory() {
   
}

//-------------------------- createTransactions -------------------------------
// Description:     Creates a transaction object
//
// Preconditions:   string data is information about a transaction
//
// Postconditions:  returns a pointer a Transaction object
//                  (i.e. Borrow, Return, Inventory, History)
//
Transaction* TransactionFactory::createTransaction(string transData) {
   // initialize data
   char transactionType;
   stringstream ss(transData);
   ss >> transactionType;
   
   // create movie object based on transaction type
   Transaction* newTransPtr = nullptr;
   switch(transactionType) {
      case 'B': {
         newTransPtr = new Borrow;
         break;
      }
      case 'R': {
         newTransPtr = new Return;
         break;
      }
      case 'I': {
         newTransPtr = new Inventory;
         break;
      }
      case 'H': {
         newTransPtr = new History;
         break;
      }
      default: {
         cout << "ERROR: Transaction Failed: Invalid Transaction Type '";
         cout << transactionType << "'" << endl;
         return nullptr;
      }
   }
   
   // set data for a transaction
   bool success = newTransPtr->setData(ss);
   if(!success) return nullptr;
   
   return newTransPtr;
}
