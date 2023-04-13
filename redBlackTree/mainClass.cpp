/*
  Daren Kostov

  the MainClass logic



*/

#include "text.h"
#include "mainClass.h"
#include "scmdprs.h"
#include <fstream>
#include <charconv>
#include <unistd.h>
#include <stdlib.h>

Text BLACK="\e[41;30m";
Text RED="\e[40;31m";
Text NORMAL="\e[0m";

//deletes all children of this node, including the node itself
void deleteAll(BinNode<int>*);

//displays the bin tree, left child is displayed first thast why we it needs more parameters
void display(BinNode<int>*);
void displayLeft(BinNode<int>*, BinNode<int>*, Text);
void displayRight(BinNode<int>*, Text);

//adds an int to the bin tree
void add(BinNode<int>*& , int);
void add(BinNode<int>*&, BinNode<int>*, BinNode<int>*, char, int);
void addToBinTree(BinNode<int>*&, std::vector<Text>);

//fixes the node structure around this node
void fixAroundThis(BinNode<int>*&, BinNode<int>*);

//gives you the color, even if its NULL
char getColor(BinNode<int>*);


//gives you the sibling, be it right or left
BinNode<int>* getSibling(BinNode<int>*);

//rotates the tree given a child, will account for root
void rotateTree(BinNode<int>*&, BinNode<int>*);

MainClass::MainClass(){
  root=nullptr;
  redVsBlack=std::make_pair(0, 0);
}
MainClass::~MainClass(){
  deleteAll(root);
  root=nullptr;
}

void MainClass::startProgram(){
  


  std::cout << "\n[" << RED << "red" << NORMAL << "/" << BLACK << "black" << NORMAL << "]: ";
  for(std::vector<Text> commands=readLine(); (commands[0]!="q") && (commands[0]!="quit"); std::cout << "\n[" << RED << "red" << NORMAL << "/" << BLACK << "black" << NORMAL << "]: ", commands=readLine()){
    if(commands[0]=="add" || commands[0]=="a"){
      addToBinTree(root, commands);
    }else if(commands[0]=="d" || commands[0]=="display"){
      display(root);
    }else if(commands[0]=="rev" || commands[0]=="reverse"){
      Text tmp=BLACK; BLACK=RED; RED=tmp;
    }else{
      std::cout << "\e[91m????????\e[0m\n";
    }


    
  }
  

}

//==ADDING

void addToBinTree(BinNode<int>*& root, std::vector<Text> commands){


  if(commands.size()==1){
      std::cout << "\e[91mAdded nothing to the Bin Tree!\n\e[0m";
      return;
  }

  int count=0;
  for(int i=1; i<commands.size(); i++){

    int numToAdd=0;

    //do we give a number or a file?
    try{
      numToAdd=std::stoi(commands[i].val());
    }catch(const std::invalid_argument& ia){
      //file?

      std::ifstream file(commands[i].val());

      //something wrong with the file?
      if(!file.good()){
        std::cout << "\e[91mFile where?\n";
        std::cout << "If \"" << commands[i] << "\" was supposed to be a number, this program failed to recognize that.\n\e[0m";
        return;
      }


      //add the numbers in the file to the bin tree
      Text number;
      while (getline(file, number, ' ')){
        add(root, std::stoi(number.val()));
        count++;
      }
      file.close();

      continue;
    }

    //number?  
    add(root, numToAdd);
    count++;
  }

  
    if(count==1)
      std::cout << "Added 1 number to the Bin Tree\n";
    else
      std::cout << "Added " << count << " numbers to the Bin Tree\n";
  
}

void add(BinNode<int>*& root, int numToAdd){
  //root doesnt exists yet?
  if(root==nullptr){
    root=new BinNode<int>(numToAdd, 'b', 'x');
    return;
  }

  //give the number to the appropriate child
  if(numToAdd<root->getValue()){
    add(root, root->getLeft(), root, 'l', numToAdd);  
  }else{
    add(root, root->getRight(), root, 'r', numToAdd);  
  }
}


void add(BinNode<int>*& root, BinNode<int>* current, BinNode<int>* previous, char whichChild, int numToAdd){
  //root doesnt exists yet?
  if(current==nullptr){

    //init the child
    auto newNode=new BinNode<int>(numToAdd, 'r', 'x');

    //immidiatly add the child
    if(whichChild=='l'){
      previous->setLeft(newNode);
      newNode->setRelation('l');
    }else{
      previous->setRight(newNode);
      newNode->setRelation('r');
    }

    //fix the childs color/position
    newNode->setParent(previous);
    fixAroundThis(root, newNode);
    return;
  }

  //give the number to the appropriate child
  if(numToAdd<current->getValue()){
    add(root, current->getLeft(), current, 'l', numToAdd);  
  }else{
    add(root, current->getRight(), current, 'r', numToAdd);  
  }
}



//==FIXING

void fixAroundThis(BinNode<int>*& root, BinNode<int>* current){


  //I use getColor because the uncle might be null (who knows the parent could also be null for some reason)  

  if(current==nullptr){
    std::cout << "\e[91mNo current!\nI dont know how that happened...\e[0m\n";
    return;
  }

  //case 1
  if(root==current){
    root->setColor('b');
    return;
  }

  auto parent=current->getParent();  
  
  //case 2 
  if(getColor(parent)=='b'){
    //do nothing
    return;
  }

  //extra {} because we dont need uncle/grandparent outside of this
  {
    auto uncle=getSibling(parent);
    auto grandparent=parent->getParent();
    //case 3
    if(getColor(parent)+getColor(uncle)=='r'*2){//yeah multiplying chars
      //reverse color of all uncles/grandparents
      uncle->setColor('b');
      parent->setColor('b');
      grandparent->setColor('r');

      //fix the grand parent
      fixAroundThis(root, grandparent);    
      return;
    }
  }

  //if the parent is red but uncle black (the parent must be red beacause of case 2) (the uncle must be black beacause of case 3)

  //case 4
  
  //we are right and parent is left OR we are left and parent is right
  if(current->getRelation()+parent->getRelation()=='r'+'l'){//cool char math
    std::cout << "call case 4\n"<< std::flush;
    //do magic
    rotateTree(root, current);
    
  }

  //case 5
  //we are right and parent is right OR we are left and parent is left
  if(current->getRelation()==current->getParent()->getRelation()){
    //do magic
    rotateTree(root, parent);
  }

  std::cout << "\e[91mHow did we get here??????????????\?/\e[0m\n";
  
}


//==DISPLAYING

void display(BinNode<int>* root){

  //lets save us a seg fault
  if(root==nullptr)
    return;

  std::cout << "\n" << BLACK << "x" << NORMAL << root->getValue() << "\n" << std::flush;
  displayLeft(root->getLeft(), root, "");
  displayRight(root->getRight(), "");

}


void displayRight(BinNode<int>* current, Text inheritance){
  // usleep(10000);


  //we arent in the bin tree? dont display us
  if(current==nullptr)
    return;


  Text myInheritance;
  for(int i=0; i<inheritance.len(); i++){
    myInheritance+=inheritance[i];
  }



  std::cout << myInheritance;


  //adjust position
  std::cout << "└─" << std::flush;
  inheritance+="  ";



  //print our value
  if(current->getColor()=='r')
    std::cout << RED << std::flush;
  else
    std::cout << BLACK << std::flush;
  std::cout << "r" << NORMAL << std::flush;
  std::cout << current->getValue() << "\n" << std::flush;

  
    
  
  displayLeft(current->getLeft(), current, inheritance);
  displayRight(current->getRight(), inheritance);

  

}

void displayLeft(BinNode<int>* current, BinNode<int>* previous, Text inheritance){
  // usleep(10000);


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
    std::cout << "└─" << std::flush;
    inheritance+="  ";
  }else{
    std::cout << "├─" << std::flush;
    inheritance+="│ ";
  }
  


  //print our value
  if(current->getColor()=='r')
    std::cout << RED << std::flush;
  else
    std::cout << BLACK << std::flush;
  std::cout << "l\e[0m" << std::flush;
  std::cout << current->getValue() << "\n" << std::flush;
  
  displayLeft(current->getLeft(), current, inheritance);
  displayRight(current->getRight(), inheritance);
}

void deleteAll(BinNode<int>* current){

  if(current==nullptr)
    return;

  //first delete the children
  deleteAll(current->getLeft());
  deleteAll(current->getRight());

  //then delete ourselves
  delete current;

}


char getColor(BinNode<int>* in){
  if(in==nullptr)
    return 'b';
  return in->getColor();
}

BinNode<int>* getSibling(BinNode<int>* in){
  char mySide=in->getRelation();
  
  if(mySide=='r')
    return in->getParent()->getLeft();
  return in->getParent()->getRight();

}


void rotateTree(BinNode<int>*& root, BinNode<int>* current){

    auto parent=current->getParent();
    BinNode<int>* subTree[3];
    char parentSide=parent->getRelation();

    {
      auto grandparent=parent->getParent();
      //move the child to the parents position (is the parent root?, make the child root)
      if(grandparent==nullptr)
        root=current;
      else
        if(parentSide=='l')
          grandparent->setLeft(current);
        else
          grandparent->setRight(current);

      current->setParent(grandparent);
    }
    
  
    //left rotation
    if(current->getRelation()=='r'){
      
      subTree[0]=parent->getLeft();//we know its the left child, no need to use get siblings
      subTree[1]=current->getLeft();
      subTree[2]=current->getRight();
      
      //move the parent to the childs position (left this time)
      current->setLeft(parent);
      parent->setRelation('l');

      //fix subTrees
      parent->setLeft(subTree[0]);
      parent->setRight(subTree[1]);
      current->setRight(subTree[2]);
      subTree[1]->setRelation('r');
      
    //right rotation
    }else{

  
      subTree[0]=current->getLeft();//we know its the left child, no need to use get siblings
      subTree[1]=current->getRight();
      subTree[2]=parent->getRight();
      
      //move the parent to the childs position (right this time)
      current->setRight(parent);
      parent->setRelation('r');

      //fix subTrees
      current->setLeft(subTree[0]);
      parent->setLeft(subTree[1]);
      parent->setRight(subTree[2]);
      subTree[1]->setRelation('l');
  
    }
  
  //fix the childs side
  current->setRelation(parentSide);
  
}
