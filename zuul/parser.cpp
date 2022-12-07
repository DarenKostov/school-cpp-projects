#include <iostream>
#include "./parser.h"
#include <cstring>

using namespace std;


Parser::Parser(char AllCommands[20][10][15], char AllCommandsDescription[20][50], char allCommandArgsDef[20][10][5], char AllCommandsArgs[20][50]){
  for(int i=0; i<commandsAmount; i++){
    strcpy(allCommandsDescription[i], AllCommandsDescription[i]);
    strcpy(allCommandsArgs[i], AllCommandsArgs[i]);
    for(int j=0; j<10; j++){
      strcpy(allCommands[i][j], AllCommands[i][j]);   
    
    
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
  
  
  
  for(int i=word+1; i<10; i++)
    strcpy(command[i],"=MISSING=\0");
  
  fixCommand() && fixArgs();
}

void* Parser::returnCommand(int i){
  return command[i];
}

bool Parser::fixCommand(){
  
  bool skipErasing=false;
  for(int j=0; j<10; j++){//proper command loop
    for(int k=0; k<10; k++){//aliases loop
  
      if(0==strcmp((char*)returnCommand(0), allCommands[j][k])){
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
 
  for(int i=1; i<10; i++){//loop through all the inputed args
    for(int j=0; j<10; j++){//loop through all the valid args
      
        if(allCommandArgsDef[commandIndex][]){
                
      
        }
      }
  }
  
  
  return true;
}

