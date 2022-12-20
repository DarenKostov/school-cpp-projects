/*
  Daren Kostov
  a simple class that stores a path to a file/folder in the system

  please use the entire path from root, not "path/to/file", but "/path/to/file"

*/

#include <vector>

#ifndef q
#define q
#include "./text.h"
#endif


class Path{
  
  public:
  Path();
  Path(Text); //initialize from Text
  Path(std::vector<Text>); //initialize from a vecor of Texts
  
  
  void operator=(Text); //set with Text
  void operator=(Path); //set with another Path
  void operator=(std::vector<Text>); //set from a vector of Texts containing folders

  Text wholeT(); //gives you the whole path in the form of a single Text
  std::vector<Text> wholeV(); //gives you the whole path in the form of a vector of Texts
  int getDepth(); //gives you how deep the the path, ex /qw/er/ty/ has dept of 3
  Text atDepth(int); //gives you the folder/file at depth i, starting from root

  //function aliases
  Text wholeText(); //gives you the whole path in the form of a Text
  std::vector<Text> wholeVector(); //gives you the whole path in the form of vector
  int length(); //gives you how deep the the path, ex /qw/er/ty/ has dept of 3
  int len(); //gives you how deep the the path, ex /qw/er/ty/ has dept of 3
  Text atLength(int); //gives you the folder/file at length i, starting from root
  Text atLen(int); //gives you the folder/file at length i, starting from root
  Text atIndex(int); //gives you the folder/file at index i, starting from root
  Text name(); //gives you the name of the file (basically does "path1.atIndex(path1.len()-1)")
  
  //changes the path, without the name
  void changeParentOnly(Path);
  void changeParentOnly(Text);
  void changeParentOnly(std::vector<Text>);
  
  //gives you the parent directory path in Text form
  Text getParent();
  
  
  //map needs this operator
  bool operator<(Path in) const;
  
  private:
  void reCalculateDepth(); //recalculates the depth of the Path
  
  std::vector<Text> path; //where we store the path
  int depth; //how many layers does the path have ex. /gh/hj/jk/kl has 4
  
  /*
    note:
    want to initialize from a char*? do:
    char char1[100]="qwerty";
    Path a(Text(char1));
  
  */

  
};
