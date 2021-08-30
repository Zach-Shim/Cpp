#include "return.h"
#include "movie.h"
#include "customer.h"
#include "bintree.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
Return::Return() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
Return::~Return(){}

//-------------------------------- setData ------------------------------------
// Description:     Sets the data members of a Borrow Transaction
//
// Preconditions:   infile holds information about a Borrow Transaction
//
// Postconditions:  return true if valid data was initailized to data members
//                  return false otherwise
//
bool Return::setData(stringstream& in_stream) {
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
// Description:     Executes a Return transaction
//
// Preconditions:   Store* shop is pointing to a store object
//
// Postconditions:  return true if Return Transacition was successful
//                  return false otherwise
//
bool Return::executeTransaction(Store* shop) {
   // retrieve client from hashtable databse
   Customer* client = shop->getCustomerInfo().retrieve(clientID);
   if(!client) {
      cout << "ERROR: Return Transaction Failed: ";
      cout << "Customer " << clientID << " Not Found" << endl;
      return false;
   }
   
   // retrieve movie from movie tree database; m is a data member of Return
   Movie* media = findMovie(shop);
   if(!media) {
      cout << "ERROR: Return Transaction Failed: ";
      cout << "Movie Not Found" << endl;
      return false;
   }
   
   bool success;
   success = client->returnMovies(media);
   if(!success) {
      cout << "ERROR: Return Transaction Failed: ";
      cout << "Customer " << clientID << " never borrowed Movie" << endl;
   }
   
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
Movie* Return::findMovie(Store* shop) {
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


//-------------------------------- display ------------------------------------
// Description:     Displays Return data
//
// Preconditions:   none
//
// Postconditions:  Borrow Transaction data is displayed
//
void Return::display() {
   char movieType;
   stringstream ss(movieData);
   ss >> movieType;
   cout << "Returned:  ";
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
