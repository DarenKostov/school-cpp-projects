/*
  Daren Kostov
*/


#ifndef q
#define q
#include "./text.h"
#include "./path.h"
#include "./file.h"
#include "./folder.h"
#endif
#include <cstring>
#include <vector>

using namespace std;



Folder::Folder(){}


Folder::Folder(Path initPath){
  path=initPath;
}

Folder& Folder::operator=(Folder in){
  return *this;
}

Text Folder::name(){
  return path.name();
}

long Folder::getDate(){
  return date;
}

bool Folder::deleteFile(Text name){
  for(vector<File>::iterator i=files.begin(); i!=files.end(); i++){
    //is the file there, if so remove it
    if(strcmp(name.val(), i->path.name().val())==0){
      files.erase(i);
      return true;
    }
    
  }
  return false;
}

bool Folder::deleteFile(const char* name){
  //use the one with Text
  return deleteFile(Text(name));
}

bool Folder::addFile(File in){
  
  //is there a file with the same name? if so dont add it
  for(int  i=0; i<files.size(); i++){
    if(strcmp(in.name().val(), files[i].path.name().val())==0){
      return false;
    }
  }
  
  //is there a folder with the same name? if so dont add it
  for(int  i=0; i<folders.size(); i++){
    if(strcmp(in.name().val(), folders[i].path.name().val())==0){
      return false;
    }
  }
  
  files.push_back(in);
  updatePaths();
  return true;
}


bool Folder::deleteFolder(Text name){
  for(vector<Folder>::iterator i=folders.begin(); i!=folders.end(); i++){
    //is the file there, if so remove it
    if(strcmp(name.val(), i->path.name().val())==0){
      folders.erase(i);
      return true;
    }
    
  }
  return false;
}

bool Folder::deleteFolder(const char* name){
  //use the one with Text
  return deleteFile(Text(name));
}

bool Folder::addFolder(Folder in){
  
  //is there a file with the same name? if so dont add it
  for(int  i=0; i<files.size(); i++){
    if(strcmp(in.name().val(), files[i].path.name().val())==0){
      return false;
    }
  }
  
  //is there a folder with the same name? if so dont add it
  for(int  i=0; i<folders.size(); i++){
    if(strcmp(in.name().val(), folders[i].path.name().val())==0){
      return false;
    }
  }
  
  folders.push_back(in);
  updatePaths();
  return true;
}

vector<File> Folder::allFiles(){
  return files;
}
  
vector<Folder> Folder::allFolders(){
  return folders;
}

Text Folder::allItems(){
  Text output="files:\n";
  
  for(int i=0; i<files.size(); i++)
      output+=files[i].name()+'\n';
  
  output+="folders:\n";  
  
  for(int i=0; i<folders.size(); i++)
    output+=folders[i].name()+'\n';

  return output;
}


long Folder::usage(){
  long out=0;
  
  //files
  for(int i=0; i<files.size(); i++)
    out+=files[i].usage();
  
  //folders, this will eterate through all child folders, and the children of those, etc until only files are left
  for(int i=0; i<folders.size(); i++)
    out+=folders[i].usage();

  //a folder is bytes
  return out+8;
}


void Folder::updatePaths(){
for(int i=0; i<files.size(); i++)
    files[i].path.changePathOnly(path);
  
  //folders, this will eterate through all child folders, and the children of those, etc until only files are left
  for(int i=0; i<folders.size(); i++){  
    folders[i].path.changePathOnly(path);
    folders[i].updatePaths();
  }
  
  //paths updated
  
}


