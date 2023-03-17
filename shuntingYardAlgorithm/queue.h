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

    //empty (noun) stack
    Queue();

  
    //empty (verb) stack
    ~Queue();

    //puts a T on tail
    void enqueue(T);

    //return the head T
    T peak();

    //return the head T and removes it
    T dequeue();

    //returns you the size of the queue
    int getSize();


  private:

    Node<T>* head;  
    Node<T>* tail;  
    int size;

};

#endif
