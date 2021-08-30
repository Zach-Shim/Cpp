#include "movie.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
Movie::Movie() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
Movie::~Movie(){}

//----------------------------- copy constructor ------------------------------
// Description:     deep copies a Movie into *this
//
// Preconditions:   Movie& right is a Movie with initialized data
//
// Postconditions:  *this is a copy of Movie& right
//
Movie::Movie(const Movie& right) {
   copy(right);
}

//------------------------------- operator= -----------------------------------
// Description:     deep copies a Movie into *this
//
// Preconditions:   Movie& right is a Movie with initialized data
//
// Postconditions:  *this is a copy of Movie& right
//
Movie& Movie::operator=(const Movie& right) {
   if(this != &right) {
      copy(right);
   }
   return *this;
}

//--------------------------------- copy --------------------------------------
// Description:     deep copies a Movie into *this
//
// Preconditions:   Movie& right is a Movie with initialized data
//
// Postconditions:  *this is a copy of Movie& right
//
void Movie::copy(const Movie& right) {
   director = right.director;
   title = right.title;
   type = right.type;
   stock = right.stock;
   year = right.year;
   return;
}

//--------------------------------- setData -----------------------------------
// Description:     Sets the data members of a Movie
//
// Preconditions:   string data holds information about a Movie
//
// Postconditions:  return true if valid data was initailized to data members
//                  return false otherwise
//
bool Movie::setData(stringstream& ss) {
   ss >> stock;
   ss.ignore();
   
   ss.ignore();
   getline(ss, director, ',');   // movie director
   
   ss.ignore();
   getline(ss, title, ',');      // movie title
   
   ss >> year;
   
   return true;
}
 
//-------------------------------- addStock -----------------------------------
// Description:     Sets the current Movie's stock
//
// Preconditions:   none
//
// Postconditions:  stock is increased by 1
//
bool Movie::addStock() {
   stock += 1;
   return true;
}
//------------------------------- removeStock ---------------------------------
// Description:     Sets the current Movie's stock
//
// Preconditions:   none
//
// Postconditions:  stock is decreased by 1
//
bool Movie::removeStock() {
   if((stock - 1) < 0) {      // if this movie is out of stock, return false
      return false;
   }
   stock -= 1;                // if there is still stock, remove 1
   return true;
}

//-------------------------------- getType ------------------------------------
// Description:     Returns the current Movie's type
//
// Preconditions:   none
//
// Postconditions:  returns the current Movie's type
//                  (i.e. 'C', 'F', 'D')
//
char Movie::getType() const {
   return type;
}

//------------------------------ getDirector ----------------------------------
// Description:     Returns the current Movie's director
//
// Preconditions:   none
//
// Postconditions:  returns the current Movie's director
//
string Movie::getDirector() const {
   return director;
}

//-------------------------------- getTitle -----------------------------------
// Description:     Returns the current Movie's title
//
// Preconditions:   none
//
// Postconditions:  returns the current Movie's title
//
string Movie::getTitle() const {
   return title;
}

//------------------------------- getStock ------------------------------------
// Description:     Returns the current Movie's stock
//
// Preconditions:   none
//
// Postconditions:  returns the current Movie's stock
//
int Movie::getStock() const {
   return stock;
}

//------------------------------- getTitle ------------------------------------
// Description:     Sets the current Movie's title
//
// Preconditions:   t holds the title of a Movie
//
// Postconditions:  The current Movie's title is set to t
//
bool Movie::setTitle(string t) {
   title = t;
   return true;
}

//------------------------------- setYear -------------------------------------
// Description:     Sets the current Movie's year
//
// Preconditions:   y holds the year of a Movie
//
// Postconditions:  The current Movie's year is set to y
//
bool Movie::setYear(int y) {
   year = y;
   return true;
}

//----------------------------- setDirector -----------------------------------
// Description:     Sets the current Movie's director
//
// Preconditions:   d holds the director of a Movie
//
// Postconditions:  The current Movie's director is set to d
//
bool Movie::setDirector(string d) {
   director = d;
   return true;
}

//-------------------------------- display ------------------------------------
// Description:     Displays Movie data
//
// Preconditions:   none
//
// Postconditions:  Movie data is displayed
//
void Movie::display() const {
   cout << setw(5) << type << setw(8) << 'D';
   cout << setw(34) << title << setw(20) << director;
   cout << setw(7) << year << setw(7) << stock << endl;
}
