#include "account.h"

//---------------------------------------------------------------------------
// Default Constructor
// initializes base value and current value
//
Account::Account() {
   baseValue = currentValue = 0;
}

//---------------------------------------------------------------------------
// Destructor
// No dynamic memory
//
Account::~Account() {}
   
//---------------------------------------------------------------------------
// setData
// initializes the current account's data members
//
bool Account::setData(int index, int value) {
   if(value < 0) {
      cout << "Invalid Request" << endl << "Attempting to initialize account with negative funds" << endl;
      return false;
   }
   
   switch(index) {
      case 0:
         type = "Money Market fund";
         break;
      case 1:
         type = "Prime Money Market fund";
         break;
      case 2:
         type = "Long-Term Bond";
         break;
      case 3:
         type = "Short-Term Bond";
         break;
      case 4:
         type = "500 Index Fund";
         break;
      case 5:
         type = "Capital Value Fund";
         break;
      case 6:
         type = "Growth Equity Fund";
         break;
      case 7:
         type = "Growth Index Fund";
         break;
      case 8:
         type = "Value Fund";
         break;
      case 9:
         type = "Value Stock Index";
         break;
   }
   
   baseValue = value;
   currentValue = value;
   return true;
}

//---------------------------------------------------------------------------
// deposit
// deposits money into current account
// updates current value
//
bool Account::deposit(int amount) {
   currentValue += amount;
   return true;
}

//---------------------------------------------------------------------------
// withdraw
// returns -1 if there is an unknown trasnaction request or insufficient funds
// return partially withdrawn amount if there are insufficient funds
// else, return the amount of money to be withdrawn
//
int Account::withdraw(int amount) {
   int withdrawnAmount;
   if(amount < 0) {
      return -1;
   }
   else if(currentValue - amount < 0) {
      withdrawnAmount = amount - (amount - currentValue);
      currentValue = 0;
      return withdrawnAmount;
   }
   currentValue -= amount;
   return amount;
}

//---------------------------------------------------------------------------
// getType
// returns the name of the current account
//
string Account::getType() const {
   return type;
}

//---------------------------------------------------------------------------
// getCurrent
// returns the current balance of the account
//
int Account::getCurrent() const {
   return currentValue;
}

//---------------------------------------------------------------------------
// getBase
// returns the starting balance of the account
//
int Account::getBase() const {
   return baseValue;
}


