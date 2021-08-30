// Simple Stack
#ifndef STACK_H
#define STACK_H

#include "nodedata.h"

//----------------------------------------------------------------------------
// class Stack
//
// ADT Stack: collection of zero or more items (list) with the restriction that
//            all insertions (push operation) and removals (pop operation) take
//            place at only one end, called the top of the stack (sometimes
//            called pushdown list, or LIFO -- Last In First Out)
//
// Implementation and assumptions:
//    -- Node (linked list implementation) is a struct made of just
//       a NodeData* and a Node*
//    -- Array implementation does not resize when full
//    -- assumes NodeData is a class of actual data
//    -- The push allocates memory for a Node, ptr to the data is passed in.
//    -- doesn't have to be NodeData* in stack, data may be stored directly
//       in the Node or array element, e.g. stack of ints, stack of NodeData
//----------------------------------------------------------------------------

class Stack {
   friend ostream &operator<<(ostream&, const Stack&);

public:
   Stack();                                    // default constructor
   ~Stack();                                   // destructor
   Stack(const Stack&);                        // copy constructor
   void clear();                               // clear out, empty out stack
   bool isEmpty() const;                       // is stack empty?
   bool isFull() const;                        // is stack full?

   // insert item, assume object passed in is valid, return whether successful
   bool push(NodeData*);

   // remove item, parameter is removed item, return whether item is popped
   NodeData* pop();

   // retrieve item, parameter is item at top, return whether item exists
   bool peek(NodeData*&) const;

private:
   // for linked list implementation
   struct Node {
      NodeData* data;
      Node* next;
   };
   Node* top;                                  // pointer to top of stack
   
   int top;                                    // subscript of stack top
};

#endif
