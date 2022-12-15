#include <iostream>
#include <cstring>
#include "./text.h"



//==CONSTRUCTOR==\\

//empty Text
Text::Text(){
  //very important to define the pointer! 
  text=new char[0];
  length=0;

  id=rand();
  
  
}

//Text from a char 
Text::Text(char initText){
  length=1;
  text=new char[2];
  text[0]=initText;    
  text[0]='\0';    

  id=rand();
  
}

//Text from char array
Text::Text(char* initText){
  length=strlen(initText);
  text=new char[length+1];    
  strcpy(text, initText);

  id=rand();
  
}

//Text from Text
//gotta have a custom copy constructor because we are dealing with char pointers
Text::Text(const Text &initText){
  length=initText.len();
  text= new char[length+1];
  strcpy(text, initText.getCharArr());
  id=rand();
}

Text::~Text(){
  //free the memory so no memory leaks happen  
  delete[] text;
  
}


//== EQUALS OPERATOR==\\


//set text from a char
void Text::operator=(char setTo){
  //set the size of the new text
  length=1; 
  
  
  delete [] text;

  //create memory for our new text
  text=new char[2];
  text[0]=setTo;
  text[1]='\0';
}


//set text from char array
void Text::operator=(char* setTo){
  //set the size of the new text
  length=strlen(setTo); 
  
  
  delete [] text;

  //create memory for our new text
  text=new char[length+1];
  strcpy(text, setTo);
}

//set text from another Text
void Text::operator=(Text setTo){
  //use the + operator for char*
  *this=setTo.getCharArr(); 
}

//==PLUS OPERATOR==\\


Text Text::operator+(char input){

  //the length of the output text
  int outputLength=1+length;
  
  char* outputCharArr= new char[outputLength+1];
  
  //copy text into it first because its before the + operator
  strcpy(outputCharArr, text);
  
  //copy the char after the text
  outputCharArr[outputLength-1]=input;
  //dont forget about the \0 char
  outputCharArr[outputLength]='\0';
  
  //create the output  
  Text output(outputCharArr);
  
  
  return output;
  
}

Text Text::operator+(char* input){

  //the length of the output text
  int outputLength=strlen(input)+length;
  
  char* outputCharArr= new char[outputLength+1];
  
  //copy text into it first because its before the + operator
  strcpy(outputCharArr, text);
  
  //copy input after the text
  for(int i=length; i<outputLength; i++)
    outputCharArr[i]=input[i-length]; 
  
  //dont forget about the \0 char
  outputCharArr[outputLength]='\0';
  
  //create the output  
  Text output(outputCharArr);
  
  
  return output;
  
}


Text Text::operator+(Text input){
  // make an output Text from out text
  Text output(getCharArr()); 

  //use the + operator for char*
  output=output+input.getCharArr();

  // use the += operator for Text that uses the operator + for Text, that uses the += operator for Text...
  // output+=text;
  
  return output;
  
}

//==PLUS EQUALS OPERATOR==\\

Text Text::operator+=(char input){
  
  //use the = for Text
  //use the + operator for char
  *this=*this+input;
  
  //output
  Text output(*this);
  return output;
  
}
Text Text::operator+=(char* input){
  
  //use the = for Text
  //use the + operator for char array
  *this=*this+input;
  
  //output
  Text output(*this);
  return output;
  
}

Text Text::operator+=(Text input){
  
  //use the = for Text
  //use the + operator for Text
  *this=*this+input;
  
  //output
  Text output(*this);
  return output;
  
}

//==EQUALS EQUALS OPERATOR==\\

bool Text::operator==(char input){
  if(text[0]==input && text[1]=='\0')
    return true;
  return false;
}

bool Text::operator==(char* input){
  if(0==strcmp(text, input))
    return true;
  return false;
}

bool Text::operator==(Text input){
  //use the == operator for char*
  if(input==text)
    return true;
  return false;
}





char Text::operator[](int i) const{
  return text[i%length];
}

int Text::len() const{
  return length;
}

char* Text::val() const{
  return text;
}

Text Text::getText() const{
  Text copy;
  copy=*this;
  return copy;
}

int Text::getId() const{
  return id;
}

//alias functions

char Text::charAt(int i) const{
  // return (*this)[i];
  return text[i%length];
}
char Text::getCharAt(int i) const{
  return charAt(i);
}

int Text::getLength() const{
  return len();
}

char* Text::getCharArr() const{
  return val();
}

char* Text::charArr() const{
  return val();
}


