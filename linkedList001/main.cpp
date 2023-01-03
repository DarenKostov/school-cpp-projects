/*
  Daren Kostov
  linked list part 1
*/

#include <iostream>
#include "./text.h"
#include "./node.h"


template class Node<Text>;


template <class T>
void printWithHeadFromStart(Node<T>*);
template <class T>
void printWithTailFromEnd(Node<T>*);
template <class T>
void printWithHeadFromEnd(Node<T>*);
template <class T>
void printWithTailFromStart(Node<T>*);


template <class T>
void printWithAnyFromEnd(Node<T>*);
template <class T>
void printWithAnyFromStart(Node<T>*);


typedef Node<Text> SNode;

int main(){

  
  
  SNode* head1= new SNode(new Text("ds"));
  
  Node<Text>* head= new Node<Text>(new Text("first"));
  Node<Text>* tail= new Node<Text>(new Text("last"));
  
  head->addAfter(tail);
  std::cout << "=print from start 000\n";
  printWithHeadFromStart(head);
  
  tail->addBefore(new Node<Text>(new Text("penultimate")));
  std::cout << "=print from start 001\n";
  printWithHeadFromStart(head);
  
  
  head->addAfter(new Node<Text>(new Text("second")));
  std::cout << "=print from start 002\n";
  printWithHeadFromStart(head);
  
  //we are change the HEAD here
  head=head->addBefore(new Node<Text>(new Text("zeroth")));
  std::cout << "=print from start 003\n";
  printWithHeadFromStart(head);
  
  //we are changing the TAIL here
  tail=tail->addAfter(new Node<Text>(new Text("after the last????")));
  std::cout << "=print from start 004\n";
  printWithHeadFromStart(head);

  std::cout << "\n\n\n";
  
  std::cout << "=print from start with head\n";
  printWithHeadFromStart(head);
  
  std::cout << "\n=print from end with tail\n";
  printWithTailFromEnd(tail);


  std::cout << "\n=print from start with tail\n";
  printWithTailFromStart(tail);
  
  std::cout << "\n=print from end with head\n";
  printWithHeadFromEnd(head);


  std::cout << "\n=print from end with any\n";
  printWithAnyFromEnd(head->getNext()->getNext());
  
  std::cout << "\n=print from start with any\n";
  printWithAnyFromStart(head->getNext()->getNext());
  
}


template <class T>
void printWithHeadFromStart(Node<T>* head){
  for(Node<T>* i=head; i!=nullptr; i=i->getNext()) 
    std::cout << *i->val() << '\n';
}
template <class T>
void printWithTailFromEnd(Node<T>* tail){
  for(Node<T>* i=tail; i!=nullptr; i=i->getPrev()) 
    std::cout << *i->val() << '\n';
}

template <class T>
void printWithHeadFromEnd(Node<T>* head){
  if(head->getNext()!=nullptr)
    printWithHeadFromEnd(head->getNext());
  std::cout << *head->val() << '\n';
}

template <class T>
void printWithTailFromStart(Node<T>* tail){
  if(tail->getPrev()!=nullptr)
    printWithTailFromStart(tail->getPrev());
  std::cout << *tail->val() << '\n';
}

template <class T>
void printWithAnyFromEnd(Node<T>* any){
    printWithHeadFromEnd(any->getNext());
    printWithTailFromEnd(any);
}

template <class T>
void printWithAnyFromStart(Node<T>* any){
    printWithTailFromStart(any);
    printWithHeadFromStart(any->getNext());
}
