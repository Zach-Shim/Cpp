#include "customer.h"
#include "transaction.h"
#include "movie.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
Customer::Customer() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
Customer::~Customer(){
   for(unsigned int i = 0; i < transactionHistory.size(); i++) {
      delete transactionHistory[i];
      transactionHistory[i] = nullptr;
   }
}

//--------------------------------- setData -----------------------------------
// Description:     Sets the data members of a Customer
//
// Preconditions:   string clientData holds information about a Customer
//
// Postconditions:  return true if valid data was initailized to data members
//                  return false otherwise
//
bool Customer::setData(string customerData) {
   stringstream ss(customerData);
   ss >> customerID;
   
   // error check customerID
   if(customerID < 1000 || customerID > 9999) {
      cout << "ERROR: Transaction Failed: Invalid Client ID ";
      cout << customerID << endl;
      return false;
   }
   
   // if there is valid data, read in customer name
   ss >> firstName >> lastName;
   return true;
}

//--------------------------------- getID -------------------------------------
// Description:     Returns customer ID
//
// Preconditions:   none
//
// Postconditions:  returns customer ID
//
int Customer::getID() const {
   return customerID;
}

//------------------------------ getFirstName ---------------------------------
// Description:     Retusn first name of Customer
//
// Preconditions:   none
//
// Postconditions:  returns first name of Customer
//
string Customer::getFirstName() const {
   return firstName;
}

//------------------------------- getLastName ---------------------------------
// Description:     Retusn last name of Customer
//
// Preconditions:   none
//
// Postconditions:  returns last name of Customer
//
string Customer::getLastName() const {
   return lastName;
}

//------------------------------ updateHistory --------------------------------
// Description:     Update Customer's history
//
// Preconditions:   Transaction* trans is a valid Transaction object with
//                  initialized data
//
// Postconditions:  A Transaction pointer is pushed into transactionHistory
//                  vector
//
void Customer::updateHistory(Transaction* trans) {
   transactionHistory.push_back(trans);
}

//--------------------------- updateBorrowedMovies ----------------------------
// Description:     show Customer's borrowed Movies
//
// Preconditions:   Borrow* bTrans is a valid Borrow Transaction object with
//                  initialized data
//
// Postconditions:  A Borrow Transaction pointer is pushed into borrowedMovies
//                  vector
//
void Customer::updateBorrowedMovies(Movie* borrowedMovie) {
   borrowedMovies.push_back(borrowedMovie);
}

//------------------------------- returnMovies --------------------------------
// Description:     Return a movie a Customer has borrowed
//
// Preconditions:   Movie* returnMoviePtr is intialized with valid data
//
// Postconditions:  return true if a Customer has borrowed a Movie and it has
//                  been successfully returned
//                  return false otherwise
//
bool Customer::returnMovies(Movie* returnMoviePtr) {
   for(unsigned int i = 0; i < borrowedMovies.size(); i++) {
      if(*borrowedMovies[i] == *returnMoviePtr) {
         returnMoviePtr->addStock();
         return true;
      }
   }
   return false;
}

//------------------------------ displayHistory -------------------------------
// Description:     show Customer's history
//
// Preconditions:   none
//
// Postconditions:  transaction history is displayed
//
void Customer::displayHistory() {
   for(unsigned int i = 0; i < transactionHistory.size(); i++) {
      (transactionHistory[i])->display();
   }
}

//------------------------------- operator== ----------------------------------
// Description:     Tests the equality of two Customer objects
//                  Compares customerID and name
//
// Preconditions:   Customer& right is a Customer with intialized, valid data
//
// Postconditions:  return true if customerID and first and last name are equal
//                  return false otherwise
//
bool Customer::operator==(const Customer& right) {
   return customerID == right.customerID && firstName == right.firstName &&
                                            lastName == right.lastName;
}
