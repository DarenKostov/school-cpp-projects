

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


  //swap us with our parents until our parents don't have lower value than us
  while(true){
    int parentIndex=getParent(childIndex);
    
    if(*data[parentIndex]<*data[childIndex]){
      
      std::cout <<  *data[parentIndex] << "<" << *data[childIndex] << "\n";
      
      //swap child & parent
      T* temp=data[parentIndex];
      data[parentIndex]=data[childIndex];
      data[childIndex]=temp;
      childIndex=parentIndex;
      // std::cout <<  *data[parentIndex] << ">" << *data[childIndex] << "\n";

      
    }else
      break;
  
  }
  
    

}

template<class T>
void Heap<T>::removeRoot(){

}

template<class T>
void Heap<T>::removeAll(){

}

template<class T>
void Heap<T>::display(){

  for(int i=0; i<100; i++){
    
    if(data[i]!=NULL)
      std::cout << "[" << i << "]" << *data[i] << ", ";
    
  }

    std::cout << "\n";


  int pointer=0;

  printf("├──");
  
  
  for(int i; 0)


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

template class Heap<int>;
