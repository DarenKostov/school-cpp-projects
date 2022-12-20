/*
  Daren Kostov
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
#include "./computer.h"
#endif

#include <vector>
#include <map>
#include <ctime>

using namespace std;

Computer::Computer(){}

void Computer::setRoot(Folder newRoot){
  root=newRoot;
  //get children
  vector<File*> newFiles= root.allFilesAdr();
  vector<Folder*> newFolders= root.allFoldersAdr();
  
  //add children to our map so we know where they are
  for(int i=0; i<newFiles.size(); i++){
    allFiles[newFiles[i]->path]=newFiles[i];
  }
  for(int i=0; i<newFolders.size(); i++){
    allFolders[newFolders[i]->path]=newFolders[i];
  }
  
  
}


//=files






