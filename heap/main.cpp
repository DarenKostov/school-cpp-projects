/*
  Daren KOstov
  Heap project

*/

#include "heap.h"




int main(){

  Heap<int> myHeap;


  for(int i=1; i<80; i++){
    myHeap.add(i);
  }
  
  myHeap.display();

  myHeap.removeAll();
  
}