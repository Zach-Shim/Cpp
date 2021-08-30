#include "prefix.h"

//-----------------------------------------------------------------------------
// constructor
// initialize the array to the empty string,
// char arrays end with '\0' (null character) so operator<< works properly

Prefix::Prefix() {
   expr[0] = '\0';
}


//-----------------------------------------------------------------------------
// setPrefix
// Set a prefix expression made of single digit operands, operators +,-,*,/
// and no blanks or tabs contained in a file. The expression is valid in
// that each valid operator has two valid operands.

void Prefix::setPrefix(ifstream& infile) {
    infile >> expr;
}


//-----------------------------------------------------------------------------
// evaluatePrefix
// Evaluate a prefix expr made of single digit operands and operators +,-,*,/
// Return the answer (integer arithmetic).

int Prefix::evaluatePrefix() const {
    if (expr[0] == '\0')                          // empty string
        return 0;

    int index = -1;                               // to walk through expr
    return evaluatePrefixHelper(index);
}


//-----------------------------------------------------------------------------
// evaluatePrefixHelper
// Recursively calculates the answer for the given prefix expr
// Return the answer (integer arithmetic)

int Prefix::evaluatePrefixHelper(int& index) const {
   char symbol = expr[++index];
   int n = symbol - '0';            // converts a char number to an actual int
   
   // if is has reached the end of the c-string/char array/expression
   if(expr[index] == '\0'){
      return 0;
   }
   
   // if the symbol is an operand/number
   if(n >= 0){
      return n;
   }
   // if the symbol is an operator
   else if(n < 0) {
      // evaluate expression (using next two operands) depending on operator
      switch(symbol) {
         case '+':
            return evaluatePrefixHelper(index) + evaluatePrefixHelper(index);
            break;
         case '-':
            return evaluatePrefixHelper(index) - evaluatePrefixHelper(index);
            break;
         case '/':
            return evaluatePrefixHelper(index) / evaluatePrefixHelper(index);
            break;
         case '*':
            return evaluatePrefixHelper(index) * evaluatePrefixHelper(index);
            break;
      }
   }
   return 0;
}


//-----------------------------------------------------------------------------
// outputAsPostfix, toPostfix
// Convert prefix expression to postfix and output

void Prefix::outputAsInfix(ostream& out) const {
    if (expr[0] == '\0') return;
    int index = -1;              // to walk through expr
    int count = -1;              // to build infix array
    char infix[MAXSIZE];
    toInfix(index, infix, count);
    infix[++count] = '\0';
    out << infix;
}


//-----------------------------------------------------------------------------
// toPostfix
// Recursively converts a prefix expression to postfix expression

void Prefix::toInfix(int& index, char infix[], int& count) const {
   char symbol = expr[++index];
   int n = symbol - '0';            // converts char number to an actual int
   
   // base case
   // if the end of the c-string/char array/expression has been reached
   if(symbol == '\0') {
      return;
   }
   
   // if the symbol is an operand/number
   if(n >= 0) {
      infix[++count] = expr[index];      // fill postfix array
   }
   // if the symbol is an operator
   else if(n < 0) {
      infix[++count] = '(';
      toInfix(index, infix, count);    // find first operand
      infix[++count] = symbol;           // place operator after two operands
      toInfix(index, infix, count);    // find second operand
      infix[++count] = ')';
   }
}

//-----------------------------------------------------------------------------
// outputAsPostfix, toPostfix
// Convert prefix expression to postfix and output

void Prefix::outputAsPostfix(ostream& out) const {
    if (expr[0] == '\0')                      // empty string
        return;

    int index = -1;                           // to walk through expr
    int count = -1;                           // used to build postfix array
    char postfix[MAXSIZE+1];                  // holds postfix expression
    toPostfix(index, postfix, count);
    postfix[++count] = '\0';
    out << postfix;
}


//-----------------------------------------------------------------------------
// toPostfix
// Recursively converts a prefix expression to postfix expression

void Prefix::toPostfix(int& index, char postfix[], int& count) const {
   char symbol = expr[++index];
   int n = symbol - '0';            // converts char number to an actual int
   
   // base case
   // if the end of the c-string/char array/expression has been reached
   if(symbol == '\0') {
      return;
   }
   
   // if the symbol is an operand/number
   if(n >= 0) {
      postfix[++count] = expr[index];      // fill postfix array
   }
   // if the symbol is an operator
   else if(n < 0) {
      toPostfix(index, postfix, count);    // find first operand
      toPostfix(index, postfix, count);    // find second operand
      postfix[++count] = symbol;           // place operator after two operands
   }
}


//-----------------------------------------------------------------------------
// operator<<
// display prefix expression as a string (char array)

ostream& operator<<(ostream& output, const Prefix& expression) {
    output << expression.expr;
    return output;
}

