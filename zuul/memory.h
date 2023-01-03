/*
  Daren Kostov
  a class that stores memory
  
  notice:
    this memory uses bytes and NOT bits


*/
#ifndef q
#define q
#include "./text.h"
#include "./path.h"
#include "./file.h"
#endif

#include <vector>

class Memory{
  public:
    //memory of 1 KB
    Memory();
  
    //memory of specified amount
    Memory(long);
    
    //adds an item to this Memory, returns true for success, false for failure
    bool addFile(File);
  
    //removes an item from this Memory via an id (index), returns true for success, false for failure
    bool removeFile(int);
  
    //gives you Text of all files/folder
    Text AllItems();
    
    //gets a File via its id (index)
    File getFile(int);
    
    //gives you how much of the memory is used
    unsigned long getUsage();
    
    //gives you how much of the memory isnt used | I know the name isnt really gramatically correct
    unsigned long getFree();

    //returns weather there is anything in the memory
    bool isNotEmpty();

  
  private:
    std::vector<File> files;
    //how much bytes does the memory store, max is 16384 PB
    // long long unsigned capacity; 
  
    //how much bytes does the memory store, max is 4 GB
    long unsigned capacity;

    //how mush of the memory is used
    long usage;
  
};
