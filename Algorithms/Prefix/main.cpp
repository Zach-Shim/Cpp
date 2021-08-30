#include "prefix.h"
#include <iostream>
using namespace std;

int main(){
   // declare file object and open the datafile
   ifstream infile("data4.txt");
   if (!infile)  {
      cout << "File could not be opened." << endl;
      return 1;                                          // exit program
   }

   // for each prefix expression, evaluate, print answer, and print as postfix
   cout << "Prefix Expression = Answer" << endl;
   cout << "--------------------------" << endl;
   for (;;) {
      Prefix expr;
      expr.setPrefix(infile);
      // on windows, new line after last line of data; no line on linux
      if (infile.eof())                  // if end of the file has been reached
         break;
      
      cout << expr << " = " << expr.evaluatePrefix();
      
      cout << endl << "       As infix:  ";
      expr.outputAsInfix(cout);        // ouput postfix version of expr
      cout << endl << "       As postfix:  ";
      expr.outputAsPostfix(cout);        // ouput postfix version of expr
      cout << endl << endl;
       
       
   }
   return 0;
}
