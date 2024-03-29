/*
  Daren Kostov
*/


#ifndef q
#define q
#include "./text.h"
#include "./globalVarsNFuns.h"
#include "./path.h"
#include "./file.h"
#include "./folder.h"
#endif
#include <cstring>
#include <vector>
#include <ctime>

using namespace std;



Folder::Folder(){
  path=Path();
  date=time(nullptr);
}

Folder::~Folder(){
  // emptyMe();
}

Folder::Folder(Path initPath){
  path=initPath;
  date=time(nullptr);
}

Folder& Folder::operator=(Folder in){
  path=in.path;
  files=in.allFiles();
  folders=in.allFolders();
  date=in.getDate();
  return *this;
}

Text Folder::name(){
  return path.name();
}

time_t Folder::getDate(){
  return date;
}

//==file

bool Folder::deleteFile(Text name){
  for(auto i=files.begin(); i!=files.end(); i++){
    //is the file there, if so remove it
    if(strcmp(name.val(), (*i)->path.name().val())==0){
      delete *i;
      files.erase(i);
      //update time, we modified the folder
      date=time(nullptr);
      return true;
    }
    
  }
  return false;
}

bool Folder::deleteFile(const char* name){
  //use the one with Text
  return deleteFile(Text(name));
}

bool Folder::addFile(File* in){
  
  //is there a file with the same name? if so dont add it
  for(auto i=files.begin(); i!=files.end(); i++){
    if(in->name()==(*i)->path.name()){
      return false;
    }
  }
  
  //is there a folder with the same name? if so dont add it
  for(auto i=folders.begin(); i!=folders.end(); i++){
    if(in->name()==(*i)->path.name()){
      return false;
    }
  }
  
  files.push_back(in);
  updatePaths();
  //update time, we modified the folder
  date=time(nullptr);
  return true;
}


vector<File*> Folder::allChildFiles(){
  vector<File*> output;
  
  for(auto i=files.begin(); i!=files.end(); i++)
    //adress of the derefrenced file iterator
    output.push_back(*i);
  
  for(auto i=folders.begin(); i!=folders.end(); i++){
    
    //get the children's files
    vector<File*> childFiles=(*i)->allChildFiles(); 
    
    //add them to output
    for(auto j=childFiles.begin(); j!=childFiles.end(); j++)
      output.push_back(*j);
  }
  
  return output;
}

File* Folder::getFile(Text name){
  for(auto i=files.begin(); i!=files.end(); i++)
    //if file is found
    if(name==(*i)->path.name())
      return *i;   
  
  //file is not found
  return nullptr;
}


//==folder

bool Folder::deleteFolder(Text name){
  for(auto i=folders.begin(); i!=folders.end(); i++){
    //is the file there, if so remove it
    if(name==(*i)->path.name()){
      (**i).emptyMe();
      delete *i;
      folders.erase(i);
      //update time, we modified the folder
      date=time(nullptr);
      return true;
    }
    
  }
  return false;
}

bool Folder::deleteFolder(const char* name){
  //use the one with Text
  return deleteFile(Text(name));
}

bool Folder::addFolder(Folder* in){
  
  //is there a file with the same name? if so dont add it
  for(auto i=files.begin(); i<files.end(); i++){
    if(in->name()==(**i).path.name()){
      return false;
    }
  }
  
  //is there a folder with the same name? if so dont add it
  for(auto i=folders.begin(); i<folders.end(); i++){
    if(in->name()==(**i).path.name()){
      return false;
    }
  }
  
  folders.push_back(in);
  updatePaths();
  //update time, we modified the folder
  date=time(nullptr);
  return true;
}

vector<File*> Folder::allFiles(){
  return files;
}
  
vector<Folder*> Folder::allFolders(){
  return folders;
}


vector<Folder*> Folder::allChildFolders(){
  vector<Folder*> output;
  
  for(auto i=folders.begin(); i!=folders.end(); i++){
    
    //add the children
    //adress of the derefrenced folder iterator
    output.push_back(*i);
    
    //get the childrens's folders
    vector<Folder*> childFolders=(*i)->allChildFolders(); 
    
    //add them to output
    for(auto j=childFolders.begin(); j!=childFolders.end(); j++)
      output.push_back(*j);
  }
  
  return output;
}

Folder* Folder::getFolder(Text name){
  for(auto i=folders.begin(); i!=folders.end(); i++)
    //if file is found
    if(name==(*i)->path.name())
      return *i;   
  
  //file is not found
  return nullptr;
}


void Folder::printTree(bool color){
  printTree(color, 0);
}

void Folder::printTree(bool color, int level){
  if(path.len()==0)
    fasttalk(color, "/\n", folderColor);
  else
    fasttalk(color, name()+'\n', folderColor);

  
  for(auto i=files.begin(); i!=files.end(); i++){
    for(int j=0; j<level; j++)
      cout << "  " << flush;
    fasttalk(color, "├─"+(**i).name()+'\n', fileColor);
  }
  
  for(auto i=folders.begin(); i!=folders.end(); i++){
    for(int j=0; j<level; j++)
      cout << "  " << flush;
    fasttalk(color, "├─");
    (**i).printTree(color, level+1);
  }
  
}



void Folder::emptyMe(){
  //delete all files
  for(auto i=files.begin(); i!=files.end(); i++){
    delete *i;
    files.erase(i);
  }

  //delete all folders, recursevely
  while(folders.size()!=0){
    //make sure its empty when deleting it | lets not do that, causes multiple delete sequences | nvm lets actually do this and fix whats actually the problem
    (*folders.begin())->emptyMe();
    delete *folders.begin();
    folders.erase(folders.begin());   
  }
  
}



Text Folder::allItems(){
  Text output="files:\n";
  
  for(int i=0; i<files.size(); i++)
      output+=files[i]->name()+'\n';
  
  output+="folders:\n";  
  
  for(int i=0; i<folders.size(); i++)
    output+=folders[i]->name()+'\n';

  return output;
}


long Folder::usage(){
  long out=0;
  
  //files
  for(int i=0; i<files.size(); i++)
    out+=files[i]->usage();
  
  //folders, this will eterate through all child folders, and the children of those, etc until only files are left
  for(int i=0; i<folders.size(); i++)
    out+=folders[i]->usage();

  //a folder is bytes
  return out+8;
}


void Folder::updatePaths(){
for(int i=0; i<files.size(); i++)
    files[i]->path.changeParentOnly(path);
  
  //folders, this will iterate through all child folders, and the children of those, etc until only files are left
  for(int i=0; i<folders.size(); i++){  
    folders[i]->path.changeParentOnly(path);
    folders[i]->updatePaths();
  }
  
  //paths updated
  
}


  


