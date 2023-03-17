/*
  Daren Kostov
  
*/

#include "stack.h"
#include "binode.h"
#include "deleteIfPointer.cpp"

template<class T>
Stack<T>::Stack(){
  head=nullptr;
}

template<class T>
Stack<T>::~Stack(){
  if(head!=nullptr){
    pop();
  }
}

template<class T>
void Stack<T>::push(T in){

  size++;

  //empty stack?
  if(head==nullptr){
    head=new Node<T>(in);
    return;
  }



  Node<T>* newHead=new Node<T>(in);
  newHead->setNext(head);
  head=newHead;

  
}

template<class T>
T Stack<T>::peek(){

  if(head==nullptr)
    return T('X');
    
  
  return head->getValue();
    
}

template<class T>
T Stack<T>::pop(){

  if(head==nullptr)
    return T('X');

  size--;

  T output=head->getValue();
  auto oldHead=head;
  
  head=head->getNext();

  //works delete the derefrenced pointer pointer, and then delete the 1st pointer
  deleteIfPointer(*oldHead);
  deleteIfPointer(oldHead);

  return output;
  
}


template<class T>
int Stack<T>::getSize(){
  return size;
}

template class Stack<char>;
template class Stack<BinNode<char>*>;
