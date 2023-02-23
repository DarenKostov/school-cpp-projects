/*
  Daren KOstov
  Heap project

*/

#include "heap.h"
#include "text.h"


void addFromFile(Heap<int>&);

void addFromConsole(Heap<int>&);

int main(){

  Heap<int> myHeap;

  Text input;


  while(input!="QUIT" && input[0]!='q'){

    std::cout << "[heap]: ";
    
    std::cin >>input;

    
    if(input[0]=='a' || input=="ADD"){
      addFromConsole(myHeap);
      continue;
    }else if(input[0]=='p' || input=="PRINT" || input[0]=='d' || input=="DISPLAY"){
      myHeap.display();
      continue;
    }    


    


  }


}

void addFromFile(Heap<int>&){
    
}

void addFromConsole(Heap<int>& heap){
  std::cout << "[value]: ";
  
  int input;
  std::cin >> input;

  heap.add(input);

  
  
}


