#include "queue.h"

//------------------------------ constructor ---------------------------------
Queue::Queue() {
   front = rear = nullptr;
}

//------------------------------ destructor ----------------------------------
Queue::~Queue() {
   makeEmpty();
}

//------------------------------ makeEmpty -----------------------------------
// empties the current object
void Queue::makeEmpty() {
   makeEmptyHelper(front);
}
// passes in the rear
void Queue::makeEmptyHelper(Node*& current) {
   if(current == nullptr) {
      return;
   }

   makeEmptyHelper(current->next);
   delete current->data;
   current->data = nullptr;
   delete current;
   current = nullptr;
}

//------------------------------ isEmpty -------------------------------------
// check to see if queue is empty
bool Queue::isEmpty() const {
   return (front == nullptr);
}

//------------------------------ enqueue -------------------------------------
// insert item into rear of queue
bool Queue::enqueue(Transaction* dataptr) {

   Node* nodeptr = new Node;
   nodeptr->data = dataptr;
   nodeptr->next = nullptr;

   // link at front if empty, otherwise at the rear
   if (isEmpty())
      front = nodeptr;
   else
      rear->next = nodeptr;
   rear = nodeptr;                                // either way, rear is set
   return true;
}

//---------------------------------- dequeue ---------------------------------
// remove item from front of queue
bool Queue::dequeue(Transaction*& dataptr) {
   if (isEmpty())
      return false;
   
   dataptr = front->data;
   Node* nodeptr = front;
   front = front->next;
   if (isEmpty())
      rear = nullptr;                   // if it's the last node in list
   delete nodeptr;
   nodeptr = nullptr;
   return true;
}

//---------------------------------- peek ------------------------------------
// return item at front of queue
bool Queue::peek(Transaction*& dataptr) const {
   if (isEmpty())
      return false;
   
   dataptr = front->data;
   return true;
}
