/*
  Daren Kostov


*/

#include "scmdprs.h"


std::vector<Text> readLine(){
  
  //dont ignore white spaces
  std::cin >> std::noskipws;

  std::vector<Text> commands;
  int commandIndex=0;

  while(true){

    //new command?
    char element;
    commands.push_back(Text());

    //is there a separator? 
    while(std::cin >> element && element != ' ' && element != '\n'){
      //if not add the char to the current argument
      commands[commandIndex]+=element;
    }

    //end of commands?
    if(element=='\n')
      break;
    
    commandIndex++;
  } 
  
  //ignore whitespaces
  std::cin >> std::skipws;

  return commands;

}
