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
//1st arg is head, 2nd is previous node, 3rd is which node (id)
void removeNode(Node*&);
void removeNode(Node*, Node*, int);

//prints all students' info
void printAll(Node*);


//Averages all of the student's gpa's and prints it
void printAverage(Node*);


//sums up all of the gpa's and returns it (also returns how many students it has added up)
void* sumGpa(Node*);

int main(){
  cout << "Welcome to the Student Database\nAvaliable commands are A(DD), P(RINT), A(VERAGE), DELETE, Q(UIT)\n";
  Node* head= nullptr;

  while(true){
		Text input;
		cout << "\nA/P/AV/R/Q:"; cin >> input;

    if(input=='P' || input=="PRINT"){
      cout << "\nPrinting all students:\n";
      printAll(head);
      continue;
    }
    if(input=='A' || input=="ADD"){
      cout << "\nAdding student...\n";
      addNode(head);
      continue;
    }
    if(input=='R' || input=="DELETE"){
      cout << "\nRemoving student...\n";
      removeNode(head);
      continue;
    }
    
    if(input=="AV" || input=="AVERAGE"){
      cout << "\nAveraging GPA's...\n";
      printAverage(head);
      continue;
    }

    if(input=='Q' || input=="QUIT"){
      cout << "\nQuitting...\n";
      return 0;
    }

    cout << "\nWhat command is \"" << input <<"\" supposed to envoke?\n";
    cout << "The following commands are valid:\n";
    cout << "A\tP\tAV\tR\tQ\n";
    cout << "ADD\tPRINT\tAVEARGE\tDELETE\tQUIT\n";
  }


}



void addNode(Node*& head){
  Text firstName, lastName;
  int id;
  double gpa;

  cout << "first name:"; cin >> firstName; 
  cout << "last name:"; cin >> lastName; 
  cout << "id:"; cin >> id; 
  cout << "gpa:"; cin >> gpa; 

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



void removeNode(Node*& head){
  int id;
  cout << "id:"; cin >> id;

  if(head->getStudent()->getId()==id){
    Text name=head->getStudent()->getName();
    Node* oldhead=head; 
    head=head->getNext();
    delete head;
    cout << name << " is removed from the Database\n";
    return;
  }

  removeNode(head->getNext(), head, id);

}

void removeNode(Node* current, Node* previous, int id){
  
  //the id of this node
  int thisID;
    
  //no need to search if we are sure the student isnt in the database
  if(current==nullptr || (thisID=current->getStudent()->getId()) > id){
    cout << "The student is nowhere to be found\n";
    return;
  }


  if(thisID==id){
    Text name=current->getStudent()->getName();
    previous->setNext(current->getNext());
    delete current;
    cout << name << " is removed from the Database\n";
    return;
  }

  
  removeNode(current->getNext(), current, id);
  
}

void printAverage(Node* head){


  void* input= sumGpa(head);

  //the "max" is so that we don't devide by 0
  double average=(*(double*)((char*)input+sizeof(int))) / max(1, *(int*)(input));


  
  free(input);

  printf("GPA average: %1.2f\n", average);
  
}


void* sumGpa(Node* current){

  //allocate memory for our output
  void* output=malloc(sizeof(int)+sizeof(double));

  //if we are at the end, return 0's
  if(current==nullptr){
    *(int*)(output)=0;
    *(double*)((char*)output+sizeof(int))=0;
    return output;  
  }

  //get the next node's sum
  void* input= sumGpa(current->getNext());


  //for ease
  Student student= *current->getStudent();



  //sum up the gpa's
  //gotta cast to char* since you cant do void* arethmetic in C++ as opposed to C
  *(int*)(output)=1+*(int*)(input);
  *(double*)((char*)output+sizeof(int))=student.getGpa()+*(double*)((char*)input+sizeof(int));


  //the function previous (rather the next actually) allocated memory for this, we gotta free it
  free(input);


  return output;  
  
}



void printAll(Node* head){
  
  //if at the end of the list
  if(head==nullptr)
    return;

  Student student=*head->getStudent();
  printf("id: %06d, GPA: %1.2f, name: %s\n", student.getId(), student.getGpa(), student.getName().val());

  //print the next node
  printAll(head->getNext());
}
