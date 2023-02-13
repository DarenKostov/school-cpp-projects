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
  int tableCounter=0;
  
  printf("printing\n");
  for(auto i=slots; i!=nullptr; i=i->getNext(), tableCounter++){
    
    for(int j=0; j<tableSize; j++){
    
      int linkedCounter=0;
      for(auto k=i->getValue()[j]; k!=nullptr; k=k->getNext(), linkedCounter++){
        Student* current=k->getValue();
        printf("%d:%d:%d %06d: %.2f, %s\n",tableCounter, j, linkedCounter, current->getId(), current->getGpa(), current->getName().val());
       }
    }
  }


}




void StudentDatabase::insert(Text firstName, Text lastName, double gpa){


  
  //get the slot where we should add the student ("Z" and "X" axis)
  Node<Student>*& workingSlot=getSlot(bestSlotForANewStudent);//this is the original


  //Now add the student on the "Y" axis
  addStudent(workingSlot, new Student(firstName, lastName, bestSlotForANewStudent, gpa));

  bestSlotForANewStudent++;
  
}


Node<Student>*& StudentDatabase::getSlot(int id){

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
  Node<Student>*& selectedSlot=selectedTable->getValue()[index]; //this is the original, not a copy

  return selectedSlot;
}


void StudentDatabase::injectStudent(Node<Student>*& whereToAdd /*head*/, Node<Student>* whatToAdd){

  //whereToAdd is the original 
  
  //no head?
  if(whereToAdd==nullptr){
    whereToAdd=whatToAdd;
    return;
  }

  //we have head?
  whereToAdd->addNext(whatToAdd);
  return;

}


void StudentDatabase::addStudent(Node<Student>*& whereToAdd /*head*/, Student* whoToAdd){

  injectStudent(whereToAdd, new Node<Student>(whoToAdd));

}




int StudentDatabase::hash(int id){
  return id%(tableSize*amountOfTables);
}

void StudentDatabase::removeStudent(Node<Student>*& whatToRemove){

  //we are the head;
  if(whatToRemove->getPrev()==nullptr){
    auto newHead=whatToRemove->getNext();
    whatToRemove->deleteMe();
    whatToRemove=newHead;
    return;
  }


  //we are not head  
  whatToRemove->deleteMe();

}


void StudentDatabase::expandAndRehash(){
  //student that is currently being re-located
  int currentlyRelocatingID=0;

  for(int i=0; i<amountOfTables; i++)
    //see the constructor if you are wondering why and how
    slots->addAfter(new Node<Node<Student>*>(new Node<Student>*[tableSize]));

    
  for(auto i=slots; i!=nullptr; i=i->getNext()){   
    for(int j=0; j<tableSize; j++){    
      for(auto& k=i->getValue()[j]; k!=nullptr;){//k is original
        //we are head;
        if(k->getPrev()==nullptr){
          auto newHead=k->getNext();
          k=newHead;
          //go to next node
          k=k->getNext();
          break;
        }

        //we are not head


        //we are bout to detach this, lets keep it so we dont lose it
        auto& current=k; //this is original
        
        //dont break the loop, go to next node
        k=k->getNext();

        //we are no longer in the database
        k->detachMe();



        // addStudent(current,);
        


        
                  
      }
    }
  }

}


