/*
  Daren Kostov
*/
#ifndef q
#define q
#include "./text.h"
#include "./globalVarsNFuns.h"
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
#include <unistd.h>
#include <stdlib.h>

using namespace std;

//map.find doesnt work so heres a TEMP solution until i figue out why
//search for a SINGLE element in the WHOLE thing
template <class T>
T* find(map<Text, T*> whole, Text single){
  T* out=nullptr;
  cout << whole.size() << "\n" << flush;  
  for(auto i=whole.begin(); i!=whole.end(); i++){
      Text forComparing=i->first;
        error(true, forComparing+'\n');
      if(forComparing==single){
        warning(true, Text("FOUND IT!!!!!!!\n"));
        out=i->second;
        // break;
      }
        unexpectedIO(true, Text("Didnt find it\n"));
    }
  return out;
}



Computer::Computer(){
  memory=Memory();
  
}

void Computer::setRoot(Folder newRoot){
  root=newRoot;
  //get children
  vector<File*> newFiles= root.allFilesAdr();
  vector<Folder*> newFolders= root.allFoldersAdr();
  
  //add children to our map so we know where they are
  for(int i=0; i<newFiles.size(); i++){
    allFiles[newFiles[i]->path.wholeT()]=newFiles[i];
        // cout << newFiles[i]->path.wholeT() << "\n";
  }
  for(int i=0; i<newFolders.size(); i++){
    allFolders[newFolders[i]->path.wholeT()]=newFolders[i];
        cout << newFolders[i]->path.wholeT() << "\n";
        // cout << newFolders[i] << "\n";
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
    info(on, parentPath.wholeT()+"\n");
    
    nextFolder=find(allFolders, parentPath.wholeT());
    currentFolder=nextFolder;
    info(on, Text("going to folder: "+where));
    return true;
  }else{
  
    // all folders in current folders
    vector<Folder> currentChildren=currentFolder->allFolders();
    for(auto i=currentChildren.begin(); i!=currentChildren.end(); i++){
      //if the folder exists
      if(where==i->name()){
        Text name=i->path.wholeT();
        nextFolder=find(allFolders, name);
        currentFolder=nextFolder;
        info(on, name+"\n");
        info(on, nextFolder->path.wholeT()+"\n");
        info(on, currentFolder->path.wholeT()+"\n");
        info(on, Text("going to folder: "+where));
        return true;
      }
    } 
  }
  error(on, Text("unable to locate folder: "+where));
  return false;
}

Folder Computer::getCurrentFolder(){

  return *currentFolder;
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
    allFiles.erase(path.wholeT());
    return true;
  }
  //deletion was not successfull
  return false;
}

