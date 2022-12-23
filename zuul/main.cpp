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
#include "./globalVarsNFuns.h"
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
const Text Daren_talking="\033[36;1m";
//bright cyan fg, black bg
const Text Daren_thinking="\033[96m";

//=you, the player

//green fg, black bg, bold
const Text Player_talking="\033[32;1m";
//bright green fg, black bg
const Text Player_thinking="\033[92m";

//=your boss in the game plot

//green fg, black bg, bold
const Text Boss_talking="\033[33;1m";
//bright green fg, black bg
const Text Boss_thinking="\033[93m";

//=some admin in the system you are infiltrating

//green fg, black bg, bold
const Text Admin_talking="\033[31;1m";
//bright green fg, black bg
const Text Admin_thinking="\033[91m";



using namespace std;


void addAllCommands(vector<Command> &commandBank);
void addedCommandInfo(Command command);



//generates random Text with certain size
Text randomText(int);
//like randomText but limited to only numbers
Text randomText(int);


template <class T>
void emptyVector(vector<T*>&); //empties a vector of object pointers
template <class T>
void emptyVector(vector<T>&); //empties a vector of objects


Computer baseComputer();
Computer brokenComputer();
Computer workingComputer();


//commands from user
void execCD(Computer&);
void execLS(Computer&);


int main(){
   
   bool isColorOn=true;
   
   
   slowtalk(isColorOn, "Welcome to Zuul", Daren_talking);
   fasttalk(isColorOn, "\n\n  This project is not ready", Daren_thinking);
   // slowtalk(isColorOn, ".....", Daren_thinking, 50);
   fasttalk(isColorOn, "\n\n  Should be ready soon thought.\n\n", Daren_thinking);
   fasttalk(isColorOn, "\n\n  ...I hope...\n\n", Daren_thinking);
   
   
   
   Computer myComputer=baseComputer();
   myComputer.on=true;
   
   
   myComputer.parser.readLn();
   
   
   
   while(true){
      //current command
      Text curCom=myComputer.parser.returnCommandT(0);
      cout <<curCom+"\n";
      if(curCom=="cd")
         execCD(myComputer);
      if(curCom=="ls")
         execLS(myComputer);
      if(curCom=="exit")
         break;
      
      
      myComputer.parser.readLn();
      
   }
   
   
   cout << "END\n";
   return 0;
}


//==commands from user
void execCD(Computer& inComp){
   if(inComp.goTo(inComp.parser.returnCommandT(1)))
      execLS(inComp);
}
void execLS(Computer& inComp){
   vector<Folder> curFolders=inComp.getCurrentFolder().allFolders();
   fasttalk(inComp.on,Text("Folders:\n"), Info);
   for(auto i=curFolders.begin(); i!=curFolders.end(); i++){
      fasttalk(inComp.on,i->path.wholeT()+"\n", Info);
   }
   vector<File> curFiles=inComp.getCurrentFolder().allFiles();
   fasttalk(inComp.on,Text("Files:\n"), Info);
   for(auto i=curFiles.begin(); i!=curFiles.end(); i++){
      fasttalk(inComp.on,i->path.wholeT()+"\n", Info);
   }
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


Text randomText(int size){
   Text out;
      for(int i=0; i<size; i++)
         out+='!'+(rand()%93);
   return out;
}
Text randomTextNumbers(int size){
   Text out;
      for(int i=0; i<size; i++)
         out+='0'+(rand()%10);
   return out;
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
   {
   char alias[100][100]={"exit", "quit"};
   char description[100]="Exits the game";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(2, alias, description, 1, args, argsDescription));
   }
   {
   char alias[100][100]={"ls", "list"};
   char description[100]="Lists the items in the current directory";
   char args[100][100]={"cmd"};
   char argsDescription[100]="none";
   commandBank.push_back( Command(2, alias, description, 1, args, argsDescription));
   }
}


Computer baseComputer(){
   //==parser
   Parser parser;
   //the amount of commands in parser
   int parserSize;
   {
      vector<Command> commandBank;
      addAllCommands(commandBank);
      parser.addCommands(commandBank);
      parserSize=commandBank.size();
   }
      
   
   
   //==folder system
   //=root   
   Folder root= Folder(Path(Text("")));

   //=root level
   Folder bin= Folder(Path(Text("/bin")));
   Folder boot= Folder(Path(Text("/boot")));
   Folder dev= Folder(Path(Text("/dev")));
   Folder etc= Folder(Path(Text("/etc")));
   Folder home= Folder(Path(Text("/home")));
   Folder lib= Folder(Path(Text("/lib")));
   Folder mnt= Folder(Path(Text("/mnt")));
   Folder opt= Folder(Path(Text("/opt")));
   Folder proc= Folder(Path(Text("/proc")));
   Folder rootFolder= Folder(Path(Text("/root")));
   Folder run= Folder(Path(Text("/run")));
   Folder srv= Folder(Path(Text("/srv")));
   Folder sys= Folder(Path(Text("/sys")));
   Folder tmp= Folder(Path(Text("/tmp")));
   Folder usr= Folder(Path(Text("/usr")));
   Folder var= Folder(Path(Text("/var")));
   Folder lostNfound= Folder(Path(Text("/lost+found")));
   
   //=bin
   File command[parserSize];
   for(int i=0; i<parserSize; i++)
      //                               get the command at index i and get its 1st alias
      command[i]= File(Path(Text("/bin/"+parser.commandDefAt(i).aliases[0])), randomText(100));
   
   //=proc
   File process[100];
   //note that rand() changes every time
   for(int i=0; i<100; i++)
      process[i]= File(Path(Text("/proc/"+randomTextNumbers(5))), randomText(100));
   
   //=dev 
   //drives
   File sda[4];
   sda[0]= File(Path(Text("/dev/sda")), randomText(100));
   for(int i=1; i<4; i++)
      sda[i]= File(Path(Text("/dev/sda")+'0'+i), randomText(100));
   //tty
   File tty[11];
   tty[0]= File(Path(Text("/dev/tty")), randomText(100));
   for(int i=0; i<10; i++)
      tty[i+1]= File(Path(Text("/dev/tty")+('0'+i)), randomText(100));
   //vcs
   File vcs[11];
   vcs[0]= File(Path(Text("/dev/vcs")), randomText(100));
   for(int i=0; i<10; i++)
      vcs[i+1]= File(Path(Text("/dev/vcs")+('0'+i)), randomText(100));
   
   //==add up all of the items
   //=dev
   //drives
   for(int i=0; i<4; i++)
      dev.addFile(sda[i]);
   //tty
   for(int i=0; i<11; i++)
      dev.addFile(tty[i]);
   //vcs
   for(int i=0; i<11; i++)
      dev.addFile(vcs[i]);
   
   //=proc
   for(int i=0; i<100; i++)
      dev.addFile(process[i]);
   
   //=bin TODO
   
   //=root
   root.addFolder(bin);
   root.addFolder(boot);
   root.addFolder(dev);
   root.addFolder(etc);
   root.addFolder(home);
   root.addFolder(lib);
   root.addFolder(mnt);
   root.addFolder(opt);
   root.addFolder(proc);
   root.addFolder(rootFolder);
   root.addFolder(run);
   root.addFolder(srv);
   root.addFolder(sys);
   root.addFolder(tmp);
   root.addFolder(usr);
   root.addFolder(var);
   root.addFolder(lostNfound);
   
   //=init computer
   Computer output;
   output.setRoot(root);

   //==parser

   {
      vector<Command> commandBank;
      addAllCommands(commandBank);
      output.parser.addCommands(commandBank);
   }
   
   
   
   return output;
   
}