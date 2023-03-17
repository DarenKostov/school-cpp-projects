/*
  Daren Kostov
  queue data structure
*/

#include "node.h"

#ifndef QUEUE
#define QUEUE



template<class T>
class Queue{

  public:

    //empty stack
    Queue();

  
    // //empty stack
    // ~Queue();

    //puts a T on tail
    void enqueue(T);

    //return the head T
    T peak();

    //return the head T and removes it
    T dequeue();

  private:

    Node<T>* head;  
    Node<T>* tail;  

};

#endif
