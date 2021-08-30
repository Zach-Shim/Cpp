#ifndef PREFIX_H
#define PREFIX_H
#include <iostream>
#include <fstream>
using namespace std;

//-----------------------------------------------------------------------------
// class Prefix
//
// ADT Prefix: Prefix expressions are made up of an operator followed by 2
//             operands and each of the operands is itself a prefix expression.
//
// Implmentaion and Assumtions:
//    -- A prefix expression is implemented as a c-string
//    -- Default constructors initializes an empty string
//    -- The file setPrefix reads from holds only integers and operators
//    -- In the data file, there is one prefix expression per line
//    -- evaluatePrefix uses a helper function to solve a prefix expression
//       recursively
//    -- outputAsPostfix uses a helper function to convert a prefix expression
//       to a postfix recursively then prints the result
//    -- Each expression is a validly formatted prefix expression
//    -- Operands consist of just one digit
//    -- Operators are either + ,- , *, /
//    -- Uses integer arithmetic (answer is an int)
//    -- There are no negative numbers in a prefix expression
//-----------------------------------------------------------------------------

int const MAXSIZE = 100;      // maximum size for an integer expression

class Prefix {
    friend ostream& operator<<(ostream&, const Prefix&);

public:
   // default constructor
   Prefix();
   // reads a prefix expr from a data txt file
   void setPrefix(ifstream& infile);
   // evaluates a prefix expression
   int evaluatePrefix() const;
   // converts and outputs a prefix expression as infix
   void outputAsInfix(ostream&) const;
   // converts and outputs a prefix expression as postfix
   void outputAsPostfix(ostream&) const;

private:
   // char array to hold integer expresssion
   char expr[MAXSIZE+1];
   // helps the function evaluatePrefix calculate a prefix expression
   int evaluatePrefixHelper(int&) const;
   // helps the function outputAsPostfix convert a prefix expression to infix
   void toInfix(int&, char [], int&) const;
   // helps the function outputAsPostfix convert a prefix expression to postfix
   void toPostfix(int&, char [], int&) const;
};

#endif
