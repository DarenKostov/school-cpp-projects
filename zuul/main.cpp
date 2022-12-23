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
   
   
   
   Computer myComputer= Computer();
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



//==commands from user
void execCD(Computer& inComp){
   if(inComp.goTo(inComp.parser.returnCommandT(1)))
      execLS(inComp);
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
         fasttalk(inComp.on, (*i)->getDate(), folderColor);
         fasttalk(inComp.on, ' '+(*i)->path.wholeT()+'\n', folderColor);
      }else
         fasttalk(inComp.on, (*i)->name() +spacer, folderColor);
   
   
   
   //all Files
   auto allFile=inComp.getCurrentFolder().allFiles();
   for(auto i=allFile.begin(); i!=allFile.end(); i++)   
      if(longList){
         fasttalk(inComp.on, (*i)->getDate(), folderColor);
         fasttalk(inComp.on, ' '+(*i)->path.wholeT()+'\n', folderColor);
      }else
         fasttalk(inComp.on, (*i)->name() +spacer, folderColor);
   
   fasttalk(inComp.on, Text("\n"), Info);
}
   





