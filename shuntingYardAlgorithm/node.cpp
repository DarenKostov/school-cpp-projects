/* 
  Daren Kostov
*/

#include "node.h" 
#include "binode.h" 
#include "deleteIfPointer.cpp" 


template<class T>
Node<T>::Node(){
  next=nullptr;
  previous=nullptr;
}


template<class T>
Node<T>::Node(T in){
  next=nullptr;
  previous=nullptr;
  value=in;
}


template<class T>
Node<T>::~Node(){
  deleteIfPointer(value);
}

template<class T>
void Node<T>::setNext(Node* in){
  next=in;
}

template<class T>
void Node<T>::setPrevious(Node* in){
  previous=in;
}

template<class T>
Node<T>* Node<T>::getNext(){
  return next;
}

template<class T>
Node<T>* Node<T>::getPrevious(){
  return previous;
}

template<class T>
T Node<T>::getValue(){
  return value;
}

template<class T>
void Node<T>::setValue(T in){
  value=in;
}


template class Node<char>;
template class Node<BinNode<char>*>;



