//readLn- reads a line and puts it in the parsers memory

// returnCommand- itll return the command/arguments dependig on what you give it
// 0-command
// 1-arg 1
// 2-arg 2
// etc

//inpit stores the entire line
//command store each induvudual command and argment in the line

//fixCommand- fixes the command input as well as apply aliases

//commandIndex is the index of the inputed command (help is 0, features is 1, tips is 2, etc) 

#include <vector>


#ifndef q
#define q
#include "./text.h"
#include "./command.h"
#endif



class Parser{
  public:
    Parser();
    ~Parser();
    void addCommand(Command*); //adds a single command from a command POINTER
    void addCommands(std::vector<Command*>); //adds commands from a vector of command POINTERS
    void readLn();
  
    template <class output>
    output returnCommand(int i){
    //cast the output type to the void, add i to it (go to index i), and de-reference it
      return *((output*)command+i);
    }
  private:
    std::vector<Command*> allCommands;  
    void* command;
    bool fixCommand();
    bool fixArgs();
    int commandIndex;
    


};