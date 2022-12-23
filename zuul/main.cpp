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


//commands from user
void execCD(Computer&);
void execLS(Computer&);
void execCAT(Computer&);


int main(){
   
   bool isColorOn=true;
   
   
   slowtalk(isColorOn, "Welcome to Zuul", Daren_talking);
   fasttalk(isColorOn, "\n\n  This project is not ready", Daren_thinking);
   // slowtalk(isColorOn, ".....", Daren_thinking, 50);
   fasttalk(isColorOn, "\n\n  Should be ready soon thought.\n\n", Daren_thinking);
   fasttalk(isColorOn, "\n\n  ...I hope...\n\n", Daren_thinking);
   
   
   
   Computer myComputer= Computer();
   myComputer.on=true;
   
   
   myComputer.parser.readLn();
   
   
   
   while(true){
      //current command
      Text curCom=myComputer.parser.returnCommandT(0);
      if(curCom=="cd")
         execCD(myComputer);
      else if(curCom=="ls")
         execLS(myComputer);
      else if(curCom=="cat")
         execCAT(myComputer);
      else if(curCom=="exit")
         break;
      else
         unexpectedIO(myComputer.on, "The command inputted is non existant.");
      
      myComputer.parser.readLn();
      
   }
   
   
   cout << "END\n";
   return 0;
}



//==commands from user
void execCD(Computer& inComp){
   if(inComp.goTo(inComp.parser.returnCommandT(1)))
      // execLS(inComp);
      1==1;
}
void execLS(Computer& inComp){
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
}
   
void execCAT(Computer& inComp){
   File* file=inComp.getFile(inComp.parser.returnCommandT(1));
   if(file!=nullptr)
   fasttalk(inComp.on, file->cont()+'\n');
}





