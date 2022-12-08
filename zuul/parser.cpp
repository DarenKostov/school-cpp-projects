#include <iostream>
#include "./parser.h"
#include <cstring>

using namespace std;


Parser::Parser(char AllCommands[20][10][15], char AllCommandsDescription[20][50], char AllCommandArgsDef[20][10][5], char AllCommandsArgs[20][50]){
  for(int i=0; i<commandsAmount; i++){
    strcpy(allCommandsDescription[i], AllCommandsDescription[i]);
    strcpy(allCommandsArgs[i], AllCommandsArgs[i]);
    for(int j=0; j<10; j++){
      strcpy(allCommands[i][j], AllCommands[i][j]);   
      strcpy(allCommandArgsDef[i][j], AllCommandArgsDef[i][j]);
    
    }
  }
  
   
  
  

}

void Parser::readLn(){
  cin.getline(input, 99);
  
  
  int j=0;
  int word=0;
  for(int i=0; i<99; i++){
    if(input[i]==' '){
      command[word][i-j]='\0';
      j=++i;
      word++;
      //continue;
    }  
  
    command[word][i-j]=input[i];
    
    if(input[i]=='\0'){
      //cout <<i<<endl;
      break;     
    }
  }
  
  
  //set all empty words into missing
  for(int i=word+1; i<20; i++)
    strcpy(command[i],"=MISSING=\0");
  
  //fix the command
  fixCommand() && fixArgs();
}

char* Parser::returnCommand(int i){

  return command[i];
}

bool Parser::fixCommand(){
  
  bool skipErasing=false;
  for(int j=0; j<10; j++){//proper command loop
    for(int k=0; k<10; k++){//aliases loop
  
      if(0==strcmp(command[0], allCommands[j][k])){
        cout << "$ " << allCommands[j][k] << endl;
        strcpy(command[0], allCommands[j][0]);
        commandIndex=j;
        skipErasing=true;
        break;
      }
      if(skipErasing)
        break;
    }
  }
  if(!skipErasing){
    strcpy(command[0], "=MISSING=\0");
    return false;
  }
  return true;
}

bool Parser::fixArgs(){
 
  for(int i=0; i<10; i++){//loop through all of the args definitions (if its int, bool, str, ect)
      
      // cout << allCommandArgsDef[commandIndex][i] << endl;  
      
      if(strcmp(allCommandArgsDef[commandIndex][i], "cmd")==0){
        //do nothing, its the command
      }else
        if(strcmp(allCommandArgsDef[commandIndex][i], "str")==0){
          //do nothing
        }else 
          if(strcmp(allCommandArgsDef[commandIndex][i], "int")==0){
            //convert command[i] into int
          }else
            if(strcmp(allCommandArgsDef[commandIndex][i], "bool")==0){
              //convert command[i] into bool
            }else{
              // cout << "missing\n";
              strcpy(command[i], "=MISSING=\0");
            } 

  }
  
  
  cout << "fixed args" << endl;
  return true;
}

