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


void File::operator=(File input){
  

}


