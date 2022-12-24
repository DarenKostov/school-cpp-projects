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
https://cplusplus.com/forum/beginner/4639/
https://www.geeksforgeeks.org/typedef-in-cpp/

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


//commands from user

//typedef function pointer 
typedef bool (*Exec)(Computer&);


bool execCD(Computer&);
bool execLS(Computer&);
bool execCAT(Computer&);
bool execTOUCH(Computer&);
bool execRM(Computer&);
bool execMKDIR(Computer&);
bool execPWD(Computer&);
bool execCLEAR(Computer&);

int main(){
   
   bool isColorOn=true;
   
   //array of function pointers
   Exec exec[]={
      execCAT,
      execLS,
      execCD,
      execTOUCH,
      execRM,
      execMKDIR,
      execPWD,
      execCLEAR,
   };
   //an array of what these functions actually are
   Text execDef[]={
      "cat",
      "ls",
      "cd",
      "touch",
      "rm",
      "mkdir",
      "pwd",
      "clear",
   };
   
   
   
   slowtalk(isColorOn, "Welcome to Zuul", Daren_talking);
   fasttalk(isColorOn, "\n\n  This project is not ready", Daren_thinking);
   // slowtalk(isColorOn, ".....", Daren_thinking, 50);
   fasttalk(isColorOn, "\n\n  Should be ready soon thought.\n\n", Daren_thinking);
   fasttalk(isColorOn, "\n\n  ...I hope...\n\n", Daren_thinking);
   
   
   
   Computer myComputer= Computer(Text("DAK"), Text("001"));
   myComputer.on=true;
     
   
   do{
      
      //[user@host pwd]#
      fasttalk(myComputer.on, "["+myComputer.getUser()+"@"+myComputer.getHost()+" ");
      if(myComputer.getCurrentFolder().path.len()==0)
         fasttalk(myComputer.on, "/");
      else
         fasttalk(myComputer.on,myComputer.getCurrentFolder().path.wholeT());
      fasttalk(myComputer.on,Text("]# "));
      
      
      myComputer.parser.readLn();
      
      //current command
      Text curCom=myComputer.parser.returnCommandT(0);
      
      
      
      int commandAmount=sizeof(execDef)/sizeof(Text);
      for(int i =0; i<(1+commandAmount); i++){
         if(i==commandAmount){
            unexpectedIO(myComputer.on, "The command inputted is non existant.");
            break;
         }
         
         if(curCom==execDef[i]){
            if(exec[i](myComputer))
               info(myComputer.on, "Action successful.");
            else
               info(myComputer.on, "Action unsuccessful.");
         
            break;
         }
      }
      
   }while(true);
   
   
   cout << "END\n";
   return 0;
}



//==commands from user
bool execCD(Computer& inComp){
   if(inComp.goTo(inComp.parser.returnCommandT(1)))
      return true;
   return false;
}
bool execLS(Computer& inComp){
   char spacer='\t';
   
   //long listing format
   bool longList=false;
   
   Text flags=inComp.parser.returnCommandT(1);
   //take in flags only if they are prefixed with a dash
   if(flags[0]=='-'){
      //if any l
      if(flags[1]=='l' || flags[2]=='l')
         longList=true;
      //if 1
      else if(flags[1]=='1')
         spacer='\n';  
   }
   
   //all Folders
   auto allFold=inComp.getCurrentFolder().allFolders();
   for(auto i=allFold.begin(); i!=allFold.end(); i++)
      if(longList){
         fasttalk(inComp.on, intToText((*i)->getDate()), folderColor);
         fasttalk(inComp.on, ' '+(*i)->path.wholeT()+'\n', folderColor);
      }else
         fasttalk(inComp.on, (*i)->name() +spacer, folderColor);
   
   
   
   //all Files
   auto allFile=inComp.getCurrentFolder().allFiles();
   for(auto i=allFile.begin(); i!=allFile.end(); i++)   
      if(longList){
         fasttalk(inComp.on, intToText((*i)->getDate()), fileColor);
         fasttalk(inComp.on, ' '+(*i)->path.wholeT()+'\n', fileColor);
      }else
         fasttalk(inComp.on, (*i)->name() +spacer, fileColor);
   
   fasttalk(inComp.on, Text("\n"), Info);
   
   
   //i cannot see a situation where this action would be unsuccessful
   return true;
   
}
   
bool execCAT(Computer& inComp){
   File* file=inComp.getFile(inComp.parser.returnCommandT(1));
   if(file!=nullptr){
      fasttalk(inComp.on, file->cont()+'\n');
      return true;
   }
   return false;
}

bool execTOUCH(Computer& inComp){
   Text name=inComp.parser.returnCommandT(1);
   if(inComp.createFile(File(Path("/a/"+name)), name))
      return true;
   return false;
}


bool execRM(Computer& inComp){
   
   Text flag=inComp.parser.returnCommandT(1);
   
   
   //are we deleting a folder(-r) or a file(none)
   //for simplicity -r works only on files
   if(flag=="-r"){
      if(inComp.deleteFolder(inComp.parser.returnCommandT(2))){
         info(inComp.on, "Folder removed recursively.");
         return true;
      }
   }else{
      if(inComp.deleteFile(flag)){
         info(inComp.on, "File removed.");
         return true;
      }
   }
   return false;
   
}
bool execMKDIR(Computer& inComp){
   Text name=inComp.parser.returnCommandT(1);
   if(inComp.createFolder(Folder(Path("/a/"+name)), name))
      return true;
   return false;
}

bool execPWD(Computer& inComp){
   
   if(inComp.getCurrentFolder().path.len()==0)
      fasttalk(inComp.on, "/\n");
   else
      fasttalk(inComp.on,inComp.getCurrentFolder().path.wholeT()+'\n');
   
   return true;
}

bool execCLEAR(Computer& inComp){
   for(int i=0; i<1000; i++)
      cout << '\n' << flush;   
   return true;
}

