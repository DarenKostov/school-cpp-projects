/*
  Daren Kostov
  this file stores variables and functions that don't really belong anywgere but are use

   sources used:
   https://www.delftstack.com/howto/cpp/how-to-convert-int-to-char-array-in-cpp/
   
*/
#ifndef q
#define q
#include "./text.h"
#include "./globalVarsNFuns.h"
#endif
#include <unistd.h>
#include <stdlib.h>
#include <charconv>

using namespace std;




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
      cout << "\033[0m" << flush;
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
      cout << "\033[0m" << flush;
}

void fasttalk(bool on, Text in){
   //are we coloring this?
   if(on)
      cout << "\033[0m" << flush;
   //print everything
   for(int i=0; i<in.len(); i++){
      cout << in[i] << flush;
      slep(1);
    }
}



void slep(){
  usleep(printSpeed);
}
void slep(int x){
  usleep(x*printSpeed);
}
void uSlep(){
  usleep(rand()%(printSpeed/2)+printSpeed/2);
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



Text intToText(int in){
   char outputChar[13];
   to_chars(outputChar, outputChar+12, in);
   return Text(outputChar);
}
