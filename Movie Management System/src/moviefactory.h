// ------------------------------ moviefactory.h ---------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// MovieFactory Class: Creates Movies based on it's genre

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - createMovie is static because a MovieFactory object does not need to be
//   directly insantiated, only class Store needs access to it to create
//   different types of movies

//

#ifndef MOVIEFACTORY_H
#define MOVIEFACTORY_H

#include <iostream>
#include <sstream>
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"

using namespace std;

class MovieFactory {
public:
    MovieFactory();
    ~MovieFactory();

    static Movie* createMovie(string);
};
#endif
