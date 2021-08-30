#include "stack.h"
// note -- destructor, copy constructor, clear, isFull are not included
//      -- subject to typos

//------------------------------ constructor ---------------------------------
Stack::Stack() {
   top = NULL;
}

//------------------------------ isEmpty -------------------------------------
// check to see if stack is empty
bool Stack::isEmpty() const {
   return (top == NULL);
}

//--------------------------------- push -------------------------------------
// push (insert) item onto top of stack
bool Stack::push(NodeData* dataptr) {

   Node* nodeptr = new Node;
   assert(nodeptr != NULL);
   nodeptr->data = dataptr;

   nodeptr->next = top;                            // link in at stack top
   top = nodeptr;
   return true;
}

//---------------------------------- pop -------------------------------------
// pop (remove) item off top of stack
NodeData* Stack::pop() {
   if (isEmpty())
      return nullptr;
   else {
      NodeData* dataptr = top->data;
      Node* nodeptr = top;
      top = top->next;
      delete nodeptr;
      nodeptr = NULL;
      return dataptr;
   }
}

//---------------------------------- peek ------------------------------------
// return item at top of stack
bool Stack::peek(NodeData*& dataptr) const {
   if (isEmpty())
      return false;
   else {
      dataptr = top->data;
      return true;
   }
}

//----------------------------------  <<  ------------------------------------
// Overloaded output operator for class Stack
ostream& operator<<(ostream& output, const Stack& theStack) {
   
   if (theStack.isEmpty())
       output << "There is nothing in the requested stack." << endl;
   else {
      Node* current = theStack.top;
      while (current != NULL) {
         output << *current->data << endl;
         current = current->next;
      }
      output << endl;
   }
   return output;
}
