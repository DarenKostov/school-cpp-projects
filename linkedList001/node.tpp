/*
  Daren Kostov
*/



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

//=getters

template<class T>
Node<T>* Node<T>::getNext() const{
  return next;
}

template<class T>
Node<T>* Node<T>::getPrev() const{
  return previous;
}

template<class T>
T* Node<T>::val() const{
  return value;
}

//=setters

template<class T>
void Node<T>::setNext(Node* arg){
  next=arg;
}

template<class T>
void Node<T>::setPrev(Node* arg){
  previous=arg;
}

//=adders

template<class T>
Node<T>* Node<T>::addNext(Node* in){
  //     |
  //     v
  //(1)=(2)=(3)
  //  
  
  Node* one=this;
  Node* two=in;
  Node* three=next;
  
  //why would we be a nullptr? how would you even call this function??
  if(one!=nullptr)
    //set the 1s next to be the 2
    one->setNext(two);
  
  //why would we add a nullptr anyway? who does this
  if(two!=nullptr){
    //set the 2s prev to be the 1
    two->setPrev(one);
    //set the 2s next to be the 3
    two->setNext(three);
  }
    
  if(three!=nullptr)
    //set the 3s prev to be the 2
    three->setPrev(two);
  //we were the HEAD
  else
    return two;
  //we are not the HEAD
  return this;
}


template<class T>
Node<T>* Node<T>::addPrev(Node* in){
  //     |
  //     v
  //(3)=(2)=(1)
  //  
  
  Node* one=this;
  Node* two=in;
  Node* three=previous;
  
  //why would we be a nullptr? how would you even call this function??
  if(one!=nullptr)
    //set the 1s prev to be the 2
    one->setPrev(two);

  
  //why would we add a nullptr anyway? who does this
  if(two!=nullptr){
    //set the 2s next to be the 1
    two->setNext(one);
    //set the 2s prev to be the 3
    two->setPrev(three);
  }
  
  if(three!=nullptr)
    //set the 3s next to be the 2
    three->setNext(two);
  //we were the TAIL
  else
    return two;
  
  //we are not the TAIL
  return this;
}

//deleters

template<class T>
Node<T>* Node<T>::removeMe(){
  //
  //(1)=(3)
  //  
  
  Node* output=nullptr;
  
  Node* one=previous;
  Node* three=next;
  
  
  //we are not HEAD
  if(one!=nullptr)
    //set the 1s next to be the 3
    one->setNext(three);
  //we are HEAD
  else
    output=three;
  
  
  //we are not TAIL
  if(three!=nullptr)
    //set the 3s prev to be the 1
    three->setPrev(one);
  //we are TAIL and HEAD
  else if(one==nullptr)
    output=nullptr;
  //we are TAIL
  else
    output=one;
  
  //evolke deconstructor
  delete this;  
  
  return output;
}

//=aliases

template<class T>
T* Node<T>::getValue() const{
  return val();
}

template<class T>
Node<T>* Node<T>::getPrevious() const{
  return getPrev();
}

template<class T>
Node<T>* Node<T>::addForward(Node* in){
  return addNext(in);
}
template<class T>
Node<T>* Node<T>::addAfter(Node* in){
  return addNext(in);
}

template<class T>
Node<T>* Node<T>::addBackwards(Node* in){
  return addPrev(in);
}
template<class T>
Node<T>* Node<T>::addBefore(Node* in){
  return addPrev(in);
}
template<class T>
Node<T>* Node<T>::addPrevious(Node* in){
  return addPrev(in);
}

template<class T>
Node<T>* Node<T>::deleteMe(){
  return removeMe();
}

