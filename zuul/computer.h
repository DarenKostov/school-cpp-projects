/*
  Daren Kostov
  A computer class that stores memory, files, etc


*/
#ifndef q
#define q
#include "./text.h"
#include "./command.h"
#include "./parser.h"
#include "./path.h"
#include "./file.h"
#include "./memory.h"
#include "./folder.h"
#endif

#include <vector>
#include <map>
#include <ctime>

File* findFile(Folder* root, Path where);
Folder* findFolder(Folder* root, Path where);




class Computer{
  public:

    //=init
        
    //computer
    Computer(Text, Text);
  
    //sets up the folder tree
    void setRoot(Folder*);
  
    //=files
    //deletes a file from name OR path
    bool deleteFile(Text);
  
    //create a file from name OR path
    bool createFile(File, Text);
  
    //get adress to file with name or path
    File* getFile(Text);
    
    //=folders
    
    //deletes a folder from name or path
    bool deleteFolder(Text);
  
    //create a folder from name
    bool createFolder(Folder, Text);
  
    //get a copy of a folder with name or path
    Folder getFolder(Text);
  
    //=navigation
    
    //gives you a copy of the current folder
    Folder getCurrentFolder();
      
    //changes your current folder to from name or path
    bool goTo(Text);
    
    //gives you the user's name
    Text getUser();
    //gives you the host's name
    Text getHost();

    //=ram

    //gives you how mych of the ram us used
    long getRamUsage();

    //gives you how much of the ram isnt used
    long getRamFree();

    //gives you the total amount of Ram
    long getRamTotal();

    //copies a FILE (given path)(folders are not supporet yet) to the ram
    bool copyToRam(Text);
  
    //pastes a file from Ram given its id to given path, the id loops to the beginign if you give one thats not there
    bool pasteFromRam(int, Text);

    //prints at most 10 items that are in the ram with their coresponding id
    void printItemsInRam(); 

    bool clearRam();

    //the parser manages itself, no need to be private
    //command parser
    Parser parser;  
    
    //weather color is off or on
    bool on;
  
  private:
  
    //this must be envoked each time an action is performed, be it sucessfull or unsucessfull
    void justPerformedATask();
  
    //the user
    Text user;
    //the host
    Text host;
    
    //where are we now
    Folder* currentFolder;
    //the ram
    Memory memory;
    // root folder (not root user folder)
    Folder* root;
    
    //some functions
    void addAllCommands();
};


