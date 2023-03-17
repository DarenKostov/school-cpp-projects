/*
  Daren Kostov
  Shunting Yard Algorithm

  sources:
  https://stackoverflow.com/questions/24930162/exists-a-way-to-free-memory-in-atexit-or-similar-without-using-global-variables

*/

#include "mainClass.h"

#include <iostream>
#include <csignal>


//at exit free the MainClass object 
void atExitFree(MainClass*);

static void freeVariable(){

    std::cout << "About to Free Main\n";
    atExitFree(NULL);
}

void atExitFree(MainClass* in){

    //store a static pointer to our Main
    static MainClass* eternalPtr;


    //if we give it a valid pointer, store it; if not, delete it
    if(in){
        std::cout << "Storing Main\n";
        eternalPtr=in;
        atexit(freeVariable);
    }else{
        std::cout << "Freeing Main\n";
        delete eternalPtr;
    }
}




void signal_handler(int signal_num){

  std::cout << "Signal Handler!\n";
  std::cout << "Signal: " << signal_num << "\n";
  exit(signal_num);
}


int main(){

  std::cout << "start of program\n";

  signal(SIGINT, signal_handler);


  MainClass* mainInstance=new MainClass();
  atExitFree(mainInstance);

  mainInstance->startProgram();
  

}
