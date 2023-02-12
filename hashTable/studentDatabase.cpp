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

void StudentDatabase::printAll(){
  printf("printing\n");
  for(auto i=slots; i!=nullptr; i=i->getNext()){
  printf("Z\n");
    for(int j=0; j<tableSize; j++){
  // printf("X\n");
      std::cout << i->getValue()[j] << "\n";
      for(auto k=i->getValue()[j]; k!=nullptr; k=k->getNext()){
  printf("Y\n");
        Student* current=k->getValue();
        printf("%06d: %.2f, %s\n", current->getId(), current->getGpa(), current->getName().val());
       }
    }
  }


}




void StudentDatabase::insert(Text firstName, Text lastName, double gpa){

  //get the slot where we should add the student ("Z" and "X" axis)
  Node<Student>* workingSlot=getSlot(bestSlotForANewStudent);


  //Now add the student on the "Y" axis
  addStudent(workingSlot, new Student(firstName, lastName, bestSlotForANewStudent, gpa));

  bestSlotForANewStudent++;
  
}


Node<Student>* StudentDatabase::getSlot(int id){

  int index=hash(id);

  //get ourselves the "Z" and "X" coordinates of this 3d array
  int tableIndex=index/tableSize;
  index%=tableSize;  

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
  // printf("adding\n");

  //whereToAdd is a separet pointer, changing it wont chnage the original
  
  //no head?
  if(whereToAdd==nullptr){
    whereToAdd=new Node<Student>(whoToAdd);
    // std::cout << whereToAdd c
    return;
  }

  //we have head?
  whereToAdd->addNext(new Node<Student>(whoToAdd));
  return;

}

int StudentDatabase::hash(int id){
  return id%(tableSize*amountOfTables);
}
