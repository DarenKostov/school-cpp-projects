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

//give it a stack and itll make you a binary tree from a queue
void constructBinaryTree(Stack<BinNode<char>*>&, Queue<char>&);

//functions are self explanatory
void printInfix(BinNode<char>*);
void printPostfix(BinNode<char>*);
void printPrefix(BinNode<char>*);



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

  constructBinaryTree(binaryTree, ioQueue);


  // Node<char>* a=nullptr;

  // std::cout << a << "\n";


  std::cout<< "Infix:\n";
  printInfix(binaryTree.peek());
  std::cout<< "\n\nPostfix:\n";
  printPostfix(binaryTree.peek());
  std::cout<< "\n\nPrefix\n";
  printPrefix(binaryTree.peek());
  std::cout<< "\n";

}


void shuntingYardAlgorithm(Queue<char>& ioQueue, Stack<char>& operatorStack){
  //initial size of the queue
  int initSize=ioQueue.getSize();

  for(int i=0; i<initSize; i++){
    char currentElement=ioQueue.dequeue();

    //if a number, add it to the output
    if(std::isdigit(currentElement)){
      ioQueue.enqueue(currentElement);
      continue;
    }

    //if a left parenthesis, push it to the stack
    if(currentElement=='('){
      operatorStack.push(currentElement);
      continue;
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

      continue;
    }

    //===if an operator===

    //if stack is empty or end with '(', add to the stack
    if(operatorStack.getSize()==0 || operatorStack.peek()=='('){
      operatorStack.push(currentElement);
      continue;
    }

    //if it has higher or equal precedence to the stack's top and is right associative, add to the stack
    if(precedence(currentElement)>=precedence(operatorStack.peek()) && rightAssociative(currentElement)){
      operatorStack.push(currentElement);
      continue;
    }
  

    //if the opposite of the previous if statement, add from the stack to the output until it is not true
    while(precedence(currentElement)<=precedence(operatorStack.peek()) && !rightAssociative(currentElement)){
      ioQueue.enqueue(operatorStack.pop());
    }
    //finally add the opertaro to the stack
    operatorStack.push(currentElement);
    continue;
    
    std::cout << "what happened here?\n";
  }


  //and at the end, add the stack to the output
  while(operatorStack.getSize()!=0){
    ioQueue.enqueue(operatorStack.pop());
  }

  
}



void constructBinaryTree(Stack<BinNode<char>*>& output, Queue<char>& input){
  while(input.getSize()!=0){
    char currentElement=input.dequeue();

    //if number add to stack
    if(std::isdigit(currentElement)){
      output.push(new BinNode<char>(currentElement));
      continue;
    }

    
    // if an operator, take the 2 numbers following it IN THE STACK and make them its children, push the operator afterwards

    BinNode<char>* newNode=new BinNode<char>(currentElement);
    newNode->setLeft(output.pop());
    newNode->setRight(output.pop());
    output.push(newNode);

    continue;//a useless continue
    
  }
  

}


void printInfix(BinNode<char>* tree){
  if (tree==nullptr)
    return;

  
  if(!std::isdigit(tree->getValue())){
    std::cout << "(" << std::flush; 
  }

  printInfix(tree->getRight());
  std::cout << tree->getValue(); 
  printInfix(tree->getLeft());

  if(!std::isdigit(tree->getValue())){
    std::cout << ")" << std::flush; 
  }

}
void printPostfix(BinNode<char>* tree){
  if (tree==nullptr)
    return;
  
  printPostfix(tree->getRight());
  printPostfix(tree->getLeft());
  std::cout << tree->getValue(); 

}
void printPrefix(BinNode<char>* tree){
  if (tree==nullptr)
    return;
  
  std::cout << tree->getValue(); 
  printPrefix(tree->getRight());
  printPrefix(tree->getLeft());

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

