// --------------------------------- drama.h ----------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Drama Class: Drama is a specific genre of a Movie

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Drama is a subclass of Movie (derived from class Movie)

//

#ifndef DRAMA_H
#define DRAMA_H

#include <iostream>
#include "movie.h"
using namespace std;

class Drama : public Movie {
public:
   Drama();                        // default constructor
   Drama(char);                    // constructor
   virtual ~Drama();               // destructor
   Drama(const Movie&);            // copy constructor
   
   virtual bool setData(stringstream&);
   
   // overloaded operators
   virtual Drama& operator=(const Movie&);
   virtual bool operator<(const Movie&) const;
   virtual bool operator>(const Movie&) const;
   virtual bool operator==(const Movie&) const;
   virtual bool operator!=(const Movie&) const;
   
private:
   void copy(const Movie&);    // copy constructor and operator= helper
};
#endif
