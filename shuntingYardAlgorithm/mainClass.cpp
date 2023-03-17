/*
  Daren Kostov

  the MainClass logic

  sources:
  https://stackoverflow.com/questions/9673708/tell-cin-to-stop-reading-at-newline

  //best explanation I could find
  https://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/

*/

#include "mainClass.h"
#include "iostream"


MainClass::MainClass(){
}
MainClass::~MainClass(){
}

//performs the Shunting yard algorithm, stack is included because I want it to be deleted in the case I stop the program in this particular function
void shuntingYardAlgorithm(Queue<char>&, Stack<char>&);

//returns the presentnce of an operator
int precedence(char);

//determine if an operator is right associative
bool rightAssociative(char);

void MainClass::startProgram(){
  
  //make the cin stream not ignore newlines or spaces
  std::cin >> std::noskipws;

  char whiteList[]="1234567890-+*/^()";

  
  char element;
  while(std::cin >> element && element != '\n'){

    //add the char only if it's on the white list
    for(int i=0; i<sizeof(whiteList)/sizeof(char); i++){
      if(whiteList[i]==element){
        ioQueue.enqueue(element);
        break;
      }
    }
  }

  shuntingYardAlgorithm(ioQueue, operatorStack);

  std::cout << "Queue output:\n";
  while(ioQueue.getSize()!=0){
    std::cout << ioQueue.dequeue() << " ";
  }
  std::cout << "\n";
  
}


void shuntingYardAlgorithm(Queue<char>& ioQueue, Stack<char>& operatorStack){
  //initial size of the queue
  int initSize=ioQueue.getSize();

  for(int i=0; i<initSize; i++){
    char currentElement=ioQueue.dequeue();

    //if a number, add it to the output
    if(std::isdigit(currentElement)){
      ioQueue.enqueue(currentElement);
      break;
    }

    //if a left parenthesis, push it to the stack
    if(currentElement=='('){
      operatorStack.push(currentElement);
      break;
    }

    
    //if a right parenthesis... add from the stack to the output untill you see a left parenthesis
    if(currentElement==')'){

      while(operatorStack.getSize()!=0){
        char toBeAdded=operatorStack.pop();

        if(toBeAdded=='(')
          //TODO add mismatches parenthesis error message
          break;
        
        ioQueue.enqueue(toBeAdded);
      }

      break;
    }

    //===if an operator===

    //if stack is empty or end with '(', add to the stack
    if(operatorStack.getSize()==0 || operatorStack.peek()=='('){
      operatorStack.push(currentElement);
      break;
    }

    //if it has higher or equal precedence to the stack's top and is right associative, add to the stack
    if(precedence(currentElement)>=precedence(operatorStack.peek()) && rightAssociative(currentElement)){
      operatorStack.push(currentElement);
      break;
    }
  

    //if the opposite of the previous if statement, add from the stack to the output until it is not true
    while(precedence(currentElement)<=precedence(operatorStack.peek()) && !rightAssociative(currentElement)){
      ioQueue.enqueue(operatorStack.pop());
    }
    //finally add the opertaro to the stack
    operatorStack.push(currentElement);
    break;
      
    std::cout << "what happened here?\n";
  }


  //and at the end, add the stack to the output
  while(operatorStack.getSize()!=0){
    ioQueue.enqueue(operatorStack.pop());
  }

  
}


int precedence(char in){
  switch(in){
    case '+':
    case '-':
      return 1;
    case '/':
    case '*':
      return 2;
    case '^':
      return 3;
    case '(':
    case ')':
      return 4;
  }

  return 0;

}


bool rightAssociative(char in){
  if(in=='^')
    return 1;
  return 0;
}

