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
  
    //=currentFolder
    
    //gives you a copy of the current folder
    Folder getCurrentFolder();
      
    //changes your current folder to from name or path
    bool goTo(Text);
    
  
    //gives you the user's name
    Text getUser();
    //gives you the host's name
    Text getHost();
  
    //the parser manages itself, no need to be private
    //command parser
    Parser parser;  
    
    //weather color is off or on
    bool on;
  
  private:
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


