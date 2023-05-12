/*
  Daren Kostov

  the MainClass logic

  sources:
  https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
  https://www.youtube.com/watch?v=lU99loSvD8s
  https://www.youtube.com/watch?v=iw8N1_keEWA
  https://www.techiedelight.com/deletion-from-bst/

*/

#include "binnode.h"
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
Text GREEN="\e[92m";
Text BLUE="\e[94m";
Text CYAN="\e[96m";


//deletes all children of this node, including the node itself
void deleteAll(BinNode<int>*);

//displays the bin tree, left child is displayed first thats why we it needs more parameters
void display(BinNode<int>*);
void displayLeft(BinNode<int>*, BinNode<int>*, Text);
void displayRight(BinNode<int>*, Text);

//like display but on a local level
void displayLocal(BinNode<int>*);

//adds an int to the bin tree, returns true if the task was successfull
bool add(BinNode<int>*& , int);
bool add(BinNode<int>*&, BinNode<int>*, BinNode<int>*, char, int);
void addCommand(BinNode<int>*&, std::vector<Text>);

//fixes the node structure around this node after adding
void fixAroundThisAfterAdding(BinNode<int>*&, BinNode<int>*);



//remove a num from the bin tree
void removeCommand(BinNode<int>*&, std::vector<Text>);
void remove(BinNode<int>*&, BinNode<int>*);

//erases a node, all connections to it will point to nullptr, and also deletes the node
void erase(BinNode<int>*&, BinNode<int>*);


//moves Node B into the place of Node A (be careful, A will be lost if you don't have a pointer to it)
void transplant(BinNode<int>*&, BinNode<int>*, BinNode<int>*);

//fixes the node structure around this node after deleting
void fixAroundThisAfterDeleting(BinNode<int>*&, BinNode<int>*);


//gives you the color, even if its NULL
char getColor(BinNode<int>*);


//gives you the sibling, be it right or left
BinNode<int>* getSibling(BinNode<int>*);

//rotates the tree given a child, will account for root
/*
  You give the function node X

      O
     / \
    O   X
       / \
      O   O
  
*/

void rotateTree(BinNode<int>*&, BinNode<int>*);

//gives you how many nodes there are of particular color or all
int count(BinNode<int>*);
int countRed(BinNode<int>*);
int countBlack(BinNode<int>*);

//returns you the bin node whoose value is the int, nullptr if the node doesnt exist
BinNode<int>* returnNodeWithValueOf(BinNode<int>*, int);
BinNode<int>* fullSearch(BinNode<int>*, int);

//tells you weather a node with value i exists
void searchCommand(BinNode<int>*, std::vector<Text>);


//returns you the bin node with the lowest value, if it doesnt exist
BinNode<int>* returnMinNode(BinNode<int>*);

//returns you the bin node with the highest value, if it doesnt exist
BinNode<int>* returnMaxNode(BinNode<int>*);


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
  

  printHelp();

  std::cout << "Welcome to this representation of Red-Black Tree!\n\n";
  std::cout << "Try (file should be included with the project): " << CYAN << "add 554 nums.txt 37 482 329\n" << NORMAL;
  std::cout << "Then try " << CYAN << "remove 577 334 764 123 888\n" << NORMAL;
  std::cout << "(I also made it impossible to have duplicates)\n";
  // std::cout << "I have varified this works exactly as expect with:  https://www.cs.usfca.edu/~galles/visualization/RedBlack.html\n";

  
  std::cout << "\n[" << RED << "0" << NORMAL << "/" << BLACK << "0" << NORMAL << "~0]: ";
  for(std::vector<Text> commands=readLine(); (commands[0]!="q") && (commands[0]!="quit"); std::cout << "\n[" << RED << redVsBlack.first << NORMAL << "/" << BLACK << redVsBlack.second << NORMAL << "~" << redVsBlack.first+redVsBlack.second << "]: ", commands=readLine()){
    if(commands[0]=="add" || commands[0]=="a"){
      addCommand(root, commands);
      redVsBlack.first=countRed(root);
      redVsBlack.second=countBlack(root);
    }else if(commands[0]=="d" || commands[0]=="display"){
      display(root);
    }else if(commands[0]=="s" || commands[0]=="search"){
      searchCommand(root, commands);
    }else if(commands[0]=="h" || commands[0]=="help"){
      printHelp();
      std::cout << '\n';
    }else if(commands[0]=="r" || commands[0]=="remove" || commands[0]=="rm"){
      removeCommand(root, commands);
      redVsBlack.first=countRed(root);
      redVsBlack.second=countBlack(root);
    }else if(commands[0]=="rmall"){
      while(root!=nullptr){
        std::cout << "Removing " << root->getValue() << "\n" << std::flush;
        remove(root, root);
      }
      redVsBlack.first=0;
      redVsBlack.second=0;
    }else if(commands[0]=="rev" || commands[0]=="reverse"){
      Text tmp=BLACK; BLACK=RED; RED=tmp;
    }else{
      std::cout << "\e[91m????????\e[0m\n";
    }


    
  }
  

}


void transplant(BinNode<int>*& root, BinNode<int>* toBeReplaced, BinNode<int>* replacement){

  //set up parent  
  switch(toBeReplaced->getRelation()){
    case 'x':
      root=replacement;
      break;
    case 'r':
      toBeReplaced->getParent()->setRight(replacement);
      break;
    case 'l':
      toBeReplaced->getParent()->setLeft(replacement);
      break;
  }

  //set up child
  replacement->setParent(toBeReplaced->getParent());
}


//==SEARCHING
void searchCommand(BinNode<int>* root, std::vector<Text> commands){


  if(commands.size()==1){
      std::cout << "\e[91mSearched nothing in the Bin Tree!\n\e[0m";
      return;
  }

  int count=0;
  for(int i=1; i<(int)commands.size(); i++){

    int num=0;

    //do we give a number or a file?
    try{
      num=std::stoi(commands[i].val());
    }catch(const std::invalid_argument& ia){
      std::cout << "\e[91m" << commands[i] << " is not a number?\n\e[0m";
      continue;
    }

    auto node=returnNodeWithValueOf(root, num);
    if(node!=nullptr){
      std::cout<< commands[i] << " was located.\n\n"; 
      displayLocal(node);
    }else
      std::cout<< commands[i] << " was not located.\n"; 
  }
  
}



//==ADDING

void addCommand(BinNode<int>*& root, std::vector<Text> commands){


  if(commands.size()==1){
      std::cout << "\e[91mAdded nothing to the Bin Tree!\n\e[0m";
      return;
  }

  int count=0;
  for(int i=1; i<(int)commands.size(); i++){

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

        int num=0;

        //is this a valid number
        try{
          num=std::stoi(number.val());
        }catch(const std::invalid_argument& ia){
          //invalid?
          std::cout << "\e[91m\""+commands[i]+"\" is not an integer :/ fix the file\n\e[0m";
          continue;
        }

        if(add(root, num))
          count++;
      }
      file.close();

      continue;
    }

    //number?  
    if(add(root, numToAdd))
      count++;
  }

  
    if(count==1)
      std::cout << "Added 1 number to the Bin Tree\n";
    else
      std::cout << "Added " << count << " numbers to the Bin Tree\n";
  
}

bool add(BinNode<int>*& root, int numToAdd){
  //root doesnt exists yet?
  if(root==nullptr){
    root=new BinNode<int>(numToAdd, 'b');
    return true;
  }


  //no duplicates!
  if(root->getValue()==numToAdd){
    return false;
  }

  //give the number to the appropriate child
  if(numToAdd<root->getValue()){
    return add(root, root->getLeft(), root, 'l', numToAdd);  
  }else{
    return add(root, root->getRight(), root, 'r', numToAdd);  
  }
}


bool add(BinNode<int>*& root, BinNode<int>* current, BinNode<int>* previous, char whichChild, int numToAdd){
  //"root" doesnt exists yet?
  if(current==nullptr){

    
    //init the child
    auto newNode=new BinNode<int>(numToAdd, 'r');

    //immidiatly add the child
    if(whichChild=='l'){
      previous->setLeft(newNode);
    }else{
      previous->setRight(newNode);
    }

    //fix the childs color/position
    newNode->setParent(previous);
    fixAroundThisAfterAdding(root, newNode);

    return true;
  }

  //no duplicates!
  if(current->getValue()==numToAdd){
    return false;
  }
    
  
  //give the number to the appropriate child
  if(numToAdd<current->getValue()){
    return add(root, current->getLeft(), current, 'l', numToAdd);  
  }else{
    return add(root, current->getRight(), current, 'r', numToAdd);  
  }

  
}



//==FIXING AFTER ADDING

void fixAroundThisAfterAdding(BinNode<int>*& root, BinNode<int>* current){


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
        fixAroundThisAfterAdding(root, grandparent);
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

//==REMOVING

void removeCommand(BinNode<int>*& root, std::vector<Text> commands){

  if(commands.size()==1){
      std::cout << "\e[91mRemoved 0 occurances of nothing!\n\e[0m";
      return;
  }

  for(int i=1; i<(int)commands.size(); i++){

    int num=0;

    //is this a valid number
    try{
      num=std::stoi(commands[i].val());
    }catch(const std::invalid_argument& ia){
      //invalid?
      std::cout << "\e[91m\""+commands[i]+"\" is not an integer :/\n\e[0m";
      return;
    }
    //valid?



    auto toBeDeleted=returnNodeWithValueOf(root, num);
    if(toBeDeleted){
      remove(root, toBeDeleted);
      std::cout << "Removed "+commands[i]+'\n';
    }else
      std::cout << "No occurances of "+commands[i]+'\n';
  

  }

}

void remove(BinNode<int>*& root, BinNode<int>* toBeDeleted){

  
  if(toBeDeleted==nullptr)
    return;



  //give us the only child; if none, make a new child; if two give us none
  BinNode<int>* child=
    toBeDeleted->getLeft()?
      toBeDeleted->getRight()?
        nullptr : //there are 2 children
        toBeDeleted->getLeft() ://there is only the left child
      toBeDeleted->getRight()?
        toBeDeleted->getRight() : //there is only the right child
        new BinNode<int>(0, 'B');//there are no children

  
  //=we have 2 children    
  if(child==nullptr){

    auto successor=returnMinNode(toBeDeleted->getRight());
    // auto successor=returnMaxNode(toBeDeleted->getLeft());
    toBeDeleted->setValue(successor->getValue());

    //remove the one we just swapped with
    remove(root, successor);
    return;
 }

  //we have 1 child or none
  

  char childRelation=child->getRelation();
  char childColor=child->getColor();

  transplant(root, toBeDeleted, child);


  
  //double black
  if(getColor(child)+getColor(toBeDeleted)=='b'*2){
    fixAroundThisAfterDeleting(root, child);
  }
  

  //delete the child if it was suposed to be nullptr
  if(childColor=='B'){
    erase(root, child);
  }
  
  delete toBeDeleted;
    
}

//==FIX AFTER REMOVING

void fixAroundThisAfterDeleting(BinNode<int>*& root, BinNode<int>* current){


  
  while(current!=root && getColor(current)=='b'){

    
    BinNode<int>* sibling=getSibling(current);
    char currentRelation=current->getRelation();

    // case 1
    //sibling is red
    if(getColor(sibling)=='r'){
      sibling->setColor('b');
      current->getParent()->setColor('r');
      rotateTree(root, sibling);
      sibling=getSibling(current);
    }

    //=sibling is black from now on
    
    // case 2

    //sibling doesnt exist? we have balanced the tree!
    if(sibling==nullptr)
      break;
    
    //the siblings children are black
    if(getColor(sibling->getLeft())+getColor(sibling->getRight())=='b'*2){
      sibling->setColor('r');
      current=current->getParent();
      continue;
    }

    //=children of sibling are either rr rb br from now on


    //are we right or left child
    if(currentRelation=='l'){
      
      // case 3
      //the left child of the sibling is red, the right child of the sibling is black
      if(getColor(sibling->getRight())=='b'){
        sibling->getLeft()->setColor('b');
        sibling->setColor('r');
        rotateTree(root, sibling->getLeft());
        sibling=getSibling(current);
      }

      //=children of sibling are either rr br from now on

      //case 4
      //the right child of the sibling is red

      sibling->setColor(getColor(sibling->getParent()));
      sibling->setColor('b');
      sibling->getRight()->setColor('b');
      rotateTree(root, sibling);
      current=root;

    }else{
    
      // case 3
      //the left child of the sibling is red, the right child of the sibling is black
      if(getColor(sibling->getLeft())=='b'){
        sibling->getRight()->setColor('b');
        sibling->setColor('r');
        rotateTree(root, sibling->getRight());
        sibling=getSibling(current);
      }

      //=children of sibling are either rr rb from now on

      //case 4
      //the right child of the sibling is red

      sibling->setColor(getColor(sibling->getParent()));
      sibling->setColor('b');
      sibling->getLeft()->setColor('b');
      rotateTree(root, sibling);
      current=root;
    
    }
        

  }

  //we are root, we must be black
  current->setColor('b');

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

void erase(BinNode<int>*& root, BinNode<int>* toBeErased){

  //fix children
  if(toBeErased->getRight()!=nullptr)
    toBeErased->getRight()->setParent(nullptr);
  if(toBeErased->getLeft()!=nullptr)
    toBeErased->getLeft()->setParent(nullptr);

  //fix parent
  auto parent=toBeErased->getParent();
  if(parent!=nullptr){
      if(toBeErased->getRelation()=='r')
        parent->setRight(nullptr);
      else
        parent->setLeft(nullptr);
   
  }else{
    root=nullptr;
  }

  
  delete toBeErased;

}

char getColor(BinNode<int>* in){
  if(in==nullptr)
    return 'b';

 if(in->getColor()=='B')
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
    char currentNodeRelation=current->getRelation();

    {
      auto grandparent=parent->getParent();

      //move the child to the parents position (is the parent root?, make the child root)
      if(grandparent==nullptr)
        root=current;
      else
        if(parent->getRelation()=='l')
          grandparent->setLeft(current);
        else
          grandparent->setRight(current);

      current->setParent(grandparent);
    }

    
  
    //left rotation
    if(currentNodeRelation=='r'){
      
      subTree=current->getLeft();
      
      //move the parent to the childs position (left this time)
      current->setLeft(parent);
      // parent->setRelation('l');

      //fix subTrees
      parent->setRight(subTree);
      if(subTree!=nullptr){
        // subTree->setRelation('r');
        subTree->setParent(parent);
      }
    //right rotation
    }else{

  
      subTree=current->getRight();
      
      //move the parent to the childs position (right this time)
      current->setRight(parent);
      // parent->setRelation('r');

      //fix subTrees
      parent->setLeft(subTree);
      if(subTree!=nullptr){
        // subTree->setRelation('l');
        subTree->setParent(parent);
      }
    
    }

  
  
  //misc fixes
  parent->setParent(current);
  // current->setRelation(parentSide);
  
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

BinNode<int>* returnNodeWithValueOf(BinNode<int>* current, int num){

  while(current!=nullptr && current->getValue()!=num){
    if(current->getValue()<num)
      current=current->getRight();
    else
      current=current->getLeft();
  }

  return current;
  
  if(current==nullptr) //do we exist
    return nullptr;
  if(current->getValue()==num) //we found the node
    return current;
  if(current->getValue()>num) //it should be somewhere on the left branch 
    return returnNodeWithValueOf(current->getLeft(), num);
  if(current->getValue()<num) //it should be somehwere on the right branch
    return returnNodeWithValueOf(current->getRight(), num);
  
  std::cout << "how did we get here?\n";
  return nullptr;
}


BinNode<int>* fullSearch(BinNode<int>* current, int num){
  
  if(current==nullptr) //do we exist
    return nullptr;
  if(current->getValue()==num) //we found the node
    return current;

  auto left=returnNodeWithValueOf(current->getLeft(), num);
  if(left==nullptr)
    return returnNodeWithValueOf(current->getRight(), num);
  return left;
  
}



BinNode<int>* returnMinNode(BinNode<int>* current){
  while(current->getLeft()!=nullptr)
    current=current->getLeft();
  return current;
}
BinNode<int>* returnMaxNode(BinNode<int>* current){
  while(current->getRight()!=nullptr)
    current=current->getRight();
  return current;
}



// void displayLocal(BinNode<int>* in){

//   if(in->getParent()!=nullptr)  
//     std::cout << "\t";
  
//      <<   std::cout << BLACK << std::flush;
//   std::cout << "l\e[0m" << std::flush;
//   std::cout << current->getValue() 


// }



void printHelp(){

    std::cout << GREEN << "(h)elp" << NORMAL << ": this help\n";
    std::cout << GREEN << "(a)dd" << BLUE << " <file1/num1> [file2/num2]..." << NORMAL << ": adds integers from files OR console to the Bin Tree from a file.\n\t(you can add multiple numbers and/or files with one command.)\n";
    std::cout << GREEN << "(s)earch" << BLUE << " <num1> [num2] [num3]..." << NORMAL << ": tells you whether num1, num2, num3... exist in the Bin Tree\n";
    std::cout << GREEN << "(d)isplay" << NORMAL << ": print the Bin Tree in a similar fasion as the command `tree`\n";
    std::cout << GREEN << "(r)emove" << BLUE << " <num1> [num2] [num3]..." << NORMAL << ": deletes num1, num2, num3... from the Bin Tree\n";
    std::cout << GREEN << "(rev)erse" << NORMAL << ": reverses the colors for Red and Black\n\t(these should really be global consts but if someone REALLY needs/wants to switch them they can)\n";
    std::cout << GREEN << "rmall" << NORMAL << ": deletes every number from the Bin Tree\n";
    std::cout << GREEN << "(q)uit" << NORMAL << ": closes the program\n";

    std::cout << "\n[" << RED << "red" << NORMAL << "/" << BLACK << "black (real)" << NORMAL << "~total]: ";
}