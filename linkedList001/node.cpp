/*
  Daren Kostov
*/

#include "./node.h"

template<class T>
Node<T>::Node(T* arg){
  value=arg;
  next=nullptr;
  previous=nullptr;
}

template<class T>
Node<T>::~Node(){
  delete value;
  
  // //evokes the deconstuctor, which in turn envokes the deconstructor....
  // delete this;
}

template<class T>
Node<T>* Node<T>::getNext(){
  return next;
}

template<class T>
Node<T>* Node<T>::getPrev(){
  return previous;
}


template<class T>
T* Node<T>::val(){
  return value;
}

template<class T>
T* Node<T>::getValue(){
  return val();
}

template<class T>
void Node<T>::setNext(Node* arg){
  next=arg;
}

template<class T>
void Node<T>::setPrev(Node* arg){
  previous=arg;
}

template<class T>
void Node<T>::addNext(Node* in){
  //     |
  //     v
  //(1)=(2)=(3)
  //  
  
  Node* one=this;
  Node* two=in;
  Node* three=next;
  
  
  //set the 3s prev to be the 2
  three->setPrev(two);
  //set the 2s prev to be the 1
  two->setPrev(one);
  
  //set the 1s next to be the 2
  one->setNext(two);
  //set the 2s next to be the 3
  two->setNext(three);
  
}


template<class T>
void Node<T>::addPrev(Node* in){
  //     |
  //     v
  //(3)=(2)=(1)
  //  
  
  Node* three=previous;
  Node* two=in;
  Node* one=this;
  
  //set the 3s next to be the 2
  three->setNext(two);
  //set the 2s next to be the 1
  two->setNext(one);
  
  //set the 1s prev to be the 2
  one->setPrev(two);
  //set the 2s prev to be the 3
  two->setPrev(three);
  
}


template<class T>
void Node<T>::removeMe(){
  //
  //(1)=(3)
  //  
  
  Node* one=previous;
  Node* three=next;
  
  //set the 1s next to be the 3
  one->setNext(three);
  //set the 3s prev to be the 1
  three->setPrev(one);
  
  //evolke deconstructor
  delete this;  
  
}

//=aliases

template<class T>
Node<T>* Node<T>::getPrevious(){
  return getPrev();
}

template<class T>
void Node<T>::addForward(Node* in){
  addNext(in);
}
template<class T>
void Node<T>::addAfter(Node* in){
  addNext(in);
}

template<class T>
void Node<T>::addBackwards(Node* in){
  addPrev(in);
}
template<class T>
void Node<T>::addBefore(Node* in){
  addPrev(in);
}
template<class T>
void Node<T>::addPrevious(Node* in){
  addPrev(in);
}

template<class T>
void Node<T>::deleteMe(){
  removeMe();
}

