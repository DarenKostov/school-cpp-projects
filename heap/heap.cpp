/*
  Daren Kostov

  note:
  the "<" operator was exclusively used on purpose

*/




#include "heap.h"

template<class T>
Heap<T>::Heap(){
  data=new T*[100];

  for(int i=0; i<100; i++){
    data[i]=NULL;
  }

  newSpot=0;

}


template<class T>
void Heap<T>::add(T childValue){

  //where are we?
  int childIndex=newSpot++;

  //put us on heap
  data[childIndex]=new T(childValue);


  //swap the child with its parent until the parent doesnt have a lower value than the child
  while(true){
    int parentIndex=getParent(childIndex);
    
    if(*data[parentIndex]<*data[childIndex]){
      
      
      //swap child & parent
      T* temp=data[parentIndex];
      data[parentIndex]=data[childIndex];
      data[childIndex]=temp;
      childIndex=parentIndex;

      
    }else
      break;
  
  }
  
    

}

template<class T>
void Heap<T>::removeRoot(){

  //the last index that holds any value
  int lastIndex=newSpot--;

  //swap the root with the last element, deleteing the root in the process (thats not really what is happening, but its happening in spirit)
  delete data[0];
  data[0]=data[lastIndex];
  data[lastIndex]=NULL;



  int parentIndex=0;

  //swap the parent with its highest value child until it has no more children

  while(true){
    int leftChildIndex=getLeftChild(parentIndex);
    int rightChildIndex=getRightChild(parentIndex);


    //left child doesnt exist? the only possible configuration that allows for this is when we don't have any children
    if(!doesItExist(leftChildIndex))
      break;
    
    //no right child? no problem, just swap with the left one
    else if(!doesItExist(rightChildIndex)){
      
      T* temp=data[parentIndex];
      data[parentIndex]=data[leftChildIndex];
      data[leftChildIndex]=temp;
      parentIndex=leftChildIndex;

    //both children exist? compare them and decide with which one to swap
    }else{

      //The right child has a higher value (or the same)? swap with it
      if(*data[leftChildIndex]<*data[rightChildIndex]){
      
        T* temp=data[parentIndex];
        data[parentIndex]=data[rightChildIndex];
        data[rightChildIndex]=temp;
        parentIndex=rightChildIndex;
      
      }else{

        T* temp=data[parentIndex];
        data[parentIndex]=data[leftChildIndex];
        data[leftChildIndex]=temp;
        parentIndex=leftChildIndex;
            
      }
    }
  }
}



template<class T>
void Heap<T>::removeAll(){

  while(data[0]!=NULL){
    std::cout << *data[0] << "\n";
    removeRoot();
  
  }



}

template<class T>
void Heap<T>::display(){

  std::cout << "x" << *data[0] << "\n";
  displayLeft(getLeftChild(0), "");
  displayRight(getRightChild(0), "");

}


template<class T>
int Heap<T>::getRightChild(int i){
  //array starts at 0, not 1, gotta account for that
  return (++i*2+1)-1;
}

template<class T>
int Heap<T>::getLeftChild(int i){
  //array starts at 0, not 1, gotta account for that
  return (++i*2)-1;
}

template<class T>
int Heap<T>::getParent(int i){
  //array starts at 0, not 1, gotta account for that
  return (--i/2);
}

template<class T>
bool Heap<T>::doesItExist(int i){
  if(i>99)
    return false;

  if(data[i]==NULL)
    return false;

  return true;
}


template<class T>
void Heap<T>::displayRight(int index, Text inheritance){


  //we arent in the heap? dont display us
  if(!doesItExist(index))
    return;


  Text myInheritance;
  for(int i=0; i<inheritance.len(); i++){
    myInheritance+=inheritance[i];
  }



  std::cout << myInheritance;


  //adjust position
  std::cout << "└─";
  inheritance+="  ";


    

  //print our value
  std::cout << "r";
  std::cout << *data[index] << "\n";

  
    
  
  displayLeft(getLeftChild(index), inheritance);
  displayRight(getRightChild(index), inheritance);

  

}

template<class T>
void Heap<T>::displayLeft(int index, Text inheritance){


  //we arent in the heap? dont display us
  if(!doesItExist(index))
    return;



  Text myInheritance;
  for(int i=0; i<inheritance.len(); i++){
    myInheritance+=inheritance[i];
  }



  std::cout << myInheritance;


  

  //if are we the only child
  if(!doesItExist(getRightChild(getParent(index)))){
    std::cout << "└─";
    inheritance+="  ";
  }else{
    std::cout << "├─";
    inheritance+="│ ";
  }
  


  //print our value
  std::cout << "l";
  std::cout << *data[index] << "\n";

  
    
  
  displayLeft(getLeftChild(index),  inheritance);
  displayRight(getRightChild(index), inheritance);

  

}


template class Heap<int>;
