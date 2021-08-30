#include <iostream>
#include <fstream>
#include "store.h"
using namespace std;

int main() {
   ifstream infile("data4movies.txt");
   if(!infile) {
      cout << "invalid file" << endl;
      return 1;
   }
   
   ifstream infile2("data4customers.txt");
   if(!infile2) {
      cout << "invalid file" << endl;
      return 1;
   }
   
   ifstream infile3("data4commands.txt");
   if(!infile3) {
      cout << "invalid file" << endl;
      return 1;
   }
   
   Store movieStore;
   movieStore.buildMovies(infile);
   movieStore.buildCustomers(infile2);
   movieStore.processTransactions(infile3);
   return 0;
}
