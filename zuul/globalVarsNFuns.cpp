/*
  Daren Kostov
  this file stores variables and functions that don't really belong anywgere but are use

*/
#ifndef q
#define q
#include "./text.h"
#include "./globalVarsNFuns.h"
#endif
#include <unistd.h>
#include <stdlib.h>

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



