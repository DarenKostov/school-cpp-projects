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
      {"look", "l", "lookaround", "la", "list", "ls"},
   };
   
   char ALLCOMMANDSDESCRIPTION[20][50]={
      "this help",
      "gives a list of all the features",
      "gives you tips"
      "go in a direction"
   };
   
   //str, int, bool 
   char ALLCOMMANDSARGSDEF[20][10][5]={
      {},
      {},
      {},
      {"str"}
   };
   
   char ALLCOMMANDSARGS[20][50]={
      "none",
      "none",
      "none",
      "direction"
   };
   
   
   Parser parser= Parser(ALLCOMMANDS, ALLCOMMANDSDESCRIPTION, ALLCOMMANDSARGSDEF, ALLCOMMANDSARGS);
   
   parser.readLn();
   
   
   for (int i=0; i<10; i++)
      cout << parser.returnCommand(i) << endl;
   
   
return 0;

}
