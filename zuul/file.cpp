/*
  Daren Kostov
*/


#ifndef q
#define q
#include "./text.h"
#include "./path.h"
#include "./file.h"
#endif


//empty and nowhere
File::File(){};

//with path and contents
File::File(Path inPath, Text inCont){
  path=inPath;
  contents=inCont;
};

//without path
File::File(Text inCont){
  contents=inCont;
};

//empty file
File::File(Path inPath){
  path=inPath;
};


void File::operator=(File in){
  //location
  path=in.path;
  id=in.id;
  
  contents=in.cont();
  date=in.getDate();
}

// file.path.name()
Text File::name(){
  return path.name();
}

long File::getDate(){
  return date;
}

Text& File::cont(){
  return contents;
}

