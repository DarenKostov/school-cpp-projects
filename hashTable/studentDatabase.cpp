/*
  Daren Kostov

  Student Data Base
  
*/

#include "studentDatabase.h"



StudentDatabase::StudentDatabase(){
  tableSize=100;
  bestSlotForANewStudent=0;
  amountOfTables=1;

  /*so....
    1.we make a new linked lists of tables (the head)
    2 we add an array of linked lists to the head, this will be the 1st table
  */
      
  slots=new Node<Node<Student>*>(new Node<Student>*[tableSize]);

}



StudentDatabase::StudentDatabase(int size){
  tableSize=size;
  bestSlotForANewStudent=0;
  amountOfTables=1;
  
  /*so....
    1.we make a new linked lists of tables (the head)
    2 we add an array of linked lists to the head, this will be the 1st table
  */
      
  slots=new Node<Node<Student>*>(new Node<Student>*[tableSize]);

  bestSlotForANewStudent=0;
}

void StudentDatabase::insert(Text firstName, Text lastName, double gpa){

  //get the slot where we should add the student ("X" and "Z" axis)
  Node<Student>* workingSlot=getSlot(bestSlotForANewStudent);


  //Now add the student on the "Y" axis
  addStudent(workingSlot, new Student(firstName, lastName, bestSlotForANewStudent, gpa));
  
}


Node<Student>* StudentDatabase::getSlot(int id){

  int index=hash(id);

  //get ourselves the "X" and "Z" coordinates of this 3d array
  int tableIndex=index/amountOfTables;
  index%=amountOfTables;  

  //move to that table
  Node<Node<Student>*>* selectedTable=slots;
  for(int i=0; i<tableIndex; i++){
    selectedTable=selectedTable->getNext();
  }

  //move to that slot
  Node<Student>* selectedSlot=selectedTable->getValue()[index];

  return selectedSlot;
}


void StudentDatabase::addStudent(Node<Student>* whereToAdd, Student* whoToAdd){

  //no head?
  if(whereToAdd==nullptr){
    whereToAdd=new Node<Student>(whoToAdd);
    return;
  }

  //we have head?
  whereToAdd->addNext(new Node<Student>(whoToAdd));
  return;

}


