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
  
  
  //use the = operator for vector
  *this=outputV;
}

//= PATH
void Path::operator=(Path input){
  //set with the = operator for vector
  *this=input.wholeV();
}

bool Path::operator==(Path in){
  if(wholeT()==in.wholeT())
    return true;
  return false;
}




//gets the path in Text form
Text Path::wholeT(){
  Text output;
  
  for(vector<Text>::iterator i=path.begin(); i!=path.end(); i++){
     output+="/";
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


void Path::changeParentOnly(Text in){
  Text output;
  output+=in+"/"+name();
  //use the = operator for Text
  *this=output;
}

void Path::changeParentOnly(Path in){
  Text output;
  //make into Text
  output+=in.wholeT()+"/"+name();
  //use the == operator for Path
  *this=output;
}

void Path::changeParentOnly(vector<Text> in){
  in.push_back(name());
  //use the = operator for vector
  *this=in;
}

bool Path::operator<(Path in)const {
  //i dont really care how the map orders the keys
  return true;
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

Path Path::getParent(){
  vector<Text> outputV;
  
  for(vector<Text>::iterator i=path.begin(); i!=(path.end()-1); i++){
     outputV.push_back(*i);
  }
  return Path(outputV);
}

