/*
  Daren Kostov

  the MainClass logic


  I didnt use all of the functions i created here
  
  sources
  https://www.geeksforgeeks.org/deletion-in-binary-search-tree/

*/

#include <iostream>
#include <vector>//does not relate to the binary tree
#include <fstream>

#include "mainClass.h"
#include "text.h"
#include "scmdprs.h"
// #include "binode.h"

MainClass::MainClass(){
  root=nullptr;
}
MainClass::~MainClass(){
  delete root;
}


//adds an int to the bin tree
void add(BinNode<int>*& , int);
void add(BinNode<int>*, BinNode<int>*, char, int);
void addToBinTree(BinNode<int>*&, std::vector<Text>);

//displays the bin tree
void display(BinNode<int>*);
void displayLeft(BinNode<int>*, BinNode<int>*, Text);
void displayRight(BinNode<int>*, Text);
void print(BinNode<int>*);

//tells you whether or not a number is in the bin tree 
void doesItContain(BinNode<int>*, std::vector<Text>);
int doesItContain(BinNode<int>*, int);

//remove a num from the bin tree
void remove(BinNode<int>*&, std::vector<Text>);
BinNode<int>* removeAndReturnNewRoot(BinNode<int>*, int, bool&);

//returns you the bin node whoose value it is int, nullptr if the node doesnt exist
BinNode<int>* returnNodeWithValueOf(BinNode<int>*, int);

//returns you the bin node with the lowest value, if it doesnt exist, it returns nullptr
BinNode<int>* returnMinNode(BinNode<int>*);

//determines whether a Text is a number
bool isANum(Text);


//print help
void printHelp();

void MainClass::startProgram(){
  

  printHelp();

  // char command[20]="";
  

  // std::cout << "press \"a\" and then Enter, this is not a bug, just press \"a\" and then Enter";
  std::cout << "[BinTree]: ";
  for(std::vector<Text> commands=readLine(); (commands[0]!="q") && (commands[0]!="quit"); commands=readLine()){
  

    if(commands[0]=="a" || commands[0]=="add"){
      addToBinTree(root, commands);
    }else if(commands[0]=="d" || commands[0]=="display"){
      display(root);
    }else if(commands[0]=="p" || commands[0]=="print"){
      print(root);
    }else if(commands[0]=="c" || commands[0]=="contains?"){
      doesItContain(root, commands);
    }else if(commands[0]=="r" || commands[0]=="remove"){
      remove(root, commands);
    }else if(commands[0]=="h" || commands[0]=="help"){
      printHelp();
    }else{
      std::cout << "\e[91m????\e[0m\n";
    }

    
    std::cout << "\n[BinTree]: ";
    
    // std::cout << "your arguments:\n";
    // for(Text command : commands)
    // std::cout << command+'\n';

  }



  
}


//==ADDING

void addToBinTree(BinNode<int>*& root, std::vector<Text> commands){

  //not enough arguments
  if(commands.size()<2)
    return;

  int numToAdd=0;

  //do we give a number or a file?
  try{
    numToAdd=std::stoi(commands[1].val());
  }catch(const std::invalid_argument& ia){
    //file?

    std::ifstream file(commands[1].val());

    //something wrong with the file?
    if(!file.good()){
      std::cout << "\e[91mFile where?\n\e[0m";
      return;
    }


    //add the numbers in the file to the bin tree
    Text number;
    while (getline(file, number, ' ')){
      add(root, std::stoi(number.val()));
    }
    file.close();

    return;
  }

  //number?
  add(root, numToAdd);
}

void add(BinNode<int>*& root, int numToAdd){
  //root doesnt exists yet?
  if(root==nullptr){
    root=new BinNode<int>(numToAdd);
    return;
  }

  //give the number to the appropriate child
  if(numToAdd<root->getValue()){
    add(root->getLeft(), root, 'l', numToAdd);  
  }else{
    add(root->getRight(), root, 'r', numToAdd);  
  }
}


void add(BinNode<int>* current, BinNode<int>* previous, char whichChild, int numToAdd){
  //root doesnt exists yet?
  if(current==nullptr){
    if(whichChild=='l')
      previous->setLeft(new BinNode<int>(numToAdd));
    else
      previous->setRight(new BinNode<int>(numToAdd));
      
    return;
  }

  //give the number to the appropriate child
  if(numToAdd<current->getValue()){
    add(current->getLeft(), current, 'l', numToAdd);  
  }else{
    add(current->getRight(), current, 'r', numToAdd);  
  }
}



//==DISPLAYING

void display(BinNode<int>* root){

  //lets save us a seg fault
  if(root==nullptr)
    return;

  std::cout << "\nx" << root->getValue() << "\n";
  displayLeft(root->getLeft(), root, "");
  displayRight(root->getRight(), "");

}


void displayRight(BinNode<int>* current, Text inheritance){


  //we arent in the bin tree? dont display us
  if(current==nullptr)
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
  std::cout << "\e[91mr";
  std::cout << current->getValue() << "\e[0m\n";

  
    
  
  displayLeft(current->getLeft(), current, inheritance);
  displayRight(current->getRight(), inheritance);

  

}

void displayLeft(BinNode<int>* current, BinNode<int>* previous, Text inheritance){


  //we arent in the bin tree? dont display us
  if(current==nullptr)
    return;



  Text myInheritance;
  for(int i=0; i<inheritance.len(); i++){
    myInheritance+=inheritance[i];
  }



  std::cout << myInheritance;


  

  //if are we the only child
  if(previous->getRight()==nullptr){
    std::cout << "└─";
    inheritance+="  ";
  }else{
    std::cout << "├─";
    inheritance+="│ ";
  }
  


  //print our value
  std::cout << "\e[96ml";
  std::cout << current->getValue() << "\e[0m\n";
  
  displayLeft(current->getLeft(), current, inheritance);
  displayRight(current->getRight(), inheritance);
}


void print(BinNode<int>* current){
  if(current==nullptr)
    return;
  std::cout << current->getValue() << " ";
  print(current->getLeft());
  print(current->getRight());

}



void doesItContain(BinNode<int>* root, std::vector<Text> commands){
  
  //not enough arguments
  if(commands.size()<2)
    return;

  int num=0;

  //is this a valid number
  try{
    num=std::stoi(commands[1].val());
  }catch(const std::invalid_argument& ia){
    //invalid?
    std::cout << "\e[91mNo, the Binary Tree defenetly does not contain \""+commands[1]+"\"\n\e[0m";
    return;
  }

  //valid?
  int occurances=doesItContain(root, num);

  if(occurances==1)
    std::cout << "There is 1 occurance of "+commands[1]+'\n';
  else
    std::cout << "There are " << occurances << " occurances of "+commands[1]+'\n';

}




int doesItContain(BinNode<int>* current, int num){
  if(current==nullptr)
    return 0;
  
  if(current->getValue()==num){
    return doesItContain(current->getLeft(), num)+doesItContain(current->getRight(), num)+1;
  }
  return doesItContain(current->getLeft(), num)+doesItContain(current->getRight(), num);
}


void remove(BinNode<int>*& root, std::vector<Text> commands){
  
  //not enough arguments
  if(commands.size()<2)
    return;

  int num=0;

  //is this a valid number
  try{
    num=std::stoi(commands[1].val());
  }catch(const std::invalid_argument& ia){
    //invalid?
    std::cout << "\e[91m\""+commands[1]+"\" could not be found in this integer-only Binary Tree in the first place :/\n\e[0m";
    return;
  }
  //valid?

  //-2 dont ask way
  int occurances=-2;

  //why use for loops their intended way?
  for(bool didItHappen=true; didItHappen; occurances++, didItHappen=false, root=removeAndReturnNewRoot(root, num, didItHappen)){}
    
  
  if(occurances==1)
    std::cout << "Removed "+commands[1]+'\n';
  else
    std::cout << "Removed " << occurances << " occurances of "+commands[1]+'\n';

}




BinNode<int>* removeAndReturnNewRoot(BinNode<int>* current, int num, bool& didItHappen){
  // std::cout << current << '\n';

  if(current==nullptr)
    return nullptr;

  //it is in/is the right child
  if(current->getValue()<num){
    current->setRight(removeAndReturnNewRoot(current->getRight(), num, didItHappen));
    
  //it is in/is the left child
  }else if(current->getValue()>num){
    current->setLeft(removeAndReturnNewRoot(current->getLeft(), num, didItHappen));
    
  //it's us 
  }else{

    //yes it happened, we found the node and are about to delete it
    didItHappen=true;
    
    /*
    if there are no children return nullptr
    if there is only 1 child, return it
    if there are 2 children return the successor
    */

    
    //we have a left child
    if(current->getLeft()!=nullptr){

      //And we have a right child
      if(current->getRight()!=nullptr){
        auto successor=returnMinNode(current->getRight());
        current->setValue(successor->getValue());
        current->setRight(removeAndReturnNewRoot(current, successor->getValue(), didItHappen));
        return current;
      }

      
      //left child, only child
      auto left=current->getLeft();
      delete current;
      return left;
    }

    //we have a right child
    if(current->getRight()!=nullptr){
      auto right=current->getRight();
      delete current;
      return right;
    }

    //we dont have any children
    return nullptr;
  
  }
  
  return current;
  
}


BinNode<int>* returnNodeWithValueOf(BinNode<int>* current, int num){

  if(current==nullptr)
    return nullptr;
  
  if(current->getValue()==num)
    return current;
  

  BinNode<int>* left=returnMinNode(current->getLeft());

  //which child has the number?
  if(left==nullptr)  
    return returnMinNode(current->getRight());
  return left;


}

BinNode<int>* returnMinNode(BinNode<int>* current){
  while(current->getLeft()!=nullptr)
    current=current->getLeft();
  return current;
}


void printHelp(){

  std::cout << "\e[92m\n";
  std::cout << "(h)elp: this help\n";
  std::cout << "(a)dd <file>: adds integers to the Bin Tree from a file.\n";
  std::cout << "(a)dd <num1> [num2] [num3]...: adds num1, num2, num3... to the Bin Tree.\n";
  std::cout << "(d)isplay: print the Bin Tree in a similar fasion as the command `tree`\n";
  std::cout << "(p)rint: prints every number in a PARENT LEFT_CHILD RIGHT_CHILD format\n";
  std::cout << "(r)emove <num1> [num2] [num3]...: deletes num1, num2, num3... from the Bin Tree\n";
  std::cout << "(c)ontains? <num1> [num2] [num3]...: tells you how many occurances there are of num1, num2, num3... in the Bin Tree\n";
  // std::cout << "(c)ontains? <num1> [num2] [num3]...: tells you how many occurances there are of num1, num2, num3... in the Bin Tree\n";
  std::cout << "(q)uit: closes the program\n";
  // std::cout << "(h)elp: this help\n";
  std::cout << "\e[0m";

}

