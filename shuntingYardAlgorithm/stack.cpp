/*
  Daren Kostov
  
*/

#include "stack.h"

template<class T>
Stack<T>::Stack(){
  head=nullptr;
}


template<class T>
void Stack<T>::push(T in){

  //empty stack?
  if(head==nullptr){
    head=new Node<T>(in);
    return;
  }



  Node<T>* newHead=new Node<T>(in);
  newHead->setNext(new Node<T>(in));
  head=newHead;

  
}

template<class T>
T Stack<T>::peak(){

  if(head==nullptr)
    return T('X');
    
  
  return head->getValue();
    
}

template<class T>
T Stack<T>::pop(){

  if(head==nullptr)
    return T('X');


  T output=head->getValue();
  auto oldHead=head;
  
  head=head->getNext();
  delete oldHead;

  return output;
  

}

template class Stack<char>;
