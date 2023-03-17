/*
  Daren Kostov

  the MainClass logic

*/

#include "mainClass.h"
#include "iostream"


MainClass::MainClass(){
  myStack=new Stack<char>();
  myQueue=new Queue<char>();
}
  
MainClass::~MainClass(){
  delete myStack;
  delete myQueue;
}

void MainClass::startProgram(){


  std::cout << "input:\n";
  for(char i='0'; i<='9'; i++){
    std::cout << i << " ";
    myQueue->enqueue(i);
    myStack->push(i);
  }
  std::cout << "\n";

  
  std::cout << "Stack output:\n";
  for(int i=0; i<10; i++){
    std::cout << myStack->pop() << " ";
  }
  std::cout << "\n";

  std::cout << "Queue output:\n";
  for(int i=0; i<10; i++){
    std::cout << myQueue->dequeue() << " ";
  }
  std::cout << "\n";
  
}
