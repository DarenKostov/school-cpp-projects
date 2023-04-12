/*
  Daren Kostov

  a class that contains the main startup and loop

  it's not called just "Main" because "main" is too close to it
  
*/

#include "binnode.h"
#include <utility>


class MainClass{

  private:
    //variables:
    BinNode<int>* root;
    std::pair<int, int> redVsBlack;
    
  public:

    //constructor, like a atSTartUp function
    MainClass();

    //deconstror
    ~MainClass();

    //the function that does all the logic, basically the main function
    void startProgram();

};
