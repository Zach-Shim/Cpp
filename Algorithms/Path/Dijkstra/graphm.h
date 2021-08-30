// -------------------------------- graphm.h ---------------------------------

// Zach Shim
// CSS 343
// Created: July 20th, 2020
// Last Modified: July 30th, 2020

// ---------------------------------------------------------------------------

// GraphM class: Dijkstra's shortest path algorithm:
//               Finds the lowest cost paths from every node to every
//               other node in a graph
//

// ---------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

//   -- reads a data file and finds the lowest cost paths
//    - assumes the data in the file is correctly formatted
//    - assumes data is given for directed, weighted graph
//   -- Graph is implmeneted as an adjacency matrix
//    - there is one two dimensional array for edges
//    - there is another two dimensional array for shortest path tracking
//   -- TableType is a struct to keep the current shortest distance (and
//      associated path info) known at any point in the algorithm.
//   -- In T and C, index 0 is not used.
//   -- default (system) destructor is used because there is no dynamic memory
//   -- assumes driver uses bool tester to determine if edge was succesfully
//      inserted or removed

// ---------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include <iomanip>
#include <climits>                  // to compile INT_MAX with linux
#include "nodedata.h"
using namespace std;
 
// each graph can have at most 100 nodes
// Note: in T, index 0 is not used, hence the 101 MAXNODES initialization
const int MAXNODES = 101;

class GraphM {

public:
   GraphM();      // default constructor
   
   void buildGraph(ifstream &);   // builds graph; takes data from txt file
   void findShortestPath();       // find the shortest path

   bool insertEdge(int, int, int);  // insert an edge into graph
   bool removeEdge(int, int);       // remove an edge between two given nodes
   
   void displayAll();         // shows the shortest distance to/from all nodes
   void display(int, int);    // prints out the distance between two nodes
   
private:
   
   struct TableType {

      bool visited;          // whether node has been visited
      int dist;              // shortest distance from source known so far
      int path;              // previous node in path of min dist

   };

   NodeData data[MAXNODES];              // data for graph nodes

   int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix

   int size;                             // number of nodes in the graph

   TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
   
   /* utility functions */
   
   // helper for findShortestPath to find the closest adjacent node
   int closestAdjacentNode(int);
   
   // recursive helper for displayAll and display
   void showShortestPath(int, int);
   
   // recursive helper for display
   void showPathLocations(int, int);
};

#endif
