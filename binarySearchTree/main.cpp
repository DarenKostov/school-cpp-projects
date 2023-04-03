/*
  Daren Kostov
  Binary Search Tree



*/

#include "mainClass.h"

#include <iostream>
#include <csignal>


//at exit free the MainClass object 
void atExitFree(MainClass*);

static void freeVariable(){

    std::cout << "\e[93mAbout to Free Main\n\e[0m";
    atExitFree(NULL);
}

void atExitFree(MainClass* in){

    //store a static pointer to our Main
    static MainClass* eternalPtr;


    //if we give it a valid pointer, store it; if not, delete it
    if(in){
        std::cout << "\e[93mStoring Main\n\e[0m";
        eternalPtr=in;
        atexit(freeVariable);
    }else{
        std::cout << "\e[93mFreeing Main\n\e[0m";
        delete eternalPtr;
    }
}




void signal_handler(int signal_num){

  std::cout << "\n\e[93mSignal Handler!\n";
  std::cout << "Signal: " << signal_num << "\n\e[0m";
  exit(signal_num);
}


int main(){

  std::cout << "\e[93mstart of program\n\e[0m";

  signal(SIGINT, signal_handler);


  MainClass* mainInstance=new MainClass();
  atExitFree(mainInstance);

  mainInstance->startProgram();
  

}
