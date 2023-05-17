/*
  Daren Kostov

  the MainClass logic



*/


#include "mainClass.h"
#include "scmdprs.h"


Text const ERROR="\e[93m"; 
Text const NORMAL="\e[0m"; 

template<class T>
bool areArgumentsEnought(std::vector<T>, int);

//gives you a number from Text
int getNumber(Text);

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

    if(commands[0]=="add" || commands[0]=="create" || commands[0]=="make" || commands[0]=="a"){      
      addNodeCommand(commands);
    }else if(commands[0]=="remove" || commands[0]=="delete" || commands[0]=="erase" || commands[0]=="r"){
      removeNodeCommand(commands);
    }else if(commands[0]=="connect" || commands[0]=="c"){
      addLinkCommand(commands);    
    }else if(commands[0]=="disconnect" || commands[0]=="d"){
      removeLinkCommand(commands);    
    }else if(commands[0]=="shortestPath" || commands[0]=="s"){
      
    }else if(commands[0]=="probe" || commands[0]=="p"){

    }
    
  }

}

void MainClass::addNodeCommand(std::vector<Text> commands){
  //example: add "this node is cool"

  if(!areArgumentsEnought(commands, 2))
    return;

  if(getNodeWithName(commands[1])!=nullptr){
    std::cout << ERROR << "Node \"" << commands[1] << "\" already exist.\n" << NORMAL;
  }

  addNode(new Text(commands[1]));
  
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


    //create the link
    removeLink(from, to);

}


//abandoned
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
  }else{
    std::cout << ERROR << command[0] << " what?\n" << NORMAL;
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

void MainClass::probe(Text in){

  auto node=getNodeWithName(in);
  
  if(node==nullptr){
    std::cout << ERROR << "\"" << in << "\" doesn't exist.\n" << NORMAL;
    return;
  }

  //print to where this node is connected
  for(auto element : links[node]){
    if(element.second!=0){
      std::cout << in << " --(" << element.second << ")-> " << *element.first << "\n"; 
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
