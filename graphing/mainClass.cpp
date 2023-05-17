/*
  Daren Kostov

  the MainClass logic



*/


#include "mainClass.h"
#include "scmdprs.h"


MainClass::MainClass(){
}
MainClass::~MainClass(){


  //free the memory
  for(auto node : nodes)
    delete node;

}



void MainClass::startProgram(){  
  //do main stuff here

  std::cout << ": ";
  for(auto commands=readLine(); (commands[0]!="q") && (commands[0]!="quit"); std::cout << ": ", commands=readLine()){

    if(commands[0]=="add" || commands[0]=="create" || commands[0]=="make"){      
      addSomethingCommand(commands);
    }else if(commands[0]=="remove" || commands[0]=="delete" || commands[0]=="erase"){
      removeSomethingCommand(commands);
    }else if(commands[0]=="connect"){
      addLinkCommand(commands);    
    }else if(commands[0]=="disconnect"){
      removeLinkCommand(commands);    
    }else if(commands[0]=="shortestPath"){

    }
    
  }

}






void MainClass::probe(Text* in){
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
