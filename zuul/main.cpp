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
   char ALLCOMMANDS[10][10][10]={
      {"help", "h"},
      {"features", "feature", "f"},
      {"tips", "ti"},
      {"go", "goto", "g"},
   };
   
   char ALLCOMMANDSDESCRIPTION[10][50]={
      "this help",
      "gives a list of all the features",
      "gives you tips"
      "go in a direction"
   };
   
   //str, int, float, bool, 
   char ALLCOMMANDSARGSDEF[10][10][10]={
      {},
      {},
      {},
      {"str"}
   };
   
   char ALLCOMMANDSARGS[10][20]={
      "none",
      "none",
      "none",
      "direction"
   };
   
   
   Parser parser= Parser(ALLCOMMANDS, ALLCOMMANDSDESCRIPTION, ALLCOMMANDSARGS);
   
   parser.readLn();
   
   
   for (int i=0; i<10; i++)
      cout << parser.returnCommand(i) << endl;
   
   
return 0;

}
