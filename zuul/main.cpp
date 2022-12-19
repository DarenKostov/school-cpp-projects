/*

   Daren Kostov
   Zuul
   11/01/2022

resources used:
https://www.geeksforgeeks.org/getline-string-c/
https://stackoverflow.com/questions/213761/what-are-some-uses-of-template-template-parameters
https://stackoverflow.com/questions/29360555/c-passing-an-array-directly-into-a-function-without-initializing-it-first
https://stackoverflow.com/questions/4000358/is-possible-to-get-automatic-cast-from-user-defined-type-to-stdstring-using-co
https://en.cppreference.com/w/cpp/chrono/c/time

https://superuser.com/questions/186520/colors-in-cygwin-being-displayed-as-raw-ansi-codes

*/
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>

// #include "./parser.h"

#ifndef q
#define q
#include "./text.h"
#include "./command.h"
#include "./parser.h"

//slot in inventory
#include "./path.h"
//item
#include "./file.h"
//inventory
#include "./memory.h"
//room
#include "./folder.h"
//building
#include "./computer.h"

//location 2
// #include "./ipadress.h"

//street adress of a building
// #include "./localipadress.h"

//longitude and latidude of a city?? TBD
// #include "./globalipadress.h"

//city? TBD
// #include "./network.h"

// std::ostream &operator <<(std::ostream&, Text&);

   
#endif


//==consts

//text colors characters/commands use
//all characters talking are bold and bright
//all characters thinking are bright
//all command output/misc is normal color

//=me!

//cyan fg, black bg, bold
const Text Daren_talking="\033[36;40;1m";
//bright cyan fg, black bg
const Text Daren_thinking="\033[96;40m";

//=you, the player

//green fg, black bg, bold
const Text Player_talking="\033[32;40;1m";
//bright green fg, black bg
const Text Player_thinking="\033[92;40m";

//=your boss in the game plot

//green fg, black bg, bold
const Text Boss_talking="\033[33;40;1m";
//bright green fg, black bg
const Text Boss_thinking="\033[93;40m";

//=some admin in the system you are infiltrating

//green fg, black bg, bold
const Text Admin_talking="\033[31;40;1m";
//bright green fg, black bg
const Text Admin_thinking="\033[91;40m";

//=messages

//white (not default) fg, black bg
const Text Info="\033[97;40m";

//yellow fg, black bg
const Text Warning="\033[33;40m";

//red fg, black bg
const Text Error="\033[31;40m";

//magenta fg, black bg
const Text UnexpectedIO="\033[35;40m";



using namespace std;


void addAllCommands(vector<Command> &commandBank);
void addedCommandInfo(Command command);

// const long printSpeed=10000;
const long printSpeed=10000;

//SLEeP, shorter than usleep, uses less 0's
void slep(){ usleep(printSpeed);};
void slep(int x){ usleep(x*printSpeed);};

//Unconfortable SLEeP, like when sleeping on an airplane, you wake up, you sleep again, etc at random
void uSlep(){ usleep(rand()%(printSpeed/2)+printSpeed/2);};

//types chars one by one
void slowtalk(bool on, Text in, Text format);
void slowtalk(bool on, Text in, Text format, int speed);
void fasttalk(bool on, Text in, Text format);



//=function names might and most likely will be confused with their respective colors

//prints an info
void info(bool on, Text in);
//prints a warning
void warning(bool on, Text in);
//prints an error
void error(bool on, Text in);
//prints an unexpected input/output, cant name function "unexpected"
void unexpectedIO(bool on, Text in);




template <class T>
void emptyVector(vector<T*>&); //empties a vector of object pointers
template <class T>
void emptyVector(vector<T>&); //empties a vector of objects






int main(){
   
   bool isColorOn=true;
   
   
   slowtalk(isColorOn, "Welcome to Zuul", Daren_talking);
   fasttalk(isColorOn, "\n\n  This project is not ready", Daren_thinking);
   // slowtalk(isColorOn, ".....", Daren_thinking, 50);
   fasttalk(isColorOn, "\n\n  Should be ready soon thought.\n\n", Daren_thinking);
   
   
   
   
   
   Parser parser;
   
   //a {} block since we wanna remove commandBank after its used
   {
      vector<Command> commandBank;
      addAllCommands(commandBank);
      parser.addCommands(commandBank);
   }
      
   
   parser.readLn();
   
   
   
   cout << (char*)parser.returnCommandT(0)<<endl;
   cout << parser.returnCommandT(1).val()<<endl;
   cout << parser.returnCommandT(2)<<endl;
   
   
   
   
   File fileA= File(Path(Text("/path/of/file/A")), Text("contents of file A"));
   File fileB= File(Path(Text("/path/of/file/B")), Text("contents of file B"));
   
   Folder folderA= Folder(Path(Text("/path/of/folder/A")));
   
   Folder folderB= Folder(Path(Text("/path/of/folder/B")));
   
   folderA.addFile(fileA);
   folderB.addFile(fileB);
   
   folderB.addFolder(folderA);
   
   
   
   
   cout << "==folder B:\n";
   cout << "=path:\n";
   cout << folderB.path.wholeT()+'\n';
   cout << "=contents:\n";
   cout << folderB.allItems();
   
   cout << "\n";
   
   cout << "==folder A:\n";
   cout << "=path:\n";
   cout << folderA.path.wholeT()+'\n';
   cout << "=contents:\n";
   cout << folderA.allItems();
   
   
   
   
   // cout << folderA.allItems() << endl;
   
   
   Memory mem1=Memory(100);   
   
   mem1.addFile(fileA);
   mem1.addFile(fileB);
   
   
   return 0;
}
void slowtalk(bool on, Text in, Text format, int speed){
   //are we coloring this?
   if(on)
      cout << format << flush;
   //print everything
   for(int i=0; i<in.len(); i++){
      cout << in[i] << flush;
      slep(speed);
    }
   //reset the color
   if(on)
      cout << "\033[0m";
}


void slowtalk(bool on, Text in, Text format){
   slowtalk(on, in, format, 5);   
}

void fasttalk(bool on, Text in, Text format){
   //are we coloring this?
   if(on)
      cout << format << flush;
   //print everything
   for(int i=0; i<in.len(); i++){
      cout << in[i] << flush;
      slep(1);
    }
   //reset the color
   if(on)
      cout << "\033[0m";
}



void info(bool on, Text in){
   fasttalk(on, "[Info] "+in+'\n', Info);
}
void warning(bool on, Text in){
   fasttalk(on, "[Warning] "+in+'\n', Warning);
}
void error(bool on, Text in){
   fasttalk(on, "[Error] "+in+'\n', Error);
}
void unexpectedIO(bool on, Text in){
   fasttalk(on, "[Unexpected] "+in+'\n', UnexpectedIO);
}


//vector object pointers
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
   }
   {
   char alias[100][100]={"cd", "chgdir", "cngdir", "chngdir"};
   char description[100]="Changes the current directory.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<directory path>";
   commandBank.push_back( Command(4, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"copy", "c"};
   char description[100]="Copies a file into the ram.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<source path>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"paste", "p"};
   char description[100]="pastes all files from ram. OR pastes a specifc file";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<destination path> [file id]";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"cp", "copypaste"};
   char description[100]="copies a file into memory and pastes it.";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<source path> <destination path>";
   commandBank.push_back( Command(2, alias, description, 3, args, argsDescription));
   }
   {
   char alias[100][100]={"rm", "remove"};
   char description[100]="Deletes a file.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<file path>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"man", "manual"};
   char description[100]="Shows detals on how to use a program.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<program>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"free", "fr"};
   char description[100]="Shows the ram usage.";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<flag>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"mv", "move"};
   char description[100]="Moves a file.";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<source path> <destination path>";
   commandBank.push_back( Command(2, alias, description, 3, args, argsDescription));
   }
   {
   //Table Of Processes, i know it doesn't stand for that, but makes more sense as an alieas than "top CPU consumers"
   char alias[100][100]={"top", "tbloprc", "tbloprs"};
   char description[100]="Shows process's name, memory usage, and cpu usage";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(3, alias, description, 1, args, argsDescription));
   }
   {
   //doesnt copy to the buffer, its the buffer thats copied into
   char alias[100][100]={"cb", "copybuffer", "copybank"};
   char description[100]="Shows you what files you have in the copy buffer.";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(3, alias, description, 1, args, argsDescription));
   }
   
   {
   char alias[100][100]={"ssh", "secureshell"};
   char description[100]="Secure Shell";
   char args[100][100]={"cmd", "txt"};
   char argsDescription[100]="<who>@<adress>\n<adress>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"scp", "securecopy"};
   char description[100]="Secure, Contain, Protect!\n\nAhem, SSH secure file copy";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<who>@<adress>:<source path> <who>@<adress>:<destination path>";
   commandBank.push_back( Command(2, alias, description, 3, args, argsDescription));
   }
   {
   char alias[100][100]={"cat", "catout"};
   char description[100]="Concatenate files and print on the standard output. tl;dr Print files into terminal.";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<file path>";
   commandBank.push_back( Command(2, alias, description, 2, args, argsDescription));
   }
   {
   char alias[100][100]={"grep"};
   char description[100]="Print lines from a file that match a pattern.";
   char args[100][100]={"cmd", "txt", "txt"};
   char argsDescription[100]="<pattern> <file path>";
   commandBank.push_back( Command(2, alias, description, 3, args, argsDescription));
   }
   {
   char alias[100][100]={"tree"};
   char description[100]="Print a tree of all child folders/files";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(1, alias, description, 1, args, argsDescription));
   }
   
}