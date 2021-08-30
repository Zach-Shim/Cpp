//---------------------------------------------------------------------------
// driver.cpp
//---------------------------------------------------------------------------
// This code tests the basic functionality of the classes to perform
// Dijkstra's algorihms and depth-first search for CSS 343 program 3.
// It is not meant to exhaustively test the class.
//
// Assumptions:
//   -- students can follow the directions to interface with this file
//   -- text files "data31.txt" and "data32.txt" are formatted as described
//   -- Data file data3uwb provides an additional data set for part 1;
//      it must be edited, as it starts with a description how to use it
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
using namespace std;

int main() {
   
   // part 1 -----------------------------------------------------------------
   ifstream infile1("data31.txt");
   if (!infile1) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // for each graph, find the shortest path from every node to all other nodes
   for (;;){
      // test constructor
      GraphM G;
      
      // test buildgraph()
      G.buildGraph(infile1);
      if (infile1.eof()) {
         break;
      }
      
      // test insert edges
      bool success = G.insertEdge(2, 5, 10);
      cout << "Edge 2 - 5 was "
           << (success ? "inserted" : "not inserted") << endl;
      success = G.insertEdge(4, 2, 12);
      cout << "Edge 4 - 2 was "
           << (success ? "inserted" : "not inserted") << endl;
      success = G.insertEdge(5, 1, 4);
      cout << "Edge 5 - 1 was "
           << (success ? "inserted" : "not inserted") << endl;
      success = G.insertEdge(2, 1, 10);
      cout << "Edge 2 - 1 was "
           << (success ? "inserted" : "not inserted") << endl;
      success = G.insertEdge(6, 20, 1200);
      cout << "Edge 6 - 20 was "
           << (success ? "inserted" : "not inserted") << endl;
      success = G.insertEdge(4, 5, 20);
      cout << "Edge 4 - 5 was "
           << (success ? "inserted" : "not inserted") << endl;
      
      // test remove edges
      bool test = G.removeEdge(5, 2);
      cout << "Edge 5 - 2 was " << (test ? "removed" : "not removed") << endl;
      test = G.removeEdge(2, 1);
      cout << "Edge 2 - 1 was " << (test ? "removed" : "not removed") << endl;
      test = G.removeEdge(53, 4);
      cout << "Edge 53 - 4 was " << (test ? "removed" : "not removed") << endl;
      cout << endl;
      
      // test Dijkstra's algorithm
      G.findShortestPath();
      
      // test display
      G.displayAll();               // display shortest distance, path to cout
      G.display(3, 4);              // display path from node 3 to 1 to cout
      G.display(1, 3);
      G.display(4, 1);
      G.display(1200, 5);
   }
   
   // part 2 -----------------------------------------------------------------
   ifstream infile2("dataUWB.txt");
   if (!infile2) {
      cout << "File could not be opened." << endl;
      return 1;
   }
   
   // for each graph, find the shortest path from every node to all other nodes
   for (;;){
      GraphM GM;
      GM.buildGraph(infile2);
      if (infile2.eof())
         break;
      GM.findShortestPath();
      GM.displayAll();              // display shortest distance, path to cout
      GM.display(1, 15);            // display path from node 1 to 15 to cout
      GM.display(6, 90);
      GM.display(3, 5);
   }

   // part 3 -----------------------------------------------------------------
   ifstream infile3("data32.txt");
   if (!infile3) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // for each graph, find the depth-first search ordering
   for (;;) {
      GraphL GL;
      GL.buildGraph(infile3);
      if (infile3.eof())
         break;
      GL.displayGraph();
      GL.depthFirstSearch();  // find and display depth-first ordering to cout
   }
   
   cout << endl;
   return 0;
 
}
