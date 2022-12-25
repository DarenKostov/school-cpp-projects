#include <iostream>
#include <vector>


#ifndef q
#define q
#include "./text.h"
#include "./command.h"
#include "./parser.h"
#endif

using namespace std;

//constructor
Parser::Parser(){
  commandText=new Text[0];
  
  char alias[100][100]={""};
  char description[100]="";
  char args[100][100]={""};
  char argsDescription[100]="";
  emptyCommand=Command(1, alias, description, 1, args, argsDescription);
  
  command=malloc(100);
  
}

Parser::~Parser(){
  delete[] commandText;
  free(command);
}

//add from a Command pointer
void Parser::addCommand(Command* input){
  allCommands.push_back(Command(*input));
}
//add from a Command pointer vector
void Parser::addCommands(vector<Command*> input){
  for(vector<Command*>::iterator i=input.begin(); i!=input.end(); i++){
    addCommand(*i);
    // allCommands.push_back(**i);       
  }
}

//add from a Command
void Parser::addCommand(Command input){
  allCommands.push_back(Command(input));
}
//add from a Command vector
void Parser::addCommands(vector<Command> input){
  for(vector<Command>::iterator i=input.begin(); i!=input.end(); i++){
    addCommand(*i);
    // allCommands.push_back(**i);       
  }
}
 
bool Parser::removeCommand(Text in){
  
  for(auto i=allCommands.begin(); i!=allCommands.end(); i++){
    if(i->aliases[0]==in)
      allCommands.erase(i);
    return true; 
  }
    return false; 
}

 
Command Parser::commandDefAt(int i){
  //add i to the pointer (go to index i) and derefrence it
  return *(allCommands.begin()+i);
}
   
vector<Command> Parser::getAllCommands(){
  return allCommands;
}
  
  


void Parser::readLn(){
  char input[99];
  
  char output[99][99];
  
  cin.getline(input, 99);
  
  
  int j=0;
  int word=0;
  
  //loop through until you meet a /0
  for(int i=0; i<99; i++){
    //once a you see a ' ' go to the next word
    if(input[i]==' '){
      output[word][i-j]='\0';
      j=++i;
      word++;
      //continue;
    }  
  
    output[word][i-j]=input[i];
    
    if(input[i]=='\0'){
      // word++;
      break;     
    }
  }
  
  
  commandLength=word+1;
  
  
  //make a Text of all the commands separated by " "
  Text outputText[commandLength];
   for(int i=0; i<commandLength; i++){
    outputText[i]=output[i];
  }
  
  
  //free the memory in the command
  delete[] commandText;
  
  
  //word is your amount of arguments
  
  
  if(setCurrentCommand(Text(output[0]))){
    //fix the command length
    commandLength=min(commandLength, currentCommandDef->argsAmount);
    
    
    commandText=new Text[commandLength];
    fixArgs(outputText, commandLength);
  }else{//if it could find an alias the command inputed was invalid
    //the current command is nothing, empty
    currentCommandDef=&emptyCommand;
    commandText=new Text[1];
    commandText[0]=currentCommandDef->aliases[0];
    
  }
  
}


Text Parser::returnCommandT(int i){
  if(i>=commandLength)
    return Text('\0');
  return commandText[i];
}



bool Parser::setCurrentCommand(Text input){
  
  int count=0;
  bool skipErasing=false;
  for(vector<Command>::iterator i=allCommands.begin(); i!=allCommands.end(); i++){//all commands loop
    count++;
    for(int j=0; j<(*i).aliasesAmount; j++){//aliases loop
      
      //if our cmd is any valid alias
      if((*i).aliases[j]==input){
        //set the curComDef to the adress of the command
        currentCommandDef=&(*i);        
        return true;
      }
    }
  }

  return false;
}


//fix with "what"
void Parser::fixArgs(Text* what, int amount){
  
  for(int i=0, j=0; i<amount; i++, j++){//loop through all of the args definitions (if its int, bool, str, ect)

      if(currentCommandDef->args[i]=="cmd"){
        commandText[i]=currentCommandDef->aliases[0];
      }else if(currentCommandDef->args[i]=="str"){
        //do nothing, we arent using strings
      }else if(currentCommandDef->args[i]=="txt"){
        //do nothing it's already a Text
        commandText[i]=what[j];
      }else if(currentCommandDef->args[i]=="int"){
        //convert to int
        commandText[i]=what[j];
      }else if(currentCommandDef->args[i]=="bool"){
        //convert to bool
        commandText[i]=what[j];
      }else if(currentCommandDef->args[i]=="''"){
        //take in whatever is in the quotes
      
        //make sure we start with empty Text
        commandText[i]="";
      
        //if we start with quotes
        if(what[j][0]=='\''){
          
            //we end with quites as well?
            if(what[j][what[j].len()-1]=='\''){ 
              //yes?
              //remove first and last charcter and onto the next argument
              for(int k=1; k<what[j].len()-1; k++)
                commandText[i]+=what[j];
              continue;
            }
        
        
          //no?
          //loop until we find the ending quotes
          while(true){
          
            //next word
            j++;  
          
            //we end with quites?
            if(what[j][what[j].len()-1]=='\''){ 
              //yes?
              //add the word (withut the ending ') to our argument and onto the next argument 
              for(int k=1; k<what[j].len()-1; k++)
                commandText[i]+=what[j];
              break;
            }

            //no? add the entire word to the argument and onto the next word
            for(int k=1; k<what[j].len()-1; k++)
              commandText[i]+=what[j];
          }
        
        
        }
    
      }else
        commandText[i]=""; 

    
    
  }
  
}

