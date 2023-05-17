/*
  Daren Kostov

  the MainClass logic



*/


#include "mainClass.h"
#include "scmdprs.h"


Text const ERROR="\e[93m"; 
Text const NORMAL="\e[0m"; 

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


void MainClass::addSomethingCommand(std::vector<Text> command){

  //add a single node
  if(command[1]=="node" || command[1]=="vertex"){


  //add multiple nodes
  }else if(command[1]=="nodes" || command[1]=="vertices"){

  //add a single link in one direction
  }else if(command[1]=="link" || command[1]=="connection" || command[1]=="edge"){
    //example: add connection of 2 from pointA to pointB


    //validate the number of arguments
    if(command.size()<8){
      std::cout << ERROR << "Not enough arguments.\n" << NORMAL;
      return;
    }else if(command.size()>8){
      std::cout << ERROR << "Too many arguments.\n" << NORMAL;
      return;
    }
    
    //from which node to connect
    Text* from=nullptr;
    //to which node to connect
    Text* to=nullptr;
    //what is the weight of the link
    int value=0;

    try{
      value=std::stoi(command[3].val());
    }catch(const std::invalid_argument& ia){
      std::cout << ERROR << command[3] << " is not a valid integer?\n" << NORMAL;
      return;
    }
    
    //get the parameters
    for(char i=0; i<3; i++){

      //get the weight
      if(command[2+i*2]=="of"){
        try{
          value=std::stoi(command[3+i*2].val());
        }catch(const std::invalid_argument& ia){
          std::cout << ERROR << command[3+i*2] << " is not a valid integer.\n" << NORMAL;
          return;
        }
      }
      
      //get the nodes
      Text* current=getNodeWithName(command[3+i*2]);

      if(current==nullptr){
        std::cout << ERROR << "\"" << command[3+i*2] << "\" doesn't exist.\n" << NORMAL;
        return;
      }

      
      if(command[2+i*2]=="from"){
        from=current;      
      }else if(command[2+i*2]=="to"){
        to=current;
      }else{
        std::cout << ERROR << "\"" << command[2+i*2] << "\" is not a keyword.\n" << NORMAL;
        return;
      }
    }

    if(from==nullptr){
      std::cout << ERROR << "Connect from where?\n" << NORMAL;
      return;
    }else if(to==nullptr){
      std::cout << ERROR << "Connect to where?\n" << NORMAL;
      return;
    }else if(value==0){
      std::cout << ERROR << "Connect with what value?\n" << NORMAL;
      return;
    }

    //create the link
    addLink(from, to, value);
    
  //add 2 links between 2 nodes
  }else if(command[1]=="links" || command[1]=="connections" || command[1]=="edges"){
    //example: make links of 5 between pointA and pointB

    //validate the number of arguments
    if(command.size()<8){
      std::cout << ERROR << "Not enough arguments.\n" << NORMAL;
      return;
    }else if(command.size()>8){
      std::cout << ERROR << "Too many arguments.\n" << NORMAL;
      return;
    }


    //nodes to connect
    Text* node1=nullptr;
    Text* node2=nullptr;
    //what is the weight of the links
    int value=0;

    {
      int i=2;
      for(int q=0; q<2; q++){

        //get the nodes
        if(command[i]=="between"){
          
          node1=getNodeWithName(command[i+1]);
          if(node1==nullptr){
            std::cout << ERROR << "\"" << command[i+1] << "\" doesn't exist.\n" << NORMAL;
            return;
          }
          if(command[i+2]!="and"){
            std::cout << ERROR << "Missing keyword \"and\"\n" << NORMAL;
            return;
          }
          node2=getNodeWithName(command[i+3]);
          if(node1==nullptr){
            std::cout << ERROR << "\"" << command[i+3] << "\" doesn't exist.\n" << NORMAL;
            return;
          }
          i+=4;
          
        //get the value
        }else if(command[i]=="of"){
          try{
            value=std::stoi(command[i+1].val());
          }catch(const std::invalid_argument& ia){
            std::cout << ERROR << command[i+1] << " is not a valid integer.\n" << NORMAL;
            return;
          }
          i+=2;
          
        }else{
          std::cout << ERROR << "\"" << command[i] << "\" is not a keyword.\n" << NORMAL;
        
        }
      }


      if(node1==nullptr || node2==nullptr){
        std::cout << ERROR << "Connect from where?\n" << NORMAL;
        std::cout << ERROR << "Connect to where?\n" << NORMAL;
        return;
      }else if(value==0){
        std::cout << ERROR << "Connect with what value?\n" << NORMAL;
        return;
      }
      
    }
  }
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
