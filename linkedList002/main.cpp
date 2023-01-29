/*
  Daren Kostov
  Linked List part 2

  fun fact: I didnt use a single "else" for this project

*/



#include "student.h"
#include "node.h"





//adds a new node, return the head|
//1st arg is head, 2nd is previous node, 3rd is what node
void addNode(Node*&);
void addNode(Node*, Node*, Node*);

//removes a node, return the head|
//1st arg is head, 2nd is which node (id)
void removeNode(Node*&);
void removeNode(Node*, int);

//prints all students' info
void printAll(Node*);


int main(){
  cout << "Welcome to the Student Database\n Avaliable commands are A(DD), P(RINT), A(VERAGE), D(ELETE), Q(UIT)";
  Node* head= nullptr;

  while(true){
		Text input;
		cin >> input;

    if(input=='P' || input=="PRINT"){
      cout << "students:\n";
      printAll(head);
      continue;
    }
    if(input=='A' || input=="ADD"){
      cout << "Adding student...\n";
      addNode(head);
      continue;
    }

    if(input=='Q' || input=="QUIT"){
      return 0;
    }
  }


}



void addNode(Node*& head){
  Text firstName, lastName;
  int id;
  double gpa;

  cout << "first name:"; cin >> firstName; 
  cout << "\nlast name:"; cin >> lastName; 
  cout << "\nid:"; cin >> id; 
  cout << "\ngpa:"; cin >> gpa; 

  Node* newNode=new Node(new Student(firstName, lastName, id, gpa));


  //if thats the 1st student added
  if(head==nullptr){
    head=newNode;
    return;
  }


  //if this student has the lowest id
  if(head->getStudent()->getId()>id){
    Node* oldhead=head;
    head=newNode;
    head->setNext(oldhead);
  }

  //if this student is somewhere after the head
  addNode(head->getNext(), head, newNode);
}


void addNode(Node* current, Node* previous, Node* forAdding){

  /*
     4   NULL
    (P)->(C)
        ^
        |
    add 5 here
  */

  if(current==nullptr){
    previous->setNext(forAdding);
    return;
  }


  /* 1    3    ?
    (P)->(C)->(N)
        ^    
        |
    add 2 here
  */

  if(current->getStudent()->getId() > forAdding->getStudent()->getId()){
    previous->setNext(forAdding);
    forAdding->setNext(current);
    return;
  }
  
  addNode(current->getNext(), current, forAdding);

}



// void removeNode(Node*& head){
//   int id;
//   cout << "id:"



// }
// void removeNode(Node* head, int id){
  
// }

void printAll(Node* head){
  
  //if at the end of the list
  if(head==nullptr)
    return;

  Student student=*head->getStudent();
  printf("id: %06d, GPA: %.2f, name: %s\n", student.getId(), student.getGpa(), student.getName().val());

  //print the next node
  printAll(head->getNext());
}
