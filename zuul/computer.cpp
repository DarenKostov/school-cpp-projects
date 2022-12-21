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

Computer::Computer(){
}

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
  
  //we are starting from root
  currentFolder=&root;
}




//=navigation

bool Computer::goTo(Text where){
  Folder* nextFolder;
  
  //go to parent
  if(where==".." || where=="../"){ 
    //get parent path
    Path parentPath=currentFolder->path.getParent();
   
    nextFolder=allFolders.at(parentPath);
    currentFolder=nextFolder;
    return true;
  }else{
  
    // all folders in current folders
    vector<Folder> currentChildren=currentFolder->allFolders();
    for(auto i=currentChildren.begin(); i!=currentChildren.end(); i++){
      //if the folder exists
      if(where==i->name()){
        
        nextFolder=allFolders.at(i->path);
        currentFolder=nextFolder;
      }
    } 
  }
  return false;
}





//=files

bool Computer::deleteFile(Text name){
  Path path;
  //first check if we are giving the name or full path
  if(name[0]=='/'){
    // //delete by full path
    //==Currently you can delete files only by name if you are in their parent directory
  }
  
  //delete by name
    
  //get path
  // "/path/to/folder" + "/" + "name of file" 
  path=currentFolder->path.wholeT()+'/'+name;
  
  //if deletion is successfull
  if(currentFolder->deleteFile(name)){
    allFiles.erase(path);
    return true;
  }
  //deletion was not successfull
  return false;
}




