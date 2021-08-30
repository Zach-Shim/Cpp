// ------------------------------ graphl.cpp ---------------------------------

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


#include "graphl.h"

//--------------------------- Default Constructor ----------------------------
// Description: gives class data default values
//
// Preconditions:    none
//
// Postconditions:   entire adjList array is null
//                   size of adjList is 0
//
GraphL::GraphL() {
   for(int i = 1; i <= MAX_NODES; i++) {
      adjList[i] = nullptr;                  // make entire adjList array null
   }
   size = 0;
}

//-------------------------------- destructor --------------------------------
// Description: every node and every node's edges memory is freed
//              destructor deletes Graphnode (vertex) data, makeEmpty deletes
//              EdgeNode (edge) data
//
// Preconditions:    none
//
// Postconditions:   all dynamic memory (GraphNode and EdgeNode object) data
//                   has been freed
//                   all adjList pointers are nullptr
//
GraphL::~GraphL() {
   for(int i = 1; i <= size; i++) {
      makeEmpty(adjList[i]->edgeHead);       // delete edges
      delete adjList[i]->data;               // delete vertex data
      adjList[i]->data = nullptr;
      delete adjList[i];                     // delete vertex
      adjList[i] = nullptr;
   }
}
   
//--------------------------------- makeEmpty --------------------------------
// Description: recursive helper for destructor to delete the edges for each
//              vertex node
//
// Preconditions:    EdgeNode*& current is pointing to a GraphNode's (vertex)
//                   edgeHead
//
// Postconditions:   all edge nodes for a vertex are deleted
//
void GraphL::makeEmpty(EdgeNode*& current) {
   if(current == nullptr) {
      return;
   }
   makeEmpty(current->nextEdge);    // move to the bottom of the linked-list
   delete current;                  // free memory
   current = nullptr;               // clean up pointer
}

//------------------------------ buildGraph ----------------------------------
// Description: builds up graph node information and adjacency list of edges
//              between each node reading from a data file.
//
// Preconditions:    infile is an opened stream connected to a text file
//
// Postconditions:   internal data: size, NodeData data, adjList Graphnodes,
//                   and EdgeNodes are all initialized
//
void GraphL::buildGraph(ifstream & infile) {
   // find the number of nodes in the graph
   char endLine;
   infile >> size;
   infile.get(endLine);            // dispose of the end line character ('\n')
   
   // set the location for all vertices in Graphnode adj list
   for(int i = 1; i <= size; i++) {
      adjList[i] = new GraphNode;
      adjList[i]->edgeHead = nullptr;
      adjList[i]->data = new NodeData;
      adjList[i]->data->setData(infile);
      adjList[i]->visited = false;
   }
   
   // set all the edges for each edge in the GraphNode adj list
   int fromNode, toNode;
   while(infile >> fromNode >> toNode) {
      if(fromNode == 0 || toNode == 0) {
         break;
      }
      else {
         // attach the new edge to the vertex as the edge head
         EdgeNode* newEdge = new EdgeNode;
         newEdge->adjGraphNode = toNode;
         newEdge->nextEdge = adjList[fromNode]->edgeHead;
         adjList[fromNode]->edgeHead = newEdge;
      }
   }
}

//-------------------------- depthFirstSearch --------------------------------
// Description: uses the DPS algorithm to display the graph
//
// Preconditions:    none
//
// Postconditions:   all nodes in the Graph are displayed in depth first order
//
void GraphL::depthFirstSearch() {
   
   cout << "Depth-first ordering: ";
   for (int i = 1; i <= size; i++) {       // loop checks each vertex's edges
      if (adjList[i] != nullptr && !adjList[i]->visited) {
         dfsHelper(i);                     // if node has not been visited
      }
   }
   cout << endl;
}
         
//------------------------------- dfsHelper ----------------------------------
// Description: uses the DPS algorithm to display the graph
//              all adjacent nodes are marked visited until reaching a nullptr
//
// Preconditions:    int vertex is the number of a node in the adj. list that
//                   has not been visited
//
// Postconditions:   all non visited adjacent nodes are marked visited
//                   (adjList[v].visited = true)
//                   all nodes in the graph are displayed
//
void GraphL::dfsHelper(int vertex) {
   adjList[vertex]->visited = true;    // mark vertex as visted
   cout << vertex << " ";              // Output vertices in depth-first order
   EdgeNode* current = adjList[vertex]->edgeHead;
   
   while (current != NULL) {
      if (!adjList[current->adjGraphNode]->visited) {
         dfsHelper(current->adjGraphNode);   // go to next non-visited vertex
      }
      current = current->nextEdge;     // if node edge is already visited, next
   }
}

//----------------------------- displayGraph ---------------------------------
// Description:  uses couts to display the shortest distance with path info
//               between the fromNode to toNode.
//
// Preconditions:    none
//
// Postconditions:   all vertex and edge information is displayed
//
void GraphL::displayGraph() {
   // loop through each vertex in array, displayEdges shows edges for each v
   cout << "\nGraph:" << endl;
   for(int i = 1; i <= size; i++) {
      cout << "Node " << i << "   " << *adjList[i]->data << endl;
      displayEdges(i, adjList[i]->edgeHead);
      cout << endl;
   }
}

//----------------------------- displayEdges ---------------------------------
// Description:  recursively displays all edges for a vertex in preorder
//
// Preconditions:    Edgenode* current is pointing to a GraphNode object
//                   (vertex) in adjList
//
// Postconditions:   all edges for a vertex are displayed
//
void GraphL::displayEdges(int v, EdgeNode* current) {
   if(current == nullptr) {
      return;
   }
   
   // recursively print out all edges of the current vertex
   cout << " edge " << v << " " << current->adjGraphNode << endl;
   displayEdges(v, current->nextEdge);
}
