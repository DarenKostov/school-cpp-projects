/*
  Daren Kostov

  the MainClass logic


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

void MainClass::startProgram(){
  

  // char command[20]="";
  

  // std::cout << "press \"a\" and then Enter, this is not a bug, just press \"a\" and then Enter";
  std::cout << "[BinTree]: ";
  for(std::vector<Text> commands=readLine(); commands[0]!="quit"; commands=readLine()){
  

    if(commands[0][0]=='a'){
      addToBinTree(root, commands);
    }else if(commands[0][0]=='d'){
      display(root);
    }else if(commands[0][0]=='p'){
      print(root);
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
  std::cout << "r";
  std::cout << current->getValue() << "\n";

  
    
  
  displayLeft(current->getLeft(), current, inheritance);
  displayRight(current->getRight(), inheritance);

  

}

void displayLeft(BinNode<int>* current, BinNode<int>* previous, Text inheritance){


  //we arent in the heap? dont display us
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
  std::cout << "l";
  std::cout << current->getValue() << "\n";
  
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




