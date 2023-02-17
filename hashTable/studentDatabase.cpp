/*
  Daren Kostov

  Student Data Base
  
*/


/*

  //loop through the entire hashmap
  for(auto i=slots; i!=nullptr; i=i->getNext()){//go through each table
    for(int j=0; j<tableSize; j++){ //go through each slot
      for(auto k=i->getValue()[j]; k!=nullptr; k=k->getNext()){ //go through each node
        
      }
    }
  }


  //loop through the entire hashmap in order
  for(auto k=i->getValue()[j]; k!=nullptr; k=k->getNext()){ //go through each node
    for(auto i=slots; i!=nullptr; i=i->getNext()){//go through each table
      for(int j=0; j<tableSize; j++){ //go through each slot
        i->getValue()[j]
      }
    }
  }



*/





#include "studentDatabase.h"
#include <vector>








StudentDatabase::StudentDatabase(){
  tableSize=100;
  bestSlotForANewStudent=0;
  amountOfTables=1;
  amountOfStudents=0;
  
  /*so....
    1.we make a new linked lists of tables (the head)
    2 we add an array of linked lists to the head, this will be the 1st table
  */
      
  slots=new Node<Node<Student>*>(new Node<Student>*[tableSize]);

  
  //starts off with normal values, not random data from memory
  for(int j=0; j<tableSize; j++){
    slots->getValue()[j]=nullptr;
  }
}


StudentDatabase::~StudentDatabase(){

  /*

    node --> array --> slots --> nodes

  */

    
  for(auto i=slots; i!=nullptr;){ //go through each table
    
    for(int j=0; j<tableSize; j++){ // go through each slot
      
      //delete every node, this deletes students too
      auto& currentNode=i->getValue()[j];
      while(currentNode!=nullptr) //go through each node
        currentNode=currentNode->deleteMe();

      //no more nodes in this slot

    }   
    
    auto TableToBeDeleted=i;
    i=i->getNext();



    //deletes the value stored (the table) and the node itself
    TableToBeDeleted->deleteMe();
    
  }

}



StudentDatabase::StudentDatabase(int size){
  tableSize=size;
  bestSlotForANewStudent=0;
  amountOfTables=1;
  amountOfStudents=0;


  
  /*so....
    1.we make a new linked lists of tables (the head)
    2 we add an array of linked lists to the head, this will be the 1st table
  */
  
   
  slots=new Node<Node<Student>*>(new Node<Student>*[tableSize]);

  bestSlotForANewStudent=0;

  //starts off with normal values, not random data from memory
  for(int j=0; j<tableSize; j++){
    slots->getValue()[j]=nullptr;
  }
}

void StudentDatabase::printAll(){
  int tableCounter=0;
  
  printf("printing\n");
  for(auto i=slots; i!=nullptr; i=i->getNext(), tableCounter++){
    
    for(int j=0; j<tableSize; j++){
    
      int linkedCounter=0;
      for(auto k=i->getValue()[j]; k!=nullptr; k=k->getNext(), linkedCounter++){
        Student* current=k->getValue();
        printf("%02d:%03d:%d %06d: %.2f, %s\n",tableCounter, j, linkedCounter, current->getId(), current->getGpa(), current->getName().val());
       }
    }
  }


}




void StudentDatabase::insert(Text firstName, Text lastName, double gpa){


  recalculateBestNewSpot();

  printf("id: %d\n", bestSlotForANewStudent);
  
  printf("real seg fault??\n");
  //get the slot where we should add the student ("Z" and "X" axis)
  Node<Student>*& workingSlot=getSlot(bestSlotForANewStudent);//this is the original


  //Now add the student on the "Y" axis
  addStudent(workingSlot, new Student(firstName, lastName, bestSlotForANewStudent, gpa));


  
}

void StudentDatabase::insert(Student* student){

  
  //get the slot where we should add the student ("Z" and "X" axis)
  Node<Student>*& workingSlot=getSlot(student->getId());//this is the original


  //Now add the student on the "Y" axis
  addStudent(workingSlot, student);
  
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


Node<Student>* StudentDatabase::getNodeStudent(int id){
  
  
  auto head=getSlot(id);


  for(auto i=head; i!=nullptr; i=i->getNext()){
    if(i->getValue()->getId()==id){
      return i;
    }
  }

  return nullptr;
    

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

  short counter=0;
  for(auto i=whereToAdd; i!=nullptr; i=i->getNext(), counter++){
    
  }
  
  if(counter>3){
    printf("\nREHASHING!!!\n");
    expandAndRehash();
    printf("\ndone rehashing\n");
  }

  
  return;

}


void StudentDatabase::addStudent(Node<Student>*& whereToAdd /*head*/, Student* whoToAdd){
  injectStudent(whereToAdd, new Node<Student>(whoToAdd));

  //more than halfway full
  if(++amountOfStudents>(amountOfTables*tableSize*3)/2){
    printf("\nREHASHING!!!\n");
    expandAndRehash();
    printf("\ndone rehashing\n");
  
  }
  
}




int StudentDatabase::hash(int id){
  return id%(tableSize*amountOfTables);
}

void StudentDatabase::removeStudent(int id){


  auto& head=getSlot(id);


  //we are the head;
  if(head->getValue()->getId()==id){
    auto newHead=head->getNext();
    head->deleteMe();
    head=newHead;
    amountOfStudents--;
    return;
  }



  //we are not head  
  for(auto i=head->getNext(); i!=nullptr; i=i->getNext()){
    if(i->getValue()->getId()==id){
      i->deleteMe();
    amountOfStudents--;
      return;
    }
  }

  //we dont know what we are
  printf("Student with id %d does not exist.\n", id);

}


void StudentDatabase::expandAndRehash(){
  //student that is currently being re-located
  int currentlyRelocatingID=0;

  int tableCounter=0;
  for(int i=0; i<amountOfTables; i++){
    //see the constructor if you are wondering why and how
    slots->addAfter(new Node<Node<Student>*>(new Node<Student>*[tableSize]));


    //fixes segfault?
    for(int j=0; j<tableSize; j++){
      slots->getNext()->getValue()[j]=nullptr;
    }
    
  }

  amountOfTables*=2;

  std::vector<Student*> alreadyMovedStudents;;





  //==start of rehashing;
    
  for(auto i=slots; i!=nullptr; i=i->getNext()){ //TABLES
    for(int j=0; j<tableSize; j++){ //SLOTS

      //cant have anything but the head a refrence, k=k.next will result the original k to be the next node
      auto& head=i->getValue()[j];//this is the original
      

      //students to be moved contains 4 nodes at most
      std::vector<Node<Student>*> forMoving; 
    


      //=eject students from the database
      for(auto k=i->getValue()[j]; k!=nullptr;){//k is original  //NODES
        printf("%p, %d=== injecting\n", k, forMoving.size());
       
        //we are about to detach this, lets keep it so we dont lose it
        auto current=k; //this is not the original
        forMoving.push_back(k);
        
        //we are head:
        if(k->getPrev()==nullptr){
          head=nullptr;//this is the original
        }

        //dont break the loop, go to next node
        k=k->getNext();

        //we are no longer in the database
        current->detachMe();
      }

      //=inject the students back into the database
      for(auto k=forMoving.begin(); k!=forMoving.end(); k=forMoving.begin()){
    
        printf("%p, %d ejecting\n", *k, forMoving.size());
        // *k is our student
                  
        Node<Student>*& workingSlot=getSlot((*k)->getValue()->getId());//this is the original

        //injected back into the database
        injectStudent(workingSlot, *k);
  

        //record that we already moved this student
        alreadyMovedStudents.push_back((*k)->getValue());

        forMoving.erase(k);
      }
    }
  }


  //we have double the tables now
  tableCounter*=2;
  


  
}


void StudentDatabase::printSorted(){


  //too lazy to make a formula for this
  int positions[]={0, 3, 2, 1};

  for(int k=0; k<4; k++){ //go through each node
    for(auto i=slots; i!=nullptr; i=i->getNext()){//go through each table
      for(int j=0; j<tableSize; j++){ //go through each slot

        //does the node not exist?
        bool doesNotExist=false;


        //=get the node we want
        auto current=i->getValue()[j];

        //node exists right?
        if(current==nullptr)
          continue;
        
        for(int l=0; l<positions[k]; l++){
          current=current->getNext();
          if(current==nullptr){
            doesNotExist=true;
            break;
          }
        }
        
        //node doesnt exist?
        if(doesNotExist)
          continue;

        

        auto student=current->getValue();
        
        printf("%d %06d: %.2f, %s\n",positions[k], student->getId(), student->getGpa(), student->getName().val());
        
      }
    }
  }

}



void StudentDatabase::recalculateBestNewSpot(){

  int tableCount=0;

  int previous=-1;

  int positions[]={0, 3, 2, 1};

  for(int k=0; k<4; k++){ //go through each node
    for(auto i=slots; i!=nullptr; i=i->getNext(), tableCount++){//go through each table
      for(int j=0; j<tableSize; j++){ //go through each slot

        //does the node not exist?
        bool doesNotExist=false;


        //=get the node we want
        auto current=i->getValue()[j];

        //node exists right?
        if(current==nullptr)
          continue;
        
        for(int l=0; l<positions[k]; l++){
          current=current->getNext();
          if(current==nullptr){
            doesNotExist=true;
            break;
          }
        }
        
        //node doesnt exist?
        if(doesNotExist)
          continue;

        printf("seg fault?\?== %d\n", tableCount);

        printf("iadress: %p\n", current->getNext());

        
        //=find a gap        
        auto student=current->getValue();

        if(previous+1!=student->getId()){
        //we found a gap!        
          bestSlotForANewStudent=previous+1;
      
          //our work here is done
          return;

                    
        }else{
        //we didnt find a gap :/
          previous++;
        }

          
      }
    }
  }

  //no gaps at all? set it to the very end then
  bestSlotForANewStudent=previous+1;

}


Student* StudentDatabase::getStudent(int id){
  return getNodeStudent(id)->getValue();
}
Student* StudentDatabase::locate(int id){
  return getStudent(id);;
}
Student* StudentDatabase::find(int id){
  return getStudent(id);
}



//=stats getters

int StudentDatabase::getStudentAmount(){
  return amountOfStudents;
}

int StudentDatabase::getCapacity(){
  return amountOfTables*tableSize*3;
}

int StudentDatabase::getTables(){
  return amountOfTables;
}

int StudentDatabase::getTableSize(){
  return tableSize;
}






