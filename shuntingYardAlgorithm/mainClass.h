/*
  Daren Kostov

  a class that contains the main startup and loop

  it's not called just "Main" because "main" is too close to it
  
*/

#include "stack.h"
#include "queue.h"
#include "binode.h"


class MainClass{

  private:
    //variables:
    Stack<char> operatorStack;
    Stack<BinNode<char>*> binaryTree;
    Queue<char> ioQueue;

    
    
  public:

    //constructor, like a atSTartUp function
    MainClass();

    //deconstror
    ~MainClass();

    //the function that does all the logic, basically the main function
    void startProgram();


};
