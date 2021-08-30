// --------------------------------- comedy.h ---------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Comedy Class: Comedy is a specific genre of a Movie

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Comedy is a subclass of Movie (derived from class Movie)

//

#ifndef COMEDY_H
#define COMEDY_H

#include <iostream>
#include "movie.h"
using namespace std;

class Comedy : public Movie {
public:
   Comedy();                        // default constructor
   Comedy(char);                    // constructor
   virtual ~Comedy();               // destructor
   Comedy(const Movie&);            // copy constructor
   
   virtual bool setData(stringstream&);
   
   // overloaded operators
   virtual Comedy& operator=(const Movie&);
   virtual bool operator<(const Movie&) const;
   virtual bool operator>(const Movie&) const;
   virtual bool operator==(const Movie&) const;
   virtual bool operator!=(const Movie&) const;

private:
   void copy(const Movie&);    // copy constructor and operator= helper
};
#endif
