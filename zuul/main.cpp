/*

   Daren Kostov
   Zuul
   11/01/2022

resources used:
https://www.geeksforgeeks.org/getline-string-c/
https://stackoverflow.com/questions/213761/what-are-some-uses-of-template-template-parameters
https://stackoverflow.com/questions/29360555/c-passing-an-array-directly-into-a-function-without-initializing-it-first

*/
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>


// #include "./parser.h"

#ifndef q
#define q
#include "./text.h"
#include "./command.h"
#include "./parser.h"
#endif

using namespace std;

// void addedCommandInfo(Command command);
void addAllCommands(vector<Command> &commandBank);


void addedCommandInfo(Command command);

//usleep but less 0's needed
void slep(){ usleep(100000);};
void slep(int x){ usleep(x*100000);};


template <class T>
void emptyVector(vector<T*>&); //empties a vector of object pointers
template <class T>
void emptyVector(vector<T>&); //empties a vector of objects




int main(){
   Parser parser;
   
   {
      //no real reason for this to be a vector of pointers
      vector<Command> commandBank;
      addAllCommands(commandBank);
      parser.addCommands(commandBank);
      //no longer are definitions of the commands needed, lets free up the memory used by them   
      emptyVector(commandBank);
   }
      
   addedCommandInfo(parser.commandDefAt(1));
   parser.readLn();
   
   cout << parser.returnCommandT(0).val()<<endl;
   cout << parser.returnCommandT(1).val()<<endl;
   cout << parser.returnCommandT(2).val()<<endl;
   
   
}

//vecor object pointers
template <class T>
void  emptyVector(vector<T*> &toBeEmptied){
   //free up the memory used by the objects in the vector
   for(typename vector<T*>::iterator i=toBeEmptied.begin(); i!=toBeEmptied.end(); i++){
      delete (*i);
   }
   //delete all of the pointers in the vector
   while(toBeEmptied.size()!=0){
      toBeEmptied.erase(toBeEmptied.begin());  
   } 
}
//vector of objects
template <class T>
void  emptyVector(vector<T> &toBeEmptied){
   //delete all of the pointers in the vector
   while(toBeEmptied.size()!=0){
      toBeEmptied.erase(toBeEmptied.begin());  
   } 
}


void addedCommandInfo(Command command){
  cout << "=command name: "<< command.aliases[0].val() << "\n=command description:\n";
  cout << command.description.val() << "\n=includes these aliases:\n";
  for(int i=0; i<command.aliasesAmount; i++)
     cout << command.aliases[i].val() << ", ";
  cout << "\n=these arguments:\n" << command.argsDescription.val() << endl;
  cout <<  "=argument types:\n";
  for(int i=0; i<command.argsAmount; i++)
     cout << command.args[i].val() << ", ";
  cout << endl;
}   


//all commands to be added
void addAllCommands(vector<Command> &commandBank){
   //big brain {} block to encapsulate variables
   {
   char alias[100][100]={"help", "h"};
   char description[100]="Prints this help.";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(2, alias, description, 1, args, argsDescription));
   //pointer aritmetic
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"cd", "chgdir", "cngdir", "chngdir"};
   char description[100]="Changes the current directory.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<directory path>";
   commandBank.push_back( Command(4, alias, description, 2, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"copy", "c"};
   char description[100]="Copies a file into the ram.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<source path>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"paste", "p"};
   char description[100]="pastes all files from ram. OR pastes a specifc file";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<destination path> [file id]";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"cp", "copypaste"};
   char description[100]="copies a file into memory and pastes it.";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<source path> <destination path>";
   commandBank.push_back( Command(2, alias, description, 3, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"rm", "remove"};
   char description[100]="Deletes a file.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<file path>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"man", "manual"};
   char description[100]="Shows detals on how to use a program.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<program>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"free", "fr"};
   char description[100]="Shows the ram usage.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<flag>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"mv", "move"};
   char description[100]="Moves a file.";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<source path> <destination path>";
   commandBank.push_back( Command(2, alias, description, 3, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   //Table Of Processes, i know it doesn't stand for that, but makes more sense as an alieas than "top CPU consumers"
   char alias[100][100]={"top", "tbloprc", "tbloprs"};
   char description[100]="Shows process's name, memory usage, and cpu usage";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(3, alias, description, 1, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"cb", "copybuffer", "copybank"};
   char description[100]="Shows you what files you have in the copy buffer.";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(3, alias, description, 1, args, argsDescription));
   addedCommandInfo(*(commandBank.end()-1));
   }
   
   
   
}