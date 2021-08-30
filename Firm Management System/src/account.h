#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------------
// Account ADT: Holds one of ten possible accounts for a Client
//
// Imlementation and Assumptions:
//   -- Has two data members, baseValue, to store the beginning balance of the
//      day; and currentValue, to store the current and final value
//   -- Client calls account class to withdraw or deposit funds from current
//      account
//   -- Client can get the current or base values
// ----------------------------------------------------------------------------

class Account {

public:
   Account();                      // default constructor
   ~Account();                     // destructor
   
   bool setData(int, int);         // set account type & base and current value
   
   bool deposit(int);              // deposit money
   int withdraw(int);              // withdraw money
   
   string getType() const;
   int getCurrent() const;         // get current value of account
   int getBase() const;            // get base value
   
private:
   string type;                    // name of account
   int baseValue;                  // starting balance
   int currentValue;               // closing balance
};

#endif
