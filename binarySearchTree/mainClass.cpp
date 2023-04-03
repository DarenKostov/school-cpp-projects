/*
  Daren Kostov

  the MainClass logic


*/

#include "mainClass.h"
#include "iostream"
#include "vector"//does not relate to the binary tree
#include "text.h"
#include "scmdprs.h"

MainClass::MainClass(){}
MainClass::~MainClass(){}


//adds an int to the bin tree
void add(BinNode<int>*& , int);


void MainClass::startProgram(){
  

  // char command[20]="";
  

  for(std::vector<Text> commands=readLine(); commands[0]!="quit"; commands=readLine()){

    // if(commands[0]=="add"){
      
    //   try{
        
    //   }catch(const std::invalid_argument& ia){
      
    //   }
    // }
    
    std::cout << "your arguments:\n";
    for(Text command : commands)
    std::cout << command+'\n';

  }



  
}















