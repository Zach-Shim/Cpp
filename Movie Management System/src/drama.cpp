#include "drama.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Drama::Drama() {}

//-----------------------------  constructor ----------------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Drama::Drama(char movieType) {
   type = movieType;
}

//------------------------------ destructor -----------------------------------
// Description:     intentionally left empty
Drama::~Drama() {}

//----------------------------- copy constructor ------------------------------
// Description:     deep copies a Drama into *this
//
// Preconditions:   Drama& right is a Drama with initialized data
//
// Postconditions:  *this is a copy of Drama& right
//
Drama::Drama(const Movie& right) {
   copy(right);
}

//------------------------------- operator= -----------------------------------
// Description:     deep copies a Drama into *this
//
// Preconditions:   Drama& right is a Drama with initialized data
//
// Postconditions:  *this is a copy of Drama& right
//
Drama& Drama::operator=(const Movie& right) {
   if(this != &right) {
      copy(right);
   }
   return *this;
}

//--------------------------------- copy --------------------------------------
// Description:     deep copies a Drama into *this
//
// Preconditions:   Drama& right is a Drama with initialized data
//
// Postconditions:  *this is a copy of Drama& right
//
void Drama::copy(const Movie& right) {
   const Drama& rightMovie = static_cast<const Drama &>(right);
   director = rightMovie.director;
   title = rightMovie.title;
   type = rightMovie.type;
   stock = rightMovie.stock;
   year = rightMovie.year;
   return;
}

//-------------------------------- setData ------------------------------------
// Description:     Sets the data members of a Movie
//
// Preconditions:   string data holds information about a Movie
//
// Postconditions:  return true if valid data was initailized to data members
//                  return false otherwise
//
bool Drama::setData(stringstream& ss) {
   return Movie::setData(ss);
}

//------------------------------- operator< -----------------------------------
// Description:     Tests the value of two Customer objects
//                  Compares by title, then year it released
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's director and title
//                  values are less than Movie& right
//                  return false otherwise
//
bool Drama::operator<(const Movie& right) const {
   const Drama& rightMovie = static_cast<const Drama &>(right);
   // compare titles of Movies
   if(director < rightMovie.director) {
      return true;
   }
   else if (director > rightMovie.director) {
      return false;
   }
   
   // if two Movie titles are equal, then compare years
   if(title < rightMovie.title) {
      return true;
   }
   else if (title > rightMovie.title) {
      return false;
   }
   
   return false;     // both titles and dates are equal
}

//------------------------------- operator< -----------------------------------
// Description:     Tests the value of two Customer objects
//                  Compares by title, then year it released
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's director and title values are
//                  greater than Movie& right
//                  return false otherwise
//
bool Drama::operator>(const Movie& right) const {
   const Drama& rightMovie = static_cast<const Drama &>(right);
   return !(*this < rightMovie) && (*this != rightMovie);
}

//------------------------------- operator== ----------------------------------
// Description:     Tests the value of two Movie objects
//                  Compares by title, then year it released
//                  Utilizes already defined operator<
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's title and year is equal to
//                  Movie& right values
//                  return false otherwise
//
bool Drama::operator==(const Movie& right) const {
   const Drama& rightMovie = static_cast<const Drama &>(right);
   return (director == rightMovie.director) && (title == rightMovie.title);
}

//------------------------------- operator!= ----------------------------------
// Description:     Tests the equality of two Movie objects
//                  Compares by title, then year it released
//                  Utilizes already defined operator==
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's title and year is not equal to
//                  Movie& right
//                  return false otherwise
//
bool Drama::operator!=(const Movie& right) const {
   return !(*this == right);
}

