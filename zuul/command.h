/*
  Daren Kostov
  this struct is a command, which includes its aliaces and arguments
  
  resources used:
  https://stackoverflow.com/questions/16724368/how-to-pass-a-2d-array-by-pointer-in-c
  https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
  https://www.geeksforgeeks.org/templates-cpp/
*/
#include <iostream>
#include <cstring>



using namespace std;

//a template for any data type, who knew such a powerful feature existed
// template <class arr1, class arr2>
struct Command{

  char** aliases;  //valid variations of the command, the 0th index is the main command
  char* description; //what the command is actualy about, does it pick up apples? pears?
  char** args; //which arg is int, bool, float, etc, the 0th index is the command itself
  char* argsDescription; //what are actually the arguments, amount of apples? pears?
  int aliasesAmount; //amount of aliases, self explanatory
  int argsAmount; //amount of arguments, self explanatory
  
template <class arr1, class arr2>
  Command(int AliasesAmount, arr1 Aliases, char* Description, int ArgsAmount, arr2 Args, char* ArgsDescription){
    
    
    
    //command aliases copy over
    aliases= new char*[AliasesAmount];
    for(int i=0; i<AliasesAmount; i++){
      //1 extra char for the \0 char
      aliases[i]= new char[strlen(Aliases[i])+1];
      //copy the input into the internal variable
      strcpy(aliases[i], Aliases[i]);
    }  

    //command argument definitions copy over
    args= new char*[ArgsAmount];
    for(int i=0; i<ArgsAmount; i++){
      //1 extra char for the \0 char
      args[i]= new char[strlen(Args[i])+1];
      //copy the input into the internal variable
      strcpy(args[i], Args[i]);
    }  
    
    //copy over descriptions
    description= new char[strlen(Description)+1];
    argsDescription= new char[strlen(ArgsDescription)+1];
    strcpy(description, Description);
    strcpy(argsDescription, ArgsDescription);
    
    //copy over amounts
    aliasesAmount=AliasesAmount;  
    argsAmount=ArgsAmount;  
    
  }
  
};