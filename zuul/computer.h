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

class Computer{
  public:

    //=init
        
    //computer
    Computer();

    //sets up the folder tree
    void setRoot(Folder);
      
    
  
    //parser
    
  
  private:
    std::map<Path, Folder> allFolders;
    std::map<Path, File> allFiless;
  

};