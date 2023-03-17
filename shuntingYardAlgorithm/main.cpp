/*
  Daren Kostov
  Shunting Yard Algorithm

  sources:
  https://stackoverflow.com/questions/24930162/exists-a-way-to-free-memory-in-atexit-or-similar-without-using-global-variables

*/

#include "queue.h"
#include "stack.h"
typedef Stack<char> StackC;
typedef Queue<char> QueueC;




























#include <iostream>
#include <csignal>
// #include "text.h"


//at exit free the varible "in" 
void atExitFree(void*);

static void freeVariable(void){

    std::cout << "freeing the variable!";
    
    atExitFree(NULL);
}

void atExitFree(void* in){

    //store a static pointer to our variable
    static void* eternalPtr;


    //if we give it a valid pointer, store it; if not, delete it
    if(in){
        eternalPtr=in;
        atexit(freeVariable);
    }else{

        delete eternalPtr;
    
        // if(std::is_array<eternalPtr>::value==true)
        //   delete[] eternalPtr;
        // else
        //   delete eternalPtr;
    }
}




void signal_handler(int signal_num){

  std::cout << "Signal Handler!\n";
  
  exit(signal_num);
}

struct someClass{
  someClass(){
    variable=new int[10];
  }
  ~someClass(){
    delete[] variable;
  }
  int* variable;
};

int main(){

  std::cout << "start of program\n";

  signal(SIGINT, signal_handler);


  // someClass* var=new someClass();
  // // delete var;
  // atExitFree(var);

  
  int* var2=new int;
  // delete var;
  atExitFree(var2);

    while(true)
      1;

  

}
