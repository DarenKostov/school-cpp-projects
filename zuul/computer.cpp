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

//could be optimized not to search in a folder that the file/folder is for sure not it
File* findFile(Folder* root, Path where){
  
  //every single file in this folder
  auto all=root->allChildFiles();
  
  for(auto i=all.begin(); i!=all.end(); i++){
      if((*i)->path==where){
        return *i;
      }
    }
  return nullptr;
}
Folder* findFolder(Folder* root, Path where){
  
  //every single file in this folder
  auto all=root->allChildFolders();
  
  for(auto i=all.begin(); i!=all.end(); i++){
      if((*i)->path==where){
        return *i;
      }
    }
  return nullptr;
}


Computer::Computer(){
  root=new Folder(Path(Text("")));
  root->addFolder(new Folder(Path(Text("/bin"))));
  root->addFolder(new Folder(Path(Text("/boot"))));
  root->addFolder(new Folder(Path(Text("/dev"))));
  root->addFolder(new Folder(Path(Text("/etc"))));
  root->addFolder(new Folder(Path(Text("/home"))));
  root->addFolder(new Folder(Path(Text("/lib"))));
  root->addFolder(new Folder(Path(Text("/mnt"))));
  root->addFolder(new Folder(Path(Text("/opt"))));
  root->addFolder(new Folder(Path(Text("/proc"))));
  root->addFolder(new Folder(Path(Text("/root"))));
  root->addFolder(new Folder(Path(Text("/run"))));
  root->addFolder(new Folder(Path(Text("/srv"))));
  root->addFolder(new Folder(Path(Text("/sys"))));
  root->addFolder(new Folder(Path(Text("/tmp"))));
  root->addFolder(new Folder(Path(Text("/usr"))));
  root->addFolder(new Folder(Path(Text("/var"))));
  root->addFolder(new Folder(Path(Text("/lost+found"))));

  memory=Memory();

  currentFolder=root;
  
  
  
}

void Computer::setRoot(Folder* newRoot){
  root=newRoot;
}




//=navigation

bool Computer::goTo(Text where){
  Folder* nextFolder;
  
  //go to parent
  if(where==".." || where=="../"){ 
    
    //get parent path
    Path parentPath=currentFolder->path.getParent();
    
    //find the parent
    nextFolder=findFolder(root, Path(parentPath.wholeT()));
    currentFolder=nextFolder;
    
    return true;
  }else{
    //if the folder is in the current folder
    
    // all folders in current folders
    vector<Folder*> currentChildren=currentFolder->allFolders();
    
    for(auto i=currentChildren.begin(); i!=currentChildren.end(); i++){
      
      //if the folder exists
      if(where==(*i)->name()){
        nextFolder=*i;
        currentFolder=nextFolder;
        return true;
      }
    } 
  }
  error(on, Text("Unable to locate folder: \""+where+'"'));
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
    // allFiles.erase(path.wholeT());
    return true;
  }
  //deletion was not successfull
  return false;
}

