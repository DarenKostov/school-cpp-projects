/*
  Daren Kostov
  linked list part 1
*/

#include <iostream>
#include "./text.h"
#include "./node.h"
#include "./student.h"


template class Node<Text>;


template <class T>
void printforward(Node<T>*);
template <class T>
void printbackward(Node<T>*);


typedef Node<Text> SNode;

int main(){

  
  
  SNode* head1= new SNode(new Text("ds"));
  
  Node<Text>* head= new Node<Text>(new Text("first"));
  Node<Text>* tail= new Node<Text>(new Text("last"));
  
  head->addAfter(tail);
  std::cout << "=print from HEAD 000\n";
  printforward(head);
  
  tail->addBefore(new Node<Text>(new Text("penultimate")));
  std::cout << "=print from HEAD 001\n";
  printforward(head);
  
  
  head->addAfter(new Node<Text>(new Text("second")));
  std::cout << "=print from HEAD 002\n";
  printforward(head);
  
  //we are change the HEAD here
  head=head->addBefore(new Node<Text>(new Text("zeroth")));
  std::cout << "=print from HEAD 003\n";
  printforward(head);
  
  //we are changing the TAIL here
  tail=tail->addAfter(new Node<Text>(new Text("after the last????")));
  std::cout << "=print from HEAD 004\n";
  printforward(head);
}


template <class T>
void printforward(Node<T>* head){
  for(Node<T>* i=head; i!=nullptr; i=i->getNext()) 
    std::cout << *i->val() << '\n';
}
template <class T>
void printbackward(Node<T>* tail){
  for(Node<T>* i=tail; i!=nullptr; i=i->getPrev()) 
    std::cout << *i->val() << '\n';
}