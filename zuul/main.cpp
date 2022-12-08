/*

   Daren Kostov
   Zuul
   11/01/2022

resources used:
https://www.geeksforgeeks.org/getline-string-c/

*/
#include <iostream>
#include <vector>
#include <cstring>


#include "./parser.h"
#include "./command.h"

using namespace std;


int main (){
   
   char ALLCOMMANDS[20][10][15]={
      {"help", "h"},
      {"features", "feature", "f"},
      {"tips", "ti"},
      {"go", "goto", "g"},
      {"take", "t",},
      {"use", "u", "utilize"},
      {"drop", "d", "letgoof"},
      {"inventory", "i", "inv"},
      {"quit", "q", "exit", "e", "leave", ":q"},
      {"look", "l", "lookaround", "la", "list", "ls", "description", "desc"},
   };
   
   char ALLCOMMANDSDESCRIPTION[20][50]={
      "this help",
      "gives a list of all the features",
      "gives you tips"
      "go in a direction"
   };
   
   //cmd is the command, first argument
   //cmd, str, int, bool 
   char ALLCOMMANDSARGSDEF[20][10][5]={
      {"cmd"},
      {"cmd"},
      {"cmd"},
      {"cmd", "str"},        //go
      {"cmd", "str", "int"}, //take
      {"cmd", "str"},        //use
      {"cmd", "str", "int"}, //drop
      {"cmd"},
      {"cmd"},
      {"cmd"},
   };
   
   char ALLCOMMANDSARGS[20][50]={
      "none",
      "none",
      "none",
      "direction"
   };
   
   
   // Parser parser= Parser(ALLCOMMANDS, ALLCOMMANDSDESCRIPTION, ALLCOMMANDSARGSDEF, ALLCOMMANDSARGS);
   
   // cout << "reading line:" << endl;
   // parser.readLn();
   
   // cout << "printing line" << endl;

   // for (int i=0; i<10; i++)
   //    cout << parser.returnCommand(i) << endl;
   
   // cout << "done printing" << endl;
   
   // Command go= Command(2, {"go", "g"}, "go somewhere", 1, {"cmd"}, "none");   
   
   char** helpAls= new char*[2];
   helpAls[0]= new char[5];
   helpAls[1]= new char[2];
   strcpy(helpAls[0], "help");
   strcpy(helpAls[1], "h");
   
   char** helpArg= new char*[0];
   helpArg[0]= new char[4];
   strcpy(helpArg[0], "cmd");
   
   Command help= Command(2, ALLCOMMANDS[0], ALLCOMMANDSDESCRIPTION[0], 1, helpArg, ALLCOMMANDSARGS[0]);   
   
   cout << help.aliases[0] << endl;
   cout << help.aliases[1] << endl;
   cout << help.description << endl;
   
   
return 0;

}
