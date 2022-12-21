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

class Computer{
  public:

    //=init
        
    //computer
    Computer();
  
    //sets up the folder tree
    void setRoot(Folder);
  
    //=files
    //deletes a file from name OR path
    bool deleteFile(Text);
  
    //create a file from name OR path
    bool createFile(File, Text);
  
    //get full access to file with name or path
    File& getFile(Text);
    
    //=folders
    
    //deletes a folder from name OR path
    bool deleteFolder(Text);
  
    //create a folder from name OR path
    bool createFolder(Folder, Text);
  
    //get a copy of a folder with name or path
    Folder getFolder(Text);
  
    //=currentFolder
    
    //gives you acopy of the current folder
    Folder getCurrentFolder();
      
    //changes your current folder to from name or path
    bool goTo(Text);
    
    //the parser manages itself, no need to be private
    //command parser
    Parser parser;  
  
  private:
    Folder* currentFolder;
    Text* currentUser;  
  
    // root folder (not root user folder)
    Folder root;
  
    std::map<Path, Folder*> allFolders;
    std::map<Path, File*> allFiles;
    
 
};