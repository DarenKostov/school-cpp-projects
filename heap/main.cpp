/*
  Daren KOstov
  Heap project

*/

#include "heap.h"
#include "text.h"
#include <fstream>


void addFromFile(Heap<int>&);

void addFromConsole(Heap<int>&);

void printHelp();


int main(){

  Heap<int> myHeap;

  Text input;

  printHelp();
  
  while(input!="QUIT" && input[0]!='q'){

    std::cout << "[heap]: ";
    
    std::cin >>input;

    
    if(input=="a" || input=="ADD"){
      addFromConsole(myHeap);
      continue;
    }else if(input=="p" || input=="PRINT" || input=="d" || input=="DISPLAY"){
      myHeap.display();
      continue;
    }else if(input=="af" || input=="ADDFILE"){
      addFromFile(myHeap);
      continue;
    }else if(input=="r" || input=="rr" || input=="REMOVEROOT"){
      myHeap.removeRoot();
      continue;
    }else if(input=="ra" || input=="REMOVEALL"){
      myHeap.removeAll();
      continue;
    }else if(input=="h" || input=="HELP"){
      printHelp();
      continue;
    }    
    
  }


}

void addFromFile(Heap<int>& heap){

  std::cin.ignore(99999,'\n');
  std::cin.clear();

  //get path
  char* path=new char[100];
  std::cout << "[file path]: ";
  std::cin.getline(path, 100);

  //get file
  std::ifstream file(path);
  delete[] path;

  //something wrong with the file?
  if(!file.good()){
    std::cout << "Oh no! Something went wrong!\n";
    return;
  }


  //add the numbers in the file to the heap
  Text number;
  while (getline(file, number, ' ')){
    heap.add(std::stoi(number.val()));
  }
  file.close();

  std::cout << "done!\n";
}

void addFromConsole(Heap<int>& heap){
  std::cout << "[value]: ";
  
  int input;
  std::cin >> input;

  heap.add(input);
}

void printHelp(){

std::cout <<
  "HELP (h): this help\n" <<
  "ADD (a): adds a new element to the heap from the console\n"<<
  "ADDFILE (af): adds new elements to the heap from a file\n"<<
  "REMOVEROOT (r)(rr): removes the root of the heap\n"<<
  "REMOVEALL (ra): removes every element, as well as print the elements in decending order\n"<<
  "DISPLAY (PRINT)(d)(p): basically tree but with the heap, not the directory system\n";

}


