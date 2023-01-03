/*
  Daren Kostov
*/


#include <vector>

#ifndef q
#define q
#include "./text.h"
#include "./path.h"
#include "./file.h"
#include "./memory.h"
#endif

using namespace std;

Memory::Memory(){
  capacity=1024;
  usage=0;
}

Memory::Memory(long in){
  capacity=in;
  usage=0;
}

bool Memory::addFile(File in){
  //check if enough memory
  if(in.usage()+usage>capacity)
    return false;
  
  //add to memory
  usage+=in.usage();
  files.push_back(in);
  return true;
}

bool Memory::removeFile(int i){
  //check if it exists
  if(i<0 || i>files.size()-1)
    return false;
  
  //remove from memory
  usage-=files[i].usage();
  files.erase(files.begin()+i);
  return true;
}

Text Memory::AllItems(){
  Text output;
  //shows up to 10 files
  for(int i=0; i<min(10, (int)files.size()); i++)
    // "{index}: {path}\n"
    output+=(Text(i)+": "+files[i].path.wholeT()+'\n');
  return output;
}

File Memory::getFile(int i){
  if(files.size()==1)
    return files[0];

  //black magic, should break the code if envoked (why try to access memory when its empty anyway?)
  if(files.size()==0)
    return *(File*)nullptr;


  //make sure we dont go over the limit
  return files[i%(files.size()-1)];
}

long Memory::getUsage(){
  return usage;
}


long Memory::getFree(){
  return capacity-usage;
}

bool Memory::isNotEmpty(){
  return files.size()!=0;
}
