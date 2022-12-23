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
#include <ctime>

using namespace std;



Folder::Folder(){
  date=time(nullptr);
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
  for(int  i=0; i<files.size(); i++){
    if(strcmp(in->name().val(), files[i]->path.name().val())==0){
      return false;
    }
  }
  
  //is there a folder with the same name? if so dont add it
  for(int  i=0; i<folders.size(); i++){
    if(strcmp(in->name().val(), folders[i]->path.name().val())==0){
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
    //adress of the derefrenced folder iterator
    // output.push_back(&*i);
    
    //get the children's files
    vector<File*> childFiles=(*i)->allChildFiles(); 
    
    //add them to output
    for(auto j=childFiles.begin(); j!=childFiles.end(); j++)
      output.push_back(*j);
  }
  
  return output;
}



//==folder

bool Folder::deleteFolder(Text name){
  for(auto i=folders.begin(); i!=folders.end(); i++){
    //is the file there, if so remove it
    if(strcmp(name.val(), (*i)->path.name().val())==0){
      (*i)->emptyMe();
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
  for(int  i=0; i<files.size(); i++){
    if(strcmp(in->name().val(), files[i]->path.name().val())==0){
      return false;
    }
  }
  
  //is there a folder with the same name? if so dont add it
  for(int  i=0; i<folders.size(); i++){
    if(strcmp(in->name().val(), folders[i]->path.name().val())==0){
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
  
  //folders, this will eterate through all child folders, and the children of those, etc until only files are left
  for(int i=0; i<folders.size(); i++){  
    folders[i]->path.changeParentOnly(path);
    folders[i]->updatePaths();
  }
  
  //paths updated
  
}


  


