/*
  Daren Kostov

  the MainClass logic

  sources:
  https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

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

//adds an int to the bin tree (some return what type of node it added)
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


//gives you how many nodes there are of particular color or all
int count(BinNode<int>*);
int countRed(BinNode<int>*);
int countBlack(BinNode<int>*);

void printHelp();

MainClass::MainClass(){
  root=nullptr;
  redVsBlack=std::make_pair(0, 0);
}
MainClass::~MainClass(){
  deleteAll(root);
  root=nullptr;
}

void MainClass::startProgram(){
  
  std::cout << "Welcome to this replresentation of Red-Black Tree!\n";

  printHelp();

  std::cout << "Welcome to this replresentation of Red-Black Tree!\n";
  
  std::cout << "\n[" << RED << "0" << NORMAL << "/" << BLACK << "0" << NORMAL << "~0]: ";
  for(std::vector<Text> commands=readLine(); (commands[0]!="q") && (commands[0]!="quit"); std::cout << "\n[" << RED << redVsBlack.first << NORMAL << "/" << BLACK << redVsBlack.second << NORMAL << "~" << redVsBlack.first+redVsBlack.second << "]: ", commands=readLine()){
    if(commands[0]=="add" || commands[0]=="a"){
      addToBinTree(root, commands);
      redVsBlack.first=countRed(root);
      redVsBlack.second=countBlack(root);
    }else if(commands[0]=="d" || commands[0]=="display"){
      display(root);
    }else if(commands[0]=="r" || commands[0]=="remove"){
      std::cout << "not yet implemented :/\n";
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
      while(getline(file, number, ' ')){
        if(number.len()==0) 
          continue;

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


  // display(root);
  
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

      parent->setColor('b');
      if(uncle!=nullptr)
        uncle->setColor('b');

      if(grandparent!=nullptr){
        grandparent->setColor('r');
        //fix the grand parent
        fixAroundThis(root, grandparent);
        }    

      return;
    }
  }

  //if the parent is red but uncle black (the parent must be red beacause of case 2) (the uncle must be black beacause of case 3)

  //case 4
  
  //we are right and parent is left OR we are left and parent is right
  if(current->getRelation()+parent->getRelation()=='r'+'l'){//cool char math

    //do magic
    rotateTree(root, current);

    current=parent;
    parent=parent->getParent();
    
    // return;
  }

  //case 5
  //we are right and parent is right OR we are left and parent is left
  if(current->getRelation()==parent->getRelation()){
    
    //do magic
    rotateTree(root, parent);
    
    //invserse colors
    current->getParent()->setColor('b');//grandparent
    getSibling(current)->setColor('r');//parent

    return;
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

  /*
  things to set up:
    
    rl=grandparent child

    rl=current, parent
    l=current, right child
    r=current, left child
    rl=current, relation
    
    rl=parent, parent
    l=parent, left child
    r=parent, right child
    rl=parent, relation
    

    current left child, parent
    current right child, parent
    current left child, relation
    current right child, relation
    

  */
  
    auto parent=current->getParent();
    BinNode<int>* subTree;
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
      
      subTree=current->getLeft();
      
      //move the parent to the childs position (left this time)
      current->setLeft(parent);
      parent->setRelation('l');

      //fix subTrees
      parent->setRight(subTree);
      if(subTree!=nullptr){
        subTree->setRelation('r');
        subTree->setParent(parent);
      }
    //right rotation
    }else{

  
      subTree=current->getRight();
      
      //move the parent to the childs position (right this time)
      current->setRight(parent);
      parent->setRelation('r');

      //fix subTrees
      parent->setLeft(subTree);
      if(subTree!=nullptr){
        subTree->setRelation('l');
        subTree->setParent(parent);
      }
    
    }

  
  
  //misc fixes
  parent->setParent(current);
  current->setRelation(parentSide);
  
}

int count(BinNode<int>* in){
  if(in==nullptr)
    return 0;
  return count(in->getLeft())+count(in->getRight())+1;
}

int countRed(BinNode<int>* in){
  if(in==nullptr)
    return 0;
  // return count(in);
  return countRed(in->getLeft())+countRed(in->getRight())+(in->getColor()=='r');
}

int countBlack(BinNode<int>* in){
  if(in==nullptr)
    return 0;
  
  return countBlack(in->getLeft())+countBlack(in->getRight())+(in->getColor()=='b');
}
void printHelp(){

    std::cout << "(h)elp: this help\n";
    std::cout << "(a)dd <file1/num1> [file2/num2]...: adds integers from files OR console to the Bin Tree from a file.\n\t(you can add multiple numbers and/or files with one command.)\n";
    std::cout << "(d)isplay: print the Bin Tree in a similar fasion as the command `tree`\n";
    std::cout << "(r)emove <num1> [num2] [num3]...: deletes num1, num2, num3... from the Bin Tree\n";
    std::cout << "(rev)erse: reverses the colors for Red and Black\n\t(these should really be global consts but if someone REALLY needs/wants to switch them they can)\n";
    std::cout << "(q)uit: closes the program\n";

  std::cout << "\n[" << RED << "red" << NORMAL << "/" << BLACK << "black (real)" << NORMAL << "~total]: ";
}