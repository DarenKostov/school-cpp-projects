// Tej Hiremath
// This is the node.h file for part 1 of the linked lists assignments.
// 1/13/23


#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "student.h"

using namespace std;

class Node{
 public:
  Node(Student*);
  ~Node();

  Student* getStudent();
  void setNext(Node* newnext);
  Node* getNext();
 private:
  Student* student;
  Node* next;
};

#endif
