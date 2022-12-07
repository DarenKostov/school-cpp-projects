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

class Parser{
  public:
    Parser(char AllCommands[20][10][15], char AllCommandsDescription[20][50], char allCommandArgsDef[20][10][5], char AllCommandsArgs[20][50]);
    void readLn();
    void* returnCommand(int i);
  private:
    int commandsAmount=20;
    int commandsWordLength=15;
    int aliasesAmount=10;
    int argumentsAmount=10;
    int descriptionLength=50;

    char allCommands[20][10][15];
    char allCommandsDescription[20][50];
    char allCommandArgsDef[20][10][5];
    char allCommandsArgs[20][50];
    char input[99];
    char command[10][15];
    bool fixCommand();
    bool fixArgs();
    int commandIndex;


};