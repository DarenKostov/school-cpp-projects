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
  
  //make a Text of all the commands separated by " "
  Text outputText[word+1];
   for(int i=0; i<word+1; i++){
    outputText[i]=output[i];
  }
  
  
  //free the memory in the command
  delete[] commandText;
  
  if(setCurrentCommand(Text(output[0]))){
    commandText=new Text[currentCommandDef->argsAmount];
    fixArgs(outputText);
  }else{//if it could find an alias the command inputed was invalid
    //the current command is nothing, empty
    currentCommandDef=&emptyCommand;
    commandText=new Text[1];
    commandText[0]=currentCommandDef->aliases[0];
    
  }
  
}


Text Parser::returnCommandT(int i){
  char empty[1]="";
  if(i>=currentCommandDef->argsAmount)
    return Text(empty);
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
        goto commandsLoopEnd;
      }
    }
  }
  commandsLoopEnd:

  return false;
}

//fix with "what"
void Parser::fixArgs(Text* what){
  
  for(int i=0; i<currentCommandDef->argsAmount; i++){//loop through all of the args definitions (if its int, bool, str, ect)
      
      // cout << allCommandArgsDef[commandIndex][i] << endl;  
      char cmd[5]="cmd";
      char str[5]="str";
      char txt[5]="txt";
      char iNt[5]="int";
      char bOol[5]="bool";
      char empty[1]="";

      if(currentCommandDef->args[i]==cmd){
        commandText[i]=currentCommandDef->aliases[0];
      }else if(currentCommandDef->args[i]==str){
        //do nothing, we arent using strings
      }else if(currentCommandDef->args[i]==txt){
        //do nothing it's already a Text
        commandText[i]=what[i];
      }else if(currentCommandDef->args[i]==cmd){
        //convert to int
        commandText[i]=what[i];
      }else if(currentCommandDef->args[i]==cmd){
        //convert to bool
        commandText[i]=what[i];
      }else
        commandText[i]=empty; 

  }
  
}

