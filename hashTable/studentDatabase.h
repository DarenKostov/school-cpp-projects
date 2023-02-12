/*
  Daren Kostov
  Student Database- manages students gpa, id, etc

*/


#include "student.h"
#include "node.h"

#ifndef DATABASE
#define DATABASE


class StudentDatabase{
  public:

    //adds a student to the database | first name, last name, gpa
    void insert(Text, Text, double);

    //gives a student based on their id. No access to change it, just read/view it.
    Student getStudent(int);
    Student locate(int);
    Student find(int);
    
    //removes a student from the database
    void remove(int);

  private:
    int bestSlotForANewStudent;
    int tables;
    Node<Node<Student*>**>* slots =nullptr;//new Node<Student*>*[100];
    
};


#endif