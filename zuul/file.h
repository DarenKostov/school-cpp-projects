/*

  Daren Kostov
  A file class that stores a file's name, path, and contents 


  get path:
  file1.path

  get id:
  file1.id

  get contents:
  file1.cont()

  get name:
  file1.name()

  get the date accessed:
  file.getDate()


*/

#ifndef q
#define q
#include "./text.h"
#include "./path.h"
#endif


class File{
  public:
    File(); //makes a file nowhere with nothing inside it
    File(Path, Text); //makes a file with all of its information; Path
    File(int, Text); //makes a file with all of its information; ID
    File(Text); //makes a file without path 
    File(Path); //makes an empty file at Path X
    File(int); //makes an empty file at ID X
    void operator=(File); //sets the contents of the File to another File
    Text name(); //gets the name of the file
    long getDate(); //gets the last date modified
    Text& cont(); //gives full access to the contents of the file
  
  
  
    //the path, should be fully accesible, we dont track it being changed and its class manages itself
    Path path; //location of the file
    int id; //location of file  
  
    private:
    Text contents; //what the file stores. apples? pears? how many? is that a grocery list?
    long date; //when was the last time the file was accessed (includes modifications)
  
  /*
    name() might get discontinued due to:
    file1.getPath().name();
    
    (the name is already included in the path)
  */
  
  
  /*
    note:
      want to get the path of the file in Text form? do:
      file1.path.wholeT();
    
      how about char*? do:
      file1.path.wholeT().val();
      
      want to change the path of the file from char*? do:
      file1.path=Path(Text(char1))
      
      want to change the contents? its a Text, read the Text class code, ex.:
      file1.cont()=char1
      file1.cont()+=char1
      file2.cont()=(text1+=(file1.cont()+char1))
  
      for further questions read the code for Path and Text at path.* and text.*
  
  */
};

