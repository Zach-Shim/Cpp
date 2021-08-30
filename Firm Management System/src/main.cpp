#include <iostream>
#include <fstream>
#include <cstdlib>
#include "firm.h"
#include "client.h"
#include "transaction.h"
#include "account.h"
#include "queue.h"
#include "bstree.h"
using namespace std;

int main() {
   Firm lose;
   ifstream clientsFile("lab5data.txt");
   if(!clientsFile) exit(0);
   lose.addClients(clientsFile);
   clientsFile.close();
   
   ifstream transactionFile("lab5command.txt");
   if(!transactionFile) exit(0);
   lose.addTransactions(transactionFile);
   clientsFile.close();
  
   lose.processTransactions();
   lose.displayReport();
   return 0;
}
