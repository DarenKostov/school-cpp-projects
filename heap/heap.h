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

    //deconstructor
    ~Heap();
  
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

  //displays the right branch, give it index and prefix
  void displayRight(int, Text);
  
  //displays the left branch, give it index and prefix
  void displayLeft(int, Text);
  
};

#endif


