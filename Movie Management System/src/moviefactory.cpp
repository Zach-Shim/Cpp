#include "moviefactory.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
MovieFactory::MovieFactory() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
MovieFactory::~MovieFactory() {}

//------------------------------ createMovie ----------------------------------
// Description:     Creates a Movie object
//                  Used by the Store class to create a new Movie type
//
// Preconditions:   string data is information about a movie and is correctly
//                  formatted
//                  Movie*& newMovie is null
//
// Postconditions:  returns a pointer to a Movie object
//                  (i.e. Classic, Comedy, Drama)
//
Movie* MovieFactory::createMovie(string movieData) {
   stringstream ss(movieData);
   char movieType;
   
   // read in movie type
   ss >> movieType;
   ss.ignore();
   
   // find movie type
   Movie* newMovie = nullptr;
   switch(movieType) {
      case 'F':
         newMovie = new Comedy(movieType);
         break;
      case 'C':
         newMovie = new Classic(movieType);
         break;
      case 'D':
         newMovie = new Drama(movieType);
         break;
      default:
         cout << "ERROR: Movie Not Added To Inventory: ";
         cout << "Invalid movie type '" << movieType << "'" << endl;
         return nullptr;
   }

   bool success = newMovie->setData(ss);
   if(!success) return nullptr;
   
   return newMovie;
}
