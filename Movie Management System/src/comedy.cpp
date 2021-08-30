#include "comedy.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
Comedy::Comedy() {}

//-----------------------------  constructor ----------------------------------
// Description:     intentionally left empty
Comedy::Comedy(char movieType) {
   type = movieType;
}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
Comedy::~Comedy() {}

//----------------------------- copy constructor ------------------------------
// Description:     deep copies a Comedy into *this
//
// Preconditions:   Comedy& right is a Comedy with initialized data
//
// Postconditions:  *this is a copy of Comedy& right
//
Comedy::Comedy(const Movie& right) {
   copy(right);
}

//------------------------------- operator= -----------------------------------
// Description:     deep copies a Comedy into *this
//
// Preconditions:   Comedy& right is a Comedy with initialized data
//
// Postconditions:  *this is a copy of Comedy& right
//
Comedy& Comedy::operator=(const Movie& right) {
   if(this != &right) {
      copy(right);
   }
   return *this;
}

//--------------------------------- copy --------------------------------------
// Description:     deep copies a Comedy into *this
//
// Preconditions:   Comedy& right is a Comedy with initialized data
//
// Postconditions:  *this is a copy of Comedy& right
//
void Comedy::copy(const Movie& right) {
   const Comedy& rightMovie = static_cast<const Comedy &>(right);
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
bool Comedy::setData(stringstream& ss) {
   return Movie::setData(ss);
}

//------------------------------- operator< -----------------------------------
// Description:     Tests the value of two Movie objects
//                  Compares by title, then year it released
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's title and year is less than
//                  Movie& right
//                  return false otherwise
//
bool Comedy::operator<(const Movie& right) const {
   const Comedy& rightMovie = static_cast<const Comedy &>(right);
   // compare titles of Movies
   if(title < rightMovie.title) {
      return true;
   }
   else if (title > rightMovie.title) {
      return false;
   }
   
   // if two Movie titles are equal, then compare years
   if(year < rightMovie.year) {
      return true;
   }
   else if (year > rightMovie.year) {
      return false;
   }
   
   return false;     // both titles and dates are equal
}

//------------------------------- operator> -----------------------------------
// Description:     Tests the value of two Movie objects
//                  Compares by title, then year it released
//                  Utilizes already defined operator<
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's title and year is greater than
//                  Movie& right
//                  return false otherwise
//
bool Comedy::operator>(const Movie& right) const {
   const Comedy& rightMovie = static_cast<const Comedy &>(right);
   return !(*this < rightMovie) && (*this != rightMovie);
}

//------------------------------- operator== ----------------------------------
// Description:     Tests the equality of two Movie objects
//                  Compares by title, then year it released
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's title and year is equal to
//                  Movie& right
//                  return false otherwise
//
bool Comedy::operator==(const Movie& right) const {
   const Comedy& rightMovie = static_cast<const Comedy &>(right);
   return (title == rightMovie.title) && (year == rightMovie.year);
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
bool Comedy::operator!=(const Movie& right) const {
   return !(*this == right);
}
