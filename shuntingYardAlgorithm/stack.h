/*
  Daren Kostov
  stack data structure
*/

#include "node.h"

#ifndef STACK
#define STACk



template<class T>
class Stack{

  public:

    //empty (noun) stack
    Stack();

    //empty (verb) stack
    ~Stack();
  
    //puts a T on the top
    void push(T);

    //return the top T
    T peek();

    //return the top T and removes it
    T pop();

    //gives you the size of the stack
    int getSize();

  private:

    Node<T>* head;
    int size;

};

#endif
