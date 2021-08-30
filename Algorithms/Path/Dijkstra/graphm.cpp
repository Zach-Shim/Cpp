// ------------------------------ graphm.cpp ---------------------------------

// Zach Shim
// CSS 343
// Created: July 20th, 2020
// Last Modified: July 30th, 2020

// ---------------------------------------------------------------------------

// GraphM class: Finds the lowest cost paths from every node to every other
//               node in a graph

// ---------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

//   -- reads a data file and finds the lowest cost paths
//    - assumes the data in the file is correctly formatted and valid
//    - assumes data is given for directed, weighted graph
//   -- Graph is implmeneted as an adjacency matrix
//    - there is one two dimensional array for edges
//    - there is another two dimensional array for shortest path tracking
//   -- TableType is a struct to keep the current shortest distance (and
//      associated path info) known at any point in the algorithm.
//    - T is a 2-dimensional array of structs because we want to work on from
//      all nodes to all other nodes.
//   -- In T and C, index 0 is not used.
//   -- insertEdge does not automatically fix the shortest path in the T
//      adjacency matrix

// ---------------------------------------------------------------------------

#include "graphm.h"

//--------------------------- Default Constructor ----------------------------
// Description: gives default values for TableType struct
//
// Preconditions:    none
//
// Postconditions:   All T[i][j].dist values are set to INFINITY for all edges
//                   inside adjacency graph
//                   T[i][j].visited set to false
//                   T[i][j].path set to zero
//                   All cost matrix values are set to infinity
// NOTE: INT_MAX is used as infinity
//

GraphM::GraphM() {
   // all cost and table adjacency matrix graph values are given base values
   for(int i = 1; i < MAXNODES; i++) {
      for(int j = 1; j < MAXNODES; j++) {
         T[i][j].dist = INT_MAX;
         T[i][j].visited = false;
         T[i][j].path = 0;
         C[i][j] = INT_MAX;
      }
   }
   size = 0;
}

//------------------------------ buildGraph ----------------------------------
// Description: builds up graph node information and adjacency matrix of edges
//              between each node reading from a data file.
//
// Preconditions:    infile is an opened stream connected to a text file
//
// Postconditions:   internal data:
//                       int size
//                       NodeData data
//                       int C[MAXNODES][MAXNODES]
//                   are all initialized with data
//
void GraphM::buildGraph(ifstream & infile) {
   // read in the total number of nodes in the graph from file stream
   char endLine;
   infile >> size;
   infile.get(endLine);       // dispose of the end line character for getline
   
   // fill out locations for NodeData data array; uses NodeData's setData
   for(int i = 1; i <= size; i++) {
      data[i].setData(infile);
   }

   // find the edges between nodes and set the data in the adjacency matrix
   int fromNode, toNode, weight;
   while(infile >> fromNode >> toNode >> weight) {
      bool success = insertEdge(fromNode, toNode, weight);
      if(!success) return;
   }
}

//------------------------------ insertEdge ----------------------------------
// Description: insert an edge into graph between two given nodes
//
// Preconditions:    firstNode and nextNode are both nonnegative integers
//
// Postconditions:   returns true if the edge is inserted into the graph
//                   returns false otherwise
//
// NOTE: insertEdge does not automatically fix the shortest path in the T adj.
//       matrix. If the client would like to perform an insertEdge after a
//       Dijkstra's shortest path algorithm, they would have to recall the
//       Dijakstra function in order to see the new shortest path
//       Example:
//               GraphM G;
//               insert insert inert....
//               G.findShortestPath();
//               G.displayAll();
//               G.removeEdge(2, 5, 10);
//               G.findShortestPath();
//
bool GraphM::insertEdge(int firstNode, int secondNode, int weight) {
   // error check
   if(firstNode <= 0 || firstNode > size) return false;
   if(secondNode <= 0 || secondNode > size) return false;
   if(weight <= 0 || firstNode == secondNode) return false;
   
   // insert edge by placing the weight inside the adjacency matrix
   C[firstNode][secondNode] = weight;
   return true;
}

//------------------------------ removeEdge ----------------------------------
// Description: removes an edge between two given nodes by inserting an
//              infinite value between them
//
// Preconditions:    firstNode and nextNode are both nonnegative integers
//
// Postconditions:   return true if the edge between the two given nodes has
//                   been removed
//                   return false otherwise
//
bool GraphM::removeEdge(int firstNode, int nextNode) {
   return insertEdge(firstNode, nextNode, INT_MAX);
}

//--------------------------- findShortestPath -------------------------------
// Description: find the shortest path between every node to every other node
//              in a graph
//
// Preconditions:    graph C should be intialized with values
//
// Postconditions:   the shortest path from each node to every other node has
//                   been found
//
// NOTE: in the two inner for loops:
//       v = vertex
//       w = edge
//
void GraphM::findShortestPath() {
   // shortest is shortest node from the current vertex; becomes new vertex
   int shortest = 0, smaller = 0;
   
   // calculate the shortest path from source to all other nodes
   for(int source = 1; source <= size; source++) {
      T[source][source].dist = 0;        // vertex's distance from itself is 0
       
       // find adjacent node not visited with shortest distance at this point
       for(int v = 1; v <= size; v++) {
          shortest = closestAdjacentNode(source);   // find closest adj. node
          T[source][shortest].visited = true;       // mark v visited
          
          if(shortest != 0) {
             for(int w = 1; w <= size; w++) {       // for each w adjacent to v
                if (C[shortest][w] < INT_MAX && !T[source][w].visited) {
                   // keep shorter distance of w or (w + v weight)
                   smaller = min(T[source][w].dist,
                                (T[source][shortest].dist + C[shortest][w]));
             
                   // if shortest distance is changed, record path info
                   if(smaller != T[source][w].dist) {
                      T[source][w].path = shortest;
                   }
                   
                   // update edge's distance for shortest path
                   T[source][w].dist = smaller;
                }
             }
          }
       }
   }
}

//-------------------------- closestAdjacentNode -----------------------------
// Description: find the closest adjacent node for a vertex
//
// Preconditions:    none
//
// Postconditions:   return the index of the closest adjacent node
//                   returns 0 if there are no adjacent nodes
//
int GraphM::closestAdjacentNode(int source) {
   int closest = 0, distance = INT_MAX;
   for(int w = 1; w <= size; w++) {
      if(T[source][w].dist < INT_MAX && !T[source][w].visited) {
         // if the distance of an adjacent node is lower, update closest
         if(T[source][w].dist < distance) {
            distance = T[source][w].dist;
            closest = w;
         }
      }
   }
   return closest;
}

//------------------------------- displayAll ---------------------------------
// Description: uses couts to demonstrate that the algorithm works properly
//
// Preconditions:    none
//
// Postconditions:   displays the shortest path between every node to every
//                   other node in the graph
//
void GraphM::displayAll() {
   // display heading
   cout << left << setw(20) << "Description";
   cout << left << setw(12) << "From_node";
   cout << left << setw(12) << "To_node";
   cout << left << setw(12) << "Dijstra's";
   cout << left << setw(12) << "Path" << endl;
   
   // display shortest path between every node to every other node in the graph
   for(int i = 1; i <= size; i++) {
      cout << data[i] << endl;                       // node/vertice name
      
      for(int j = 1; j <= size; j++) {
         if(i != j) {
            cout << right << setw(25) << i;         // from node
            cout << right << setw(11) << j;         // to node
            
            // print dijkstra's path distance value
            if(T[i][j].dist < INT_MAX) {
               cout << right << setw(13) << T[i][j].dist;
            }
            // if there is no path, display nothing ("---" = no path)
            else {
               cout << right << setw(14) << "---" << endl;
               continue;
            }
            
            // display the path from one node to all other nodes
            // Example: 1->2 Path is 1 5 2
            cout << right << setw(8);
            showShortestPath(i, j);
            cout << endl;
         }
      }
   }
   cout << endl;
}

//-------------------------------- display -----------------------------------
// Description:  uses couts to display the shortest distance with path info
//               between the fromNode to toNode.
//
// Preconditions:    fromNode and toNode are valid integers
//
// Postconditions:   the shortest distance from fromNode to toNode is displayed
//
// NOTE: v = fromNode
void GraphM::display(int fromNode, int toNode) {
   // error checking
   if ((fromNode > size || fromNode <= 0) || (toNode > size || toNode <= 0)) {
       cout << right << setw(3) << fromNode << right << setw(5) << toNode;
       cout << right << setw(5) << "---" << endl;
       return;
   }
   
   cout << right << setw(3) << fromNode;       // display from node
   cout << right << setw(5) << toNode;         // display to node
   
   // dijstra's path distance value
   if(T[fromNode][toNode].dist < INT_MAX) {
      cout << right << setw(5) << T[fromNode][toNode].dist << right << setw(8);
   }
   // if there is no path, display nothing ("---" = no path)
   else {
      cout << right << setw(5) << "---";
      cout << right << setw(5) << endl;
      return;
   }
   
   // display the path from one node to all other nodes
   // Example: 1->2 Path is 1 5 2
   showShortestPath(fromNode, toNode);
   cout << endl;
   showPathLocations(fromNode, toNode);
   cout << endl << endl;
}

//---------------------------- showShortestPath ------------------------------
// Description: recursive helper for display and displayAll
//
// Preconditions:    v is a vertex integer and w is an edge integer
//
// Postconditions:   displays the order of nodes in the path from one node
//                   to another
//
void GraphM::showShortestPath(int v, int w) {
   // base case, in case there is no path
   if(v == 0 || w == 0) {
      return;
   }
   // the starting node has been reached
   else if(v == w) {
      cout << w << " ";
      return;
   }
   // travel path from final node to first node, then print path backwards
   // recursively (from first to last node)
   else {
      showShortestPath(v, T[v][w].path);
      cout << w << " ";
   }
}

//---------------------------- showPathLocations -----------------------------
// Description: helper for display
//              prints out the location of nodes on the path from fromNode to
//              toNode
//
// Preconditions:    v is a vertex integer and w is an edge integer
//
// Postconditions:   displays the location of nodes in the path from one node
//                   to another
//
void GraphM::showPathLocations(int v, int w) {
   // base case, in case there is no path
   if(v == 0 || w == 0) {
      return;
   }
   // the starting node has been reached
   else if(v == w) {
      cout << data[w] << endl;
      return;
   }
   // travel path from final node to first node, then print path backwards
   // recursively (from first to last node)
   else {
      showPathLocations(v, T[v][w].path);
      cout << data[w] << endl;
   }
}
