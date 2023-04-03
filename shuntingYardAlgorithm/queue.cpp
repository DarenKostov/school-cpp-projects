/*
  Daren Kostov

*/


#include "queue.h"


template<class T>
Queue<T>::Queue(){
  size=0;
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

  //increasing the size
  size++;
  
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
T Queue<T>::peek(){
  
  if(head==nullptr)
    return T('X');
  
  return head->getValue();
}

template<class T>
T Queue<T>::dequeue(){
  
  if(head==nullptr)
    return T('X');

  //decreasing the size
  size--;


  T output=head->getValue();
  auto oldHead=head;  

  head=head->getNext();
  delete oldHead;

  return output;
}


template<class T>
int Queue<T>::getSize(){
  return size;
}

template class Queue<char>;

