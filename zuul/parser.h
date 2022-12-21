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

//watch out fot "command" capitalization in the comments

class Parser{
  public:
    Parser();
    ~Parser();
    void addCommand(Command*); //adds a single Command from a Command POINTER
    void addCommands(std::vector<Command*>); //adds Commands from a vector of Command POINTERS
    void addCommand(Command); //adds a single Command from a Command
    void addCommands(std::vector<Command>); //adds Commands from a vector of Commands
    
    //removes a command given its 1st alias
    bool removeCommand(Text);
  
    void readLn();
  
    template <class output>
    output returnCommand(int i){ //returns what is the command/argument inputed at that index
    //cast the output type to the void, add i to it (go to index i), and de-reference it
      return *((output*)command+i);
    }

    Text returnCommandT(int i);// returns what is the command/argument inputed at that index in Text form`
    int getCommandIndex(); //returns the current command index in the Command vector
    Command commandDefAt(int);// returns what is the Command definition at an index
  
  private:
    //all Commands should be stored in the parser since its safer, we dont want main to delete the commands and the parser to throw a seg fault
    std::vector<Command> allCommands; //where all posible Commands are stored
    
    //the command inputed
    void* command; //the current commands inputed with its inputed arguments (cast a type pointer of the type it should be)
    Text* commandText; // the command inputed but in Text form
    int commandLength; // the amount of arguments inputed, believe it or not without this there is a major seg fault
  
    bool setCurrentCommand(Text); //determines what command the user inputed, returns false if it couldnt determine
    void fixArgs(Text*, int); // fixes the arguments inputed returns 1 for success
    int commandIndex; // the current command index
    Command* currentCommandDef; // the current command inputed definition
    
    Command emptyCommand;//an empty command


};