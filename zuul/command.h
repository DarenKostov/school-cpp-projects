/*
  Daren Kostov
  this struct is a command, which includes its aliaces and arguments
  
  resources used:
  https://stackoverflow.com/questions/16724368/how-to-pass-a-2d-array-by-pointer-in-c
  https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
  //a template for any data type, who knew such a powerful feature existed
  https://www.geeksforgeeks.org/templates-cpp/
*/
#include <cstring>

#ifndef q
#define q
#include "./text.h"
#endif

struct Command{

  Text* aliases;  //valid variations of the command, the 0th index is the main command
  Text description; //what the command is actualy about, does it pick up apples? pears?
  Text* args; //which arg is int, bool, float, etc, the 0th index is the command itself
  Text argsDescription; //what are actually the arguments, amount of apples? pears?
  int aliasesAmount; //amount of aliases, self explanatory
  int argsAmount; //amount of arguments, self explanatory
  
  template <class arr1, class arr2>
  Command(int AliasesAmount, arr1 Aliases, char* Description, int ArgsAmount, arr2 Args, char* ArgsDescription){
   
    //command aliases copy over
    aliases= new Text[AliasesAmount];
    for(int i=0; i<AliasesAmount; i++){
      //copy the input into the internal variable
      aliases[i]=Aliases[i];
    }  

    //command argument definitions copy over
    args= new Text[ArgsAmount];
    for(int i=0; i<ArgsAmount; i++){
      //copy the input into the internal variable
      args[i]=Args[i];
    }  
    
    //copy over descriptions
    description=Description;
    argsDescription=ArgsDescription;
    
    //copy over amounts
    aliasesAmount=AliasesAmount;  
    argsAmount=ArgsAmount;  
    
  }
  
};
