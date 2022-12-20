/*
  Daren Kostov
  a class that stores other folders or files

  perhaps I should make the folder store folder pointers and not the whole folders
  since im wasting memory storing duplicte folders however parent folders they have

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
  
  //Folder with a Path
  Folder(Path);

  //set the folder to another folder
  Folder& operator=(Folder);
  
  //gets the name of the folder
  Text name();
  
  //gets when the folder was last modified
  std::time_t getDate();
  
  //deletes a File with name, returns false if unsuccessful
  bool deleteFile(Text);
  bool deleteFile(const char*);
  
  //adds a File, deletes false if unsuccessful
  bool addFile(File);
  
  //deletes a Folder with name, uses recursion, returns false if unsuccessful
  bool deleteFolder(Text);
  bool deleteFolder(const char*);
  
  //adds a Folder, deletes false if unsuccessful
  bool addFolder(Folder);
  
  //returns all files in this Folder, a copy
  std::vector<File> allFiles();
  
  //returns all folders in this Folder, a copy
  std::vector<Folder> allFolders();
  
  
  //returns all file adresses in this Folder and its children
  std::vector<File*> allFilesAdr();
  
  //returns all folder adresses in this Folder and its children
  std::vector<Folder*> allFoldersAdr();
  
  //return all files/folder in Text form
  Text allItems();
  
  //returns how mush memory the folder uses
  long usage();
  
  //location of folder
  Path path;

  private:
  std::vector<File> files;
  std::vector<Folder> folders;
  void updatePaths();
  std::time_t date;
  
};