// ------------------------------- classic.h ----------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Classic Class: Classic is a specific genre of a Movie

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Classic is a subclass of Movie (derived from class Movie)

//

#ifndef CLASSIC_H
#define CLASSIC_H

#include <iostream>
#include "movie.h"
using namespace std;

class Classic : public Movie {
public:
   Classic();                        // default constructor
   Classic(char);                     // constructor
   virtual ~Classic();               // destructor
   Classic(const Movie&);            // copy constructor
   
   virtual bool setData(stringstream&);
   
   // setter functions
   bool setMajorActor(string);
   bool setReleaseMonth(int);
   
   // overloaded operators
   virtual Classic& operator=(const Movie&);
   virtual bool operator<(const Movie&) const;
   virtual bool operator>(const Movie&) const;
   virtual bool operator==(const Movie&) const; // tests releaseDate and mActor
   virtual bool operator!=(const Movie&) const;
   virtual bool isEqual(const Movie&) const;    // tests general Movie data
   
   virtual void display() const;
   
private:
   int releaseMonth;
   string majorActor;
   
   void copy(const Movie&);    // copy constructor and operator= helper
};
#endif
