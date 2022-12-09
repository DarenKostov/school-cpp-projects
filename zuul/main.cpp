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


// #include "./parser.h"

#ifndef qwe
#define qwe
#include "./command.h"
#endif

using namespace std;

// void addedCommandInfo(Command command);
void addAllCommands(vector<Command*> &commandBank);


void addedCommandInfo(Command command);



int main(){
   vector<Command*> commandBank;
   addAllCommands(commandBank);
   
   
   
}

// template <class arr1, class arr2, class par1, class par2, class par3, class par4, class par5, class par6>
// void addCommand(vector<Command<arr1, arr2>*> commandBank, );

// template <class arr1, class arr2, class par1, class par2, class par3>
// void addCommand(vector<Command<arr1, arr2>*> commandBank, );

// int main (){
   
//    char ALLCOMMANDS[20][10][15]={
//       {"help", "h"},
//       {"features", "feature", "f"},
//       {"tips", "ti"},
//       {"go", "goto", "g"},
//       {"take", "t",},
//       {"use", "u", "utilize"},
//       {"drop", "d", "letgoof"},
//       {"inventory", "i", "inv"},
//       {"quit", "q", "exit", "e", "leave", ":q"},
//       {"look", "l", "lookaround", "la", "list", "ls", "description", "desc"},
//    };
   
//    char ALLCOMMANDSDESCRIPTION[20][50]={
//       "this help",
//       "gives a list of all the features",
//       "gives you tips"
//       "go in a direction"
//    };
   
//    //cmd is the command, first argument
//    //cmd, str, int, bool 
//    char ALLCOMMANDSARGSDEF[20][10][5]={
//       {"cmd"},
//       {"cmd"},
//       {"cmd"},
//       {"cmd", "str"},        //go
//       {"cmd", "str", "int"}, //take
//       {"cmd", "str"},        //use
//       {"cmd", "str", "int"}, //drop
//       {"cmd"},
//       {"cmd"},
//       {"cmd"},
//    };
   
//    char ALLCOMMANDSARGS[20][50]={
//       "none",
//       "none",
//       "none",
//       "direction"
//    };
   
   
   // Parser parser= Parser(ALLCOMMANDS, ALLCOMMANDSDESCRIPTION, ALLCOMMANDSARGSDEF, ALLCOMMANDSARGS);
   
   // cout << "reading line:" << endl;
   // parser.readLn();
   
   // cout << "printing line" << endl;

   // for (int i=0; i<10; i++)
   //    cout << parser.returnCommand(i) << endl;
   
   // cout << "done printing" << endl;
   
   
//    vector<Command*> commandBank;
   
//    char alias[100][100]={"help", "h"};
//    char description[100]="Prints this help.";
//    char args[100][100]={"cmd"};
//    char argsDescription[100]="none";
//    Command help(2, alias, description, 1, args, argsDescription);   
//    addedCommandInfo(help);
   
   
// return 0;

// }
   
   
// template <class arr1, class arr2, class par1, class par2, class par3, class par4, class par5, class par6>
// void addCommand(vector<Command*> &commandBank, par1 AliasesAmount, par2 Aliases, par3 Description, par4 ArgsAmount, par5 Args, par6 ArgsDescription){
   
   
// }



   
void addedCommandInfo(Command command){
  cout << "=created "<< command.aliases[0] << "\n=command description:\n";
  cout << command.description << "\n=includes these aliases:\n";
  for(int i=0; i<command.aliasesAmount; i++)
     cout << command.aliases[i] << ", ";
  cout << "\n=these arguments:\n" << command.argsDescription << endl;
  cout <<  "=argument types:\n";
  for(int i=0; i<command.argsAmount; i++)
     cout << command.args[i] << ", ";
  cout << endl;
}   


//all commands to be added
void addAllCommands(vector<Command*> &commandBank){
   //big brain {} block to encapsulate variables
   {
   char alias[100][100]={"help", "h"};
   char description[100]="Prints this help.";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back(new Command(2, alias, description, 1, args, argsDescription));
   //pointer arithmetic
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"cd", "chgdir", "cngdir", "chngdir"};
   char description[100]="Changes the current directory.";
   char args[100][100]={"cmd", "str"};
   char argsDescription[100]="<directory path>";
   commandBank.push_back(new Command(4, alias, description, 2, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"copy", "c"};
   char description[100]="Copies a file into the ram.";
   char args[100][100]={"cmd", "str"};
   char argsDescription[100]="<source path>";
   commandBank.push_back(new Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"paste", "p"};
   char description[100]="pastes all files from ram.";
   char args[100][100]={"cmd", "str"};
   char argsDescription[100]="<destination path>";
   commandBank.push_back(new Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"cp", "copypaste"};
   char description[100]="copies a file into memory and pastes it.";
   char args[100][100]={"cmd", "str", "str"};
   char argsDescription[100]="<source path> <destination path>";
   commandBank.push_back(new Command(2, alias, description, 3, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"rm", "remove"};
   char description[100]="Deletes a file.";
   char args[100][100]={"cmd", "str"};
   char argsDescription[100]="<file path>";
   commandBank.push_back(new Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"man", "manual"};
   char description[100]="Shows detals on how to use a program.";
   char args[100][100]={"cmd", "str"};
   char argsDescription[100]="<program>";
   commandBank.push_back(new Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"free", "fr"};
   char description[100]="Shows the ram usage.";
   char args[100][100]={"cmd", "str"};
   char argsDescription[100]="<flag>";
   commandBank.push_back(new Command(2, alias, description, 2, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"mv", "move"};
   char description[100]="Moves a file.";
   char args[100][100]={"cmd", "str", "str"};
   char argsDescription[100]="<source path> <destination path>";
   commandBank.push_back(new Command(2, alias, description, 3, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   //Table Of Processes, i know it doesn't stand for that, but makes more sense as an alieas than "top CPU consumers"
   char alias[100][100]={"top", "tlboprc", "tbloprs"};
   char description[100]="Shows process's name, memory usage, and cpu usage";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back(new Command(3, alias, description, 1, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   cout << "============\n";
   {
   char alias[100][100]={"cb", "copybuffer", "copybank"};
   char description[100]="Shows you what files you have in the copy buffer.";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back(new Command(3, alias, description, 1, args, argsDescription));
   addedCommandInfo(**(commandBank.end()-1));
   }
   
   
   
}