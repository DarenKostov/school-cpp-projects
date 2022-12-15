/*
  Daren Kostov

*/
#include <vector>

#ifndef q
#define q
#include "./text.h"
#include "./path.h"
#endif

using namespace std;

Path::Path(){}

Path::Path(Text input){
  //set with the = operator for Text
  *this=input;
}

Path::Path(vector<Text> input){
  //set with the = operator for vector of Texts
  *this=input;
}

//= VECTOR
void Path::operator=(vector<Text> input){
  //empty the path
  while(path.size()!=0)
    path.erase(path.begin());
  
  //fill the path with the new path
  for(vector<Text>::iterator i=input.begin(); i!=input.end(); i++)
    path.push_back(*i);
  
  reCalculateDepth();
}

//= TEXT
void Path::operator=(Text input){
  vector<Text> outputV;
  char outputC[999][999];
  
  int j=0;
  int word=-1;
  for(int i=0; i<999; i++){
    //if the next charcter is "\" go to the next folder/file
    if(input.val()[i]=='/'){
      outputC[word][i-j]='\0';
      j=++i;
      word++;
    }  
    //add the char to the current folder/file
    outputC[word][i-j]=input.val()[i];
    
    //if its the end of the Text break out of the loop
    if(input.val()[i]=='\0'){
      break;     
    }
  }
  
  //fill the output with all of the folders/files
   for(int i=0; i<word+1; i++)
    outputV.push_back(Text(outputC[i]));
  
  
  //use the == operator for vector
  *this=outputV;
}

//= PATH
void Path::operator=(Path input){
  //set with the == operator for vector
  *this=input.wholeV();
}


//gets the path in Text form
Text Path::wholeT(){
  char slash[2]="/";
  Text output;
  
  for(vector<Text>::iterator i=path.begin(); i!=path.end(); i++){
    //the magic of using Text instead of char*
     output+=slash;
     output+=*i;
  }
  return output;
}

//get the entire vector
vector<Text> Path::wholeV(){
  return path;
}

//gets length
int Path::getDepth(){
  return depth;
}

//gets the folder/file at index i
Text Path::atDepth(int i){
  //dont go over the limit and cause a seg fault
  i%=depth;
  
  //pointer arithmetic
  return *(path.begin()+i);
}

Text Path::name(){  
  //pointer arithmetic
  return *(path.end()-1);
}
//recalculates depth based on the size of the vector
void Path::reCalculateDepth(){
  depth=path.size();
}

//aliases

Text Path::wholeText(){
  return wholeT();
}

vector<Text> Path::wholeVector(){
  return wholeV();
}

int Path::length(){
  return getDepth();
}

int Path::len(){
  return getDepth();
}

Text Path::atLength(int i){
  return atDepth(i);
}

Text Path::atLen(int i){
  return atDepth(i);
}

Text Path::atIndex(int i){
  return atDepth(i);
}



