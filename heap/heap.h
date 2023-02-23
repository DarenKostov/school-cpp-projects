/*

  Daren Kostov
  
  Heap- a data structure involves binary trees or something like that

*/

#ifndef HEAP
#define HEAP

#include "text.h"

template<class T>
class Heap{

  public:

    //empty constructor, make sure the type can be be compared with the operator <
    Heap();
  
    //adds an element to the heap
    void add(T);
    
    //removes the root
    void removeRoot();

    //removes every element
    void removeAll();

    //displayes the entire heap
    void display();

  

  private:

  //where the data is stored
  T** data;

  //where should we add an elemnt if we were to add an element
  int newSpot=0;

  //gets the right child of parent index
  int getRightChild(int);
  
  //gets the left child of parent index
  int getLeftChild(int);

  //gets the parent of child index
  int getParent(int);

  //determines weather this elemtn exists or not
  bool doesItExist(int);

  //displayes the children of a given index also specify at which level that index is
  //and weather we are displaying the right(1) or left(0) branch
  void display(int, int, bool, Text);
  void display(int, int);
  
};

#endif


