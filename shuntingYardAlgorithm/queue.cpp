/*
  Daren Kostov

*/


#include "queue.h"


template<class T>
Queue<T>::Queue(){
  head=nullptr;
  tail=nullptr;
}

template<class T>
Queue<T>::~Queue(){

  while(head!=nullptr){
    dequeue();
  }
  
}

template<class T>
void Queue<T>::enqueue(T in){


  //empty queue?
  if(head==nullptr){
    head=new Node<T>(in);
    tail=head;
    return;
  }

  tail->setNext(new Node<T>(in));
  tail=tail->getNext();
  
}

template<class T>
T Queue<T>::peak(){
  
  if(head==nullptr)
    return T('X');
  
  return head->getNext()->getValue();
}

template<class T>
T Queue<T>::dequeue(){
  
  if(head==nullptr)
    return T('X');



  T output=head->getValue();
  auto oldHead=head;  

  head=head->getNext();
  delete oldHead;

  return output;

  
}


template class Queue<char>;

