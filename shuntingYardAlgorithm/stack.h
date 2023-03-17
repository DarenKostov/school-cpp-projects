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

    //empty stack
    Stack();

    //puts a T on the top
    void push(T);

    //return the top T
    T peak();

    //return the top T and removes it
    T pop();


  private:

    Node<T>* head;  

};

#endif
