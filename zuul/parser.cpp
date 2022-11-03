#include <iostream>
#include "./parser.h"
#include <cstring>

using namespace std;


Parser::Parser(char AllCommands[10][10][10], char AllCommandsDescription[10][50], char AllCommandsArgs[10][20]){
  for(int i=0; i<10; i++){
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
    strcpy(command[i],"000000000\0");
  
  fixCommand();
  
}

char* Parser::returnCommand(int i){
  return command[i];
}

void Parser::fixCommand(){
  
  for(int i=0; i<10; i++){//command args loop
    bool skipErasing=false;
    for(int j=0; j<10; j++){//proper command loop
      for(int k=0; k<10; k++){//aliases loop
    
        if(0==strcmp(returnCommand(i), allCommands[j][k])){
          cout << "$ " << allCommands[j][k] << endl;
          strcpy(command[i], allCommands[j][0]);
          skipErasing=true;
          break;
        }
        if(skipErasing)
          break;
      }
    }
    if(!skipErasing)
      strcpy(command[i], "000000000\0");
  }    
}


