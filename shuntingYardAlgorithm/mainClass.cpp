/*
  Daren Kostov

  the MainClass logici

  sources:
  https://stackoverflow.com/questions/9673708/tell-cin-to-stop-reading-at-newline


*/

#include "mainClass.h"
#include "iostream"


MainClass::MainClass(){
}
MainClass::~MainClass(){
}

void MainClass::startProgram(){
  
  //make the cin stream not ignore newlines or spaces
  std::cin >> std::noskipws;

  char whiteList[]="1234567890-+*/^()";

  
  char element;
  while(std::cin >> element && element != '\n'){

    //add the char only if it's on the white list
    for(int i=0; i<sizeof(whiteList)/sizeof(char); i++){
      if(whiteList[i]==element){
        myQueue.enqueue(element);
        break;
      }
    }
  }



  std::cout << "Queue output:\n";
  while(myQueue.getSize()!=0){
    std::cout << myQueue.dequeue() << " ";
  }
  std::cout << "\n";
  
}
