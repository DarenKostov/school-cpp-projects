/*
  Daren Kostov
  a class that stores other folders or files


*/
#ifndef q
#define q
#include "./text.h"
#include "./path.h"
#include "./file.h"
#endif
#include <vector>
#include <ctime>

class Folder{
  public:
  //empty Folder, nowhere
  Folder();
  
  //deconstructor
  ~Folder();
  
  //Folder with a Path
  Folder(Path);

  Folder& operator=(Folder);

  //gets the name of the folder
  Text name();
  
  //gets when the folder was last modified
  std::time_t getDate();
  
  
  //=file
  
  //deletes a File with name, returns false if unsuccessful
  bool deleteFile(Text);
  bool deleteFile(const char*);
  
  //adds a File, deletes false if unsuccessful
  bool addFile(File*);
  
  //returns all files in this Folder, a copy
  std::vector<File*> allFiles();
  
  //returns all file adresses in this Folder and its children
  std::vector<File*> allChildFiles();
  
  //gives you the child Folder given its name
  File* getFile(Text);
  
  //searches for a File in any of its children given the path, recursive
  File* findFileInChildren(Path);
  
  
  //=folder
  
  //deletes a Folder with name, uses recursion, returns false if unsuccessful
  bool deleteFolder(Text);
  bool deleteFolder(const char*);
  
  //adds a Folder, deletes false if unsuccessful
  bool addFolder(Folder*);
  
  //returns all folders in this Folder, a copy
  std::vector<Folder*> allFolders();
  
  //returns all folder adresses in this Folder and its children
  std::vector<Folder*> allChildFolders();
  
  //gives you the child Folder given its name
  Folder* getFolder(Text);
  
  
  //searches for a File in any of its children given the path, recursive
  Folder* findFolderInChildren(Path);
  
  // erases everything from this folder, no questions asked
  void emptyMe();
  
  //return all files/folder in Text form
  Text allItems();
  
  //returns how mush memory the folder uses
  long usage();
  
  //location of folder
  Path path;

  private:
  std::vector<File*> files;
  std::vector<Folder*> folders;
  void updatePaths();
  std::time_t date;
  
};