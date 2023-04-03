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


//fully deletes a binay tree
void deleteBinaryTree(BinNode<char>*);

MainClass::MainClass(){}
MainClass::~MainClass(){

  //delete the binary node tree
  if(binaryTree.getSize()!=0){
    deleteBinaryTree(binaryTree.peek());
  }
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

  std::cout << "This is infix to infix, postfix and prefix program!\n\n"; 
  std::cout << "The operand/operators can be separted by spaces,\n"; 
  std::cout << "by nothing, or even the sequence \"separator\"!\n"; 
  std::cout << "The program will ignore anything that is not a number or an operator!\n"; 
  std::cout << "Mismatched parenthesis detection included.\n";
  
  
  std::cout << "\nhere are some examples:\n\e[92m";
  std::cout << "1 / ( 2 - 4 ) / 4 ^ ( 5 - 0 / 2 )\n";
  std::cout << "2*(7^3)-9/5+1^2/(6-7)^((1-3)*4/2)\n";
  std::cout << "(separator3separator+separator4separator)separator*separator5\n";
  std::cout << "q~(w0r-gf9f)h^j(k2&r*te(@h5o-p.i4hg)fv,/fd5:e)\n";
  
  std::cout << "\n\e[0minput: ";
  
  //make the cin stream not ignore newlines or spaces
  std::cin >> std::noskipws;

  char whiteList[]="1234567890-+*/^()";

  
  char element;
  while(std::cin >> element && element != '\n'){

    std::cout << "\e[91m";
    //add the char only if it's on the white list
    for(int i=0; i<sizeof(whiteList)/sizeof(char); i++){
      if(whiteList[i]==element){
        ioQueue.enqueue(element);
        std::cout << "\e[0m";
        break;
      }
    }


    if(element==' ')
      std::cout << "█";
    else
      std::cout << element;
  
  
  }
  std::cout << "\e[0m\n";
  
  shuntingYardAlgorithm(ioQueue, operatorStack);

  constructBinaryTree(binaryTree, ioQueue);


  std::cout<< "\nInfix:\n";
  printInfix(binaryTree.peek());
  std::cout<< "\n\nPostfix:\n";
  printPostfix(binaryTree.peek());
  std::cout<< "\n\nPrefix\n";
  printPrefix(binaryTree.peek());
  std::cout<< "\n\n";


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
          break;

        if(operatorStack.getSize()==0){
          std::cout<< "\e[91mmismatched parenthesis ( \n\e[0m";
          exit(0);
        }
        
        
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
    
    if(operatorStack.peek()=='('){
      std::cout<< "\e[91mmismatched parenthesis\n\e[0m";
      exit(0);
    }
    
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


void deleteBinaryTree(BinNode<char>* tree){
  if(tree==nullptr)
    return;
  
  deleteBinaryTree(tree->getLeft());
  deleteBinaryTree(tree->getRight());
  delete tree;
}

void printInfix(BinNode<char>* tree){
  if(tree==nullptr)
    return;

  
  if(!std::isdigit(tree->getValue())){
    std::cout << "("; 
  }

  printInfix(tree->getRight());
  std::cout << tree->getValue(); 
  printInfix(tree->getLeft());

  if(!std::isdigit(tree->getValue())){
    std::cout << ")"; 
  }

}

void printPostfix(BinNode<char>* tree){
  if(tree==nullptr)
    return;
  
  printPostfix(tree->getRight());
  printPostfix(tree->getLeft());
  std::cout << tree->getValue(); 

}

void printPrefix(BinNode<char>* tree){
  if(tree==nullptr)
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
  }

  return 0;

}


bool rightAssociative(char in){
  if(in=='^')
    return 1;
  return 0;
}

