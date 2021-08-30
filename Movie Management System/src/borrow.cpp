#include "borrow.h"
#include "customer.h"
#include "bintree.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
Borrow::Borrow() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
Borrow::~Borrow(){}

//-------------------------------- setData ------------------------------------
// Description:     Sets the data members of a Borrow Transaction
//
// Preconditions:   infile holds information about a Borrow Transaction
//
// Postconditions:  return true if valid data was initailized to data members
//                  return false otherwise
//
bool Borrow::setData(stringstream& in_stream) {
   in_stream >> clientID >> mediaType;
   
   // check transaction type data
   if(clientID > 9999 || clientID < 1000) {
      cout << "ERROR: Transaction Failed: ";
      cout << "Customer " << clientID << " does not exist" << endl;
      return false;
   }
   // check media type data
   if(mediaType != 'D') {
      cout << "ERROR: Transaction Failed: Invalid Media Type ";
      cout << mediaType << endl;
      return false;
   }
   
   getline(in_stream, movieData);
   return true;
}

//--------------------------- executeTransaction ------------------------------
// Description:     Executes a borrow transaction
//
// Preconditions:   Store* shop is pointing to a store object
//
// Postconditions:  return true if Borrow Transacition was successful
//                  return false otherwise
//
bool Borrow::executeTransaction(Store* shop) {
   // retrieve client from hashtable databse; return false if not found
   Customer* client = shop->getCustomerInfo().retrieve(clientID);
   if(!client) {
      cout << "ERROR: Borrow Transaction Failed: ";
      cout << "CustomerID " << clientID << " Not Found" << endl;
      return false;
   }
   
   // retrieve movie from movie tree database; return false if not found
   Movie* media = findMovie(shop);
   if(media == nullptr) {
      cout << "ERROR: Borrow Transaction Failed: ";
      cout << "Movie Not Found" << endl;
      return false;
   }
   
   // update stock of movie and history of client; return false if out of stock
   bool success = media->removeStock();
   if(!success) {
      cout << "ERROR: Borrow Transaction Failed: Not Enough Stock" << endl;
      if(media->getType() == 'C') {
         return borrowAlternative(shop, client, media);
      }
      return false;
   }
   
   client->updateBorrowedMovies(media);
   client->updateHistory(this);
   return true;
}

//-------------------------------- findMovie ----------------------------------
// Description:     finds a movie from a movieTree
//
// Preconditions:   mTree is initialized and has data
//                  stringstream ss is instantiated
//
// Postconditions:  return movie if movie is found in tree
//                  return nullptr if movie is not found
//
Movie* Borrow::findMovie(Store* shop) {
   // read and instantiate data
   char movieType;
   stringstream ss(movieData);
   ss >> movieType;
   
   // find and create movie type
   Movie* targetMovie = nullptr;
   switch(movieType) {
      case 'F': {
         // read in data
         string title;
         int year;
         ss.ignore();
         getline(ss, title, ',');
         ss >> year;
         
         // create movie type object
         Comedy* comedyPtr = new Comedy;
         comedyPtr->setTitle(title);
         comedyPtr->setYear(year);
         
         // retrieve object from tree; return nullptr if not found
         shop->getComedyTree().retrieve(*comedyPtr, targetMovie);
         
         delete comedyPtr;
         comedyPtr = nullptr;
         break;
      }
      case 'C': {
         // read in releaseData and majorActor from movieData data member
         int releaseMonth, releaseYear;
         string majorActor;
         ss >> releaseMonth >> releaseYear;
         ss.ignore();
         getline(ss, majorActor);

         // create Classic type object and initialize data
         Classic* classicPtr = new Classic;
         classicPtr->setMajorActor(majorActor);       // Movie class does not
         classicPtr->setReleaseMonth(releaseMonth);   // contain these methods
         classicPtr->setYear(releaseYear);

         // retrieve target from classic tree; return nullptr if not found
         shop->getClassicTree().retrieve(*classicPtr, targetMovie);
         
         delete classicPtr;
         classicPtr = nullptr;
         break;
      }
      case 'D': {
         // read in data
         string director, title;
         ss.ignore();
         getline(ss, director, ',');   // stock of movie
         ss.ignore();
         getline(ss, title, ',');   // stock of movie
         
         // create movie object
         Drama* dramaPtr = new Drama;
         dramaPtr->setDirector(director);
         dramaPtr->setTitle(title);

         // retrieve object from tree; return nullptr if not found
         shop->getDramaTree().retrieve(*dramaPtr, targetMovie);
         
         delete dramaPtr;
         dramaPtr = nullptr;
         break;
      }
   }
   return targetMovie;
}

//--------------------------- borrowAlternative -------------------------------
// Description:     Method is called when a Classic Movie is out of stock
//                  and has different versions
//
// Preconditions:   Store* shop is pointing to a Store object
//                  Customer* client is pointing to a valid Customer object
//                  Movie* media is pointing to a valid Movie object
//
// Postconditions:  return true if Borrow Transacition was successful
//                  return false otherwise
//
bool Borrow::borrowAlternative(Store* shop, Customer* client, Movie* media) {
   while(true) {
      // if there are alter movies; retrieve Classic movie from classicTree
      Movie* alterClassic = nullptr;
      shop->getClassicTree().retrieveClassic(*media, alterClassic);
      
      // if there was an alternative movie found that has stock, successfull
      if(alterClassic && alterClassic->removeStock()){
         client->updateBorrowedMovies(media);
         client->updateHistory(this);
         return true;
      }
      else {
         return false;
      }
   }
   return true;
}

//-------------------------------- display ------------------------------------
// Description:     Displays Borrow data
//
// Preconditions:   none
//
// Postconditions:  Borrow Transaction data is displayed
//
void Borrow::display() {
   char movieType;
   stringstream ss(movieData);
   ss >> movieType;
   cout << "Borrowed:  ";
   switch(movieType) {
      case 'C': {
         // read in data
         int releaseMonth, releaseYear;
         string majorActor;
         ss >> releaseMonth >> releaseYear;
         ss.ignore();
         getline(ss, majorActor);
         
         cout << "Classic Movie with major actor " << majorActor;
         cout << " and release date " << releaseMonth << " " << releaseYear;
         cout << endl;
      }
      case 'F': {
         // read in data
         string title;
         int year;
         ss.ignore();
         getline(ss, title, ',');
         ss >> year;
         
         cout << "Comedy Movie with title " << title;
         cout << " made in the year " << year << endl;
      }
      case 'D': {
         // read in data
         string director, title;
         ss.ignore();
         getline(ss, director, ',');   // stock of movie
         ss.ignore();
         getline(ss, title, ',');   // stock of movie
         
         cout << "Drama Movie with title " << title;
         cout << " and director " << director << endl;
      }
   }
}


