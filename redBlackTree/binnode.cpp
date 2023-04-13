/* 
  Daren Kostov
*/

#include "binnode.h" 

template<class T>
BinNode<T>::BinNode(){
  left=nullptr;
  right=nullptr;
  parent=nullptr;
}


template<class T>
BinNode<T>::BinNode(T in, char col, char relation){
  left=nullptr;
  right=nullptr;
  parent=nullptr;
  value=in;
  color=col;
  relationship=relation;
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
void BinNode<T>::setParent(BinNode* in){
  parent=in;
}

template<class T>
BinNode<T>* BinNode<T>::getParent(){
  return parent;
}

template<class T>
BinNode<T>*& BinNode<T>::Parent(){
  return parent;
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


template<class T>
char BinNode<T>::getRelation(){
  return relationship;
}

template<class T>
char& BinNode<T>::Relation(){
  return relationship;
}

template<class T>
void BinNode<T>::setRelation(char in){
  relationship=in;
}


template<class T>
char BinNode<T>::getColor(){
  return color;
}

template<class T>
char& BinNode<T>::Color(){
  return color;
}

template<class T>
void BinNode<T>::setColor(char in){
  color=in;
}


template class BinNode<int>;


