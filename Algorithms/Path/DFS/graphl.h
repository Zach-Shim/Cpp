// -------------------------------- graphl.h ---------------------------------

// Zach Shim
// CSS 343
// Created: July 20th, 2020
// Last Modified: July 30th, 2020

// ---------------------------------------------------------------------------

// GraphL class: Algorithm that traverses through nodes in a pre-order fashion
//               You visit a vertex's non-visited edges, then visit that
//               vertex's next non-visted edge and so on until reaching a
//               stopping point. This is performed for all vertices.

// ---------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

//   -- data is not sorted when read in by buildGraph()
//   -- EdgeNodes are always inserted at the beginning of an adjacency list
//      for a GraphNode.
//    - The ouput of edges for each node will, thus, be in the reverse order
//      in which they are listed in the input file
//   -- A zero in the text file for the first integer signifies the end of
//      the data for that one graph.
//   -- Graphs are implmeneted in an adjacency list (array of lists)
//   -- GraphNode* adjList is an array holding all vertex nodes in a graph
//    - the field edgeHead points to the head of a list of EdgeNode
//      (which stores edge info)
//    - visited is used to mark whether the node has been visited
//    - data is a pointer to NodeData that has the information about this
//      GraphNode
//   -- struct EdgeNode holds all edges for vertices
//    - edges are implmeneted in a linked list
//   -- structs are used for GraphNode and EdgeNode for simplicity

// ---------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H

#include <iostream>
#include <climits>
#include "nodedata.h"
using namespace std;

// each graph can have at most 100 nodes
const int MAX_NODES = 100;
   
class GraphL {
public:
   GraphL();            // default constructor
   ~GraphL();           // destructor
   
   void buildGraph(ifstream &);  // builds graph; takes data from txt file
   void displayGraph();          // displays the vertices and edges in a graph
   void depthFirstSearch();      // uses DFS algorithm to traverse graph
   
private:
   struct EdgeNode;         // forward references for the compiler

   struct GraphNode {
     EdgeNode* edgeHead;    // head of the list of edges
     NodeData* data;        // data information about each node
     bool visited;
   };
   
   GraphNode* adjList[MAX_NODES];

   struct EdgeNode {
     int adjGraphNode;      // subscript of the adjacent graph node
     EdgeNode* nextEdge;    // points to the next edge in the edge list
   };
   
   int size;       // number of vertices in a graph
   
   /* utility functions */
   
   // recursive helper for depthFirstSeach
   void dfsHelper(int);
   
   // recursive helper for the destructor
   void makeEmpty(EdgeNode*&);
   
   // recursive helper for display to show all edges for each vertex
   void displayEdges(int, EdgeNode*);
};

#endif
