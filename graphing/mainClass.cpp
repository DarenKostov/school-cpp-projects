/*
  Daren Kostov

  the MainClass logic



*/


#include "mainClass.h"


MainClass::MainClass(){
}
MainClass::~MainClass(){
}



void MainClass::startProgram(){  
  //do main stuff here


}


void MainClass::probe(Text*){
  //print node stuff

}


void MainClass::addNode(Text* in){
  nodes.insert(in);

  /*add to the 2d table

    we are adding w
    - means 0
    = means any Link* or 0
    + means un-initialized or doesn't exist

    goal:

      a b c w
    a = = = -
    b = = = -
    c = = = -
    w - - - -

  */


  links[in]= std::unordered_map<Text*, unsigned int>();
  /*^^^^^^
      a b c
    a = = =
    b = = =
    c = = =
    w + + +
  */



  for(auto& row : links){
    links[in][row.first]=0;
    /*^^^^^^
        // a b c w
      a = = = +
      b = = = +
      c = = = +
      w - - - -
    */
    links[row.first][in]=0;
    /*^^^^^^
        a b c w
      a = = = -
      b = = = -
      c = = = -
      w + + + -
    */
  
  }

}

void MainClass::removeNode(Text* in){
  
  nodes.erase(in);


  //remove the links associated with this node
  //remove on the Y axis
  for(auto& row : links){
    links[row.first].erase(in);
  }

  //remove on the X axis
  links.erase(in);
  
  delete in;
}

void MainClass::addLink(Text* from, Text* to, int in){
  
  //all of the inputs exist right?
  if(from==nullptr) return;
  if(to==nullptr) return;
  if(in==0) return;

  //connect a node to itself?
  if(from==to) return;

  //we are not overwriting a link right?
  if(links[from][to]!=0) return;

  
  std::cout << "creating link\n";
  
  links[from][to]=in;
  
}


void MainClass::removeLink(Text* from, Text* to){
  links[from][to]=0;
}
