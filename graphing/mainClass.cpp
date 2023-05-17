/*
  Daren Kostov

  the MainClass logic



*/


#include "mainClass.h"
#include "scmdprs.h"
#include <limits.h>

Text const ERROR="\e[91m"; 
Text const ACTION="\e[96m"; 
Text const NORMAL="\e[0m"; 

template<class T>
bool areArgumentsEnought(std::vector<T>, int);

//gives you a number from Text
int getNumber(Text);

//prints how to use the commands
void printHelp();

MainClass::MainClass(){
}
MainClass::~MainClass(){


  //free the memory
  for(auto node : nodes)
    delete node;

}



void MainClass::startProgram(){  
  //do main stuff here

  std::cout << "Welcome to Graphing!\n";
  printHelp();
  
  std::cout << ": ";
  for(auto commands=readLine(); (commands[0]!="q") && (commands[0]!="quit"); std::cout << ": ", commands=readLine()){

    if(commands[0]=="add" || commands[0]=="create" || commands[0]=="make" || commands[0]=="a"){      
      addNodeCommand(commands);
    }else if(commands[0]=="remove" || commands[0]=="delete" || commands[0]=="erase" || commands[0]=="r"){
      removeNodeCommand(commands);
    }else if(commands[0]=="connect" || commands[0]=="c"){
      addLinkCommand(commands);    
    }else if(commands[0]=="disconnect" || commands[0]=="d"){
      removeLinkCommand(commands);    
    }else if(commands[0]=="shortestPath" || commands[0]=="s"){
      getShortestPath(commands);
    }else if(commands[0]=="probe" || commands[0]=="p"){
      probe(commands[1]);
    }else if(commands[0]=="help" || commands[0]=="h"){
      printHelp();
    }else{
      std::cout << ERROR << "?????\n" << NORMAL;
    }
  }

}

void MainClass::getShortestPath(std::vector<Text> commands){

        
        auto node1=getNodeWithName(commands[1]);
        auto node2=getNodeWithName(commands[2]);



            
        if(node1==nullptr){
          std::cout << ERROR << "Node \"" << commands[2] << "\" doesn't exist.\n" << NORMAL;
          return;
        }else if(node2==nullptr){
          std::cout << ERROR << "Node \"" << commands[1] << "\" doesn't exist.\n" << NORMAL;
          return;
        }else if(node1==node2){
          std::cout << ERROR << "Node cannot be the same\n" << NORMAL;
          return;
        }

        std::stack<Text*> shortestPath;
        
        
        int totalCost=findShortestPath(shortestPath, node1, node2);

        if(totalCost==0){
          std::cout << ERROR << "Nodes are not connected\n" << NORMAL;
          return;
        }


        std::cout << "Optimal path:\n" << *node1;
        //make the path
        shortestPath.pop();
        while(!shortestPath.empty()){
          std::cout << "->" << *shortestPath.top();
          shortestPath.pop();
        }

        std::cout << "\nWith the cost of " << totalCost << "\n";
        
}
int MainClass::findShortestPath(std::stack<Text*>& path, Text* from, Text* to){

  std::set<Text*> notVisited;
  std::unordered_map<Text*, int> shortestDistanceFromDestination;
  std::unordered_map<Text*, Text*> previousNode;




  //set up
  for(auto node : nodes){
    notVisited.insert(node);
    shortestDistanceFromDestination[node]=INT_MAX;
    previousNode[node]=nullptr;
  }
  shortestDistanceFromDestination[from]=0;



  while(!notVisited.empty()){

    Text* current=nullptr;

    //get the node with smallest distance
    int val=INT_MAX;
    for(auto node : notVisited){
      if(shortestDistanceFromDestination[node]<val){
        val=shortestDistanceFromDestination[node];
          current=node;
      }
    }
    //there is no connection
    if(val==INT_MAX)
      return 0;

    //get all adjacent nodes
    for(auto node : nodes){
        if(links[current][node]==0)
          continue;


        //if the previous path costed more, replace it with this (cheaper) path
        int linkSum=links[current][node]+shortestDistanceFromDestination[current];
        if(shortestDistanceFromDestination[node]>linkSum){
          previousNode[node]=current;
          shortestDistanceFromDestination[node]=linkSum;
        }
    }

    //we just visited this node
    notVisited.erase(current);

  }


  //store the shortest path
  auto current=to;
  while(current!=nullptr){
    path.push(current);
    current=previousNode[current];
  }


  //return the cost of the shortest path
  return shortestDistanceFromDestination[to];




}


void MainClass::addNodeCommand(std::vector<Text> commands){
  //example: add "this node is cool"

  if(!areArgumentsEnought(commands, 2))
    return;

  if(getNodeWithName(commands[1])!=nullptr){
    std::cout << ERROR << "Node \"" << commands[1] << "\" already exist.\n" << NORMAL;
  }

  addNode(new Text(commands[1]));
  std::cout << ACTION << "Created the node\n" << NORMAL;
  
}
void MainClass::removeNodeCommand(std::vector<Text> commands){
  //example: erase NodeC

  if(!areArgumentsEnought(commands, 2))
    return;

  auto node=getNodeWithName(commands[1]);
  
  if(node==nullptr){
    std::cout << ERROR << "Node \"" << commands[1] << "\" doesn't exist.\n" << NORMAL;
  }

  removeNode(node);
  std::cout << ACTION << "Removed the node\n" << NORMAL;

}
void MainClass::addLinkCommand(std::vector<Text> commands){
  //example: connect pointA pointB 34
  
    //validate the number of arguments
    if(!areArgumentsEnought(commands, 4)){
      return;
    }
    
  
    Text* from=getNodeWithName(commands[1]);
    Text* to=getNodeWithName(commands[2]);
    int value=getNumber(commands[3]);

    if(from==nullptr){
      std::cout << ERROR << "\"" << commands[1] << "\" doesn't exist.\n" << NORMAL;
      return;
    }else if(to==nullptr){
      std::cout << ERROR << "\"" << commands[2] << "\" doesn't exist.\n" << NORMAL;
      return;
    }else if(value==0){
      std::cout << ERROR << commands[3] << " is not a valid integer.\n" << NORMAL;
      return;
    }
  
    //create the link
    addLink(from, to, value);
    std::cout << ACTION << "Created the link\n" << NORMAL;

}
void MainClass::removeLinkCommand(std::vector<Text> commands){
  //example: disconnect pointA pointB
  
    //validate the number of arguments
    if(!areArgumentsEnought(commands, 3)){
      return;
    }
    
  
    Text* from=getNodeWithName(commands[1]);
    Text* to=getNodeWithName(commands[2]);

    if(from==nullptr){
      std::cout << ERROR << "\"" << commands[1] << "\" doesn't exist.\n" << NORMAL;
      return;
    }else if(to==nullptr){
      std::cout << ERROR << "\"" << commands[2] << "\" doesn't exist.\n" << NORMAL;
      return;
    }else if(links[from][to]==0){
      std::cout << ERROR << "Link doesn't exist.\n" << NORMAL;
      return;
    }


    //remove the link
    removeLink(from, to);
    std::cout << ACTION << "Removed the link\n" << NORMAL;

}



Text* MainClass::getNodeWithName(Text label){

  

  //find our node
  for(auto node : nodes){
    if(*node==label){
      return node;
    }
  }
  
  return nullptr;
}

void MainClass::probe(Text in){

  auto node=getNodeWithName(in);
  
  if(node==nullptr){
    std::cout << ERROR << "\"" << in << "\" doesn't exist.\n" << NORMAL;
    return;
  }

  //print to where this node is connected
  for(auto element : links[node]){
    if(element.second!=0){
      std::cout << in << " -(" << element.second << ")-> " << *element.first << "\n"; 
    }
  
  }

  
  // std::cout << "pointed by:\n";
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

template<class T>
bool areArgumentsEnought(std::vector<T> vect, int amount){
    if((int)vect.size()<amount){
      std::cout << ERROR << "Not enough arguments.\n" << NORMAL;
      return false;
    }else if((int)vect.size()>amount){
      std::cout << ERROR << "Too many arguments.\n" << NORMAL;
      return false;
    }

  return true;

}

int getNumber(Text in){
  
  int num=0;
  
    try{
      num=std::stoi(in.val());
    }catch(const std::invalid_argument& ia){
      return 0;
    }
  return num;

}

void printHelp(){

  std::cout << "(h)elp: this help\n";
  std::cout << "(a)dd/create/make <label>: make a node with a label\n";
  std::cout << "(r)emove/delete/erase <label>: removes a node with a label\n";
  std::cout << "(c)onnect <from> <to> <weight of link>: makes a link from node to node with a certain cost\n";
  std::cout << "(d)isconnect <from> <to>: destroys the links from node to node\n";
  std::cout << "(s)hortestPath <from> <to>: tell's you the shortest path from node to node\n";
  std::cout << "(p)robe: tells you to what a node is connecting (pointing) to\n";
  std::cout << "\nYou can use quotes to have spaces in a label. ex:\n";
  std::cout << "make \"cool node\"\n";
  std::cout << "connect \"cool node\" \"some other node\" 32\n";


}


