/* 
  Daren Kostov
*/

#include "binnode.h" 

template<class T>
BinNode<T>::BinNode(){
  left=nullptr;
  right=nullptr;
}


template<class T>
BinNode<T>::BinNode(T in){
  left=nullptr;
  right=nullptr;
  value=in;
}

template<class T>
BinNode<T>::~BinNode(){
  //do nothing
}

template<class T>
void BinNode<T>::setRight(BinNode* in){
  right=in;
}

template<class T>
BinNode<T>* BinNode<T>::getRight(){
  return right;
}

template<class T>
BinNode<T>*& BinNode<T>::Right(){
  return right;
}


template<class T>
void BinNode<T>::setLeft(BinNode* in){
  left=in;
}

template<class T>
BinNode<T>* BinNode<T>::getLeft(){
  return left;
}

template<class T>
BinNode<T>*& BinNode<T>::Left(){
  return left;
}


template<class T>
T BinNode<T>::getValue(){
  return value;
}

template<class T>
T& BinNode<T>::Value(){
  return value;
}

template<class T>
void BinNode<T>::setValue(T in){
  value=in;
}


template class BinNode<int>;



