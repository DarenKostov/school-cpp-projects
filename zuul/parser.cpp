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
}

Parser::~Parser(){
  delete[] commandText;

  // free the memory command stores somehow 
  // delete[] command;
  // delete command;
  // free(command);
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
  
Command Parser::commandDefAt(int i){
  //add i to the pointer (go to index i) and derefrence it
  return *(allCommands.begin()+i);
}
   
  
  


void Parser::readLn(){
  char input[99];
  
  char output[99][99];
  
  
  cin.getline(input, 99);
  int j=0;
  int word=0;
  for(int i=0; i<99; i++){
    if(input[i]==' '){
      output[word][i-j]='\0';
      j=++i;
      word++;
      //continue;
    }  
  
    output[word][i-j]=input[i];
    
    if(input[i]=='\0'){
      //cout <<i<<endl;
      // word++;
      break;     
    }
  }
  
  //free the memory in the command
  delete[] commandText;
  
  //allocate memory for the command
  commandText=new Text[word+1];
  
  //fill the command with the found words
  for(int i=0; i<word+1; i++){
    commandText[i]=output[i];
  }
  
  //fix the command
  fixCommand() && fixArgs();
}


Text Parser::returnCommandT(int i){
  //makes sure we are not going over the limit
  return commandText[i%currentCommandDef->argsAmount];
}



bool Parser::fixCommand(){
  
  int count=0;
  bool skipErasing=false;
  for(vector<Command>::iterator i=allCommands.begin(); i!=allCommands.end(); i++){//all commands loop
    count++;
    for(int j=0; j<(*i).aliasesAmount; j++){//aliases loop
      
      //if our cmd is any valid alias
      if((*i).aliases[j]==commandText[0]){
        // cout << "$ " << (*i).aliases[0].val() << endl;
        commandText[0]=(*i).aliases[0];
        commandIndex=count;
        //set the curComDef to the adress of the command
        currentCommandDef=&(*i);        
        return true;
        goto commandsLoopEnd;
      }
    }
  }
  commandsLoopEnd:

  char empty[1]="";
  commandText[0]=empty;
  return false;
}

bool Parser::fixArgs(){
  
  for(int i=0; i<currentCommandDef->argsAmount; i++){//loop through all of the args definitions (if its int, bool, str, ect)
      
      // cout << allCommandArgsDef[commandIndex][i] << endl;  
      char cmd[5]="cmd";
      char str[5]="str";
      char txt[5]="txt";
      char iNt[5]="int";
      char bOol[5]="bool";
      char empty[1]="";

      if(currentCommandDef->args[i]==cmd){
        //do nothing, its the command
      }else if(currentCommandDef->args[i]==str){
        //do nothing, we arent using strings
      }else if(currentCommandDef->args[i]==txt){
        //do nothing it's already a Text
      }else if(currentCommandDef->args[i]==cmd){
        //convert to int
      }else if(currentCommandDef->args[i]==cmd){
        //convert to bool
      }else
        commandText[i]=empty; 

  }
  
  return true;
}

