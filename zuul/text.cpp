#include <iostream>
#include <cstring>
#include <cmath>
#include "./text.h"



//==CONSTRUCTOR==\\

//empty Text
Text::Text(){
  //very important to define the pointer! 
  text=new char[1];
  text[0]='\0';
  length=0;

  id=rand();
  
  
}

//Text from a char 
Text::Text(char initText){
  length=1;
  text=new char[2];
  text[0]=initText;    
  text[1]='\0';    

  id=rand();
  
}

//Text from char array
Text::Text(const char* initText){
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
  strcpy(text, initText.val());
  id=rand();
}

Text::~Text(){
  //free the memory so no memory leaks happen  
  delete[] text;
  
}


//Text from int
Text::Text(int initInt){

  //might not be the most efficient formula
  length=floor(log10(std::max(1,initInt)))+1;
  
  text=new char[length+1];

  for(int i=0; i<length; i++){
    text[(length-i)-1]=initInt%10+'0';
    initInt/=10;
  }

  text[length]='\0';

  id=rand();
  
}

//Text from long
Text::Text(long initInt){

  //might not be the most efficient formula
  length=floor(log10(std::max((long)1,initInt)))+1;
  
  text=new char[length+1];

  for(int i=0; i<length; i++){
    text[(length-i)-1]=initInt%10+'0';
    initInt/=10;
  }

  text[length]='\0';

  id=rand();
  
}

//== EQUALS OPERATOR==\\


//set text from a char
Text& Text::operator=(char setTo){
  //set the size of the new text
  length=1; 
  
  
  delete [] text;

  //create memory for our new text
  text=new char[2];

  text[0]=setTo;
  text[1]='\0';

  return *this;

}


//set text from char array
Text& Text::operator=(const char* setTo){
  //set the size of the new text
  length=strlen(setTo); 
  
  
  delete [] text;

  //create memory for our new text
  text=new char[length+1];
  strcpy(text, setTo);
  
  return *this;
}

//set text from another Text
Text& Text::operator=(Text setTo){
  //use the = operator for char*
  *this=setTo.val(); 
  
  return *this;
}

//set text from int
Text& Text::operator=(int setTo){
  //use the = operator for Text
  *this=Text(setTo); 
  return *this;
}
//set text from long
Text& Text::operator=(long setTo){
  //use the = operator for Text
  *this=Text(setTo); 
  return *this;
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

Text Text::operator+(const char* input){

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
  // make an output Text from our text
  Text output(text); 

  //use the + operator for char*
  output=output+input.val();

  // use the += operator for Text that uses the operator + for Text, that uses the += operator for Text...
  // output+=text;
  
  return output;
  
}

Text Text::operator+(int input){
  // make an output Text from our text
  Text output(text); 

  //use the + operator for Text
  output=output+Text(input);

  return output;
  
}
Text Text::operator+(long input){
  // make an output Text from our text
  Text output(text); 

  //use the + operator for Text
  output=output+Text(input);

  return output;
  
}

//==PLUS EQUALS OPERATOR==\\

Text& Text::operator+=(char input){
  
  //use the = for Text
  //use the + operator for char
  *this=*this+input;
  
  return *this;
  
}
Text& Text::operator+=(const char* input){
  
  //use the = for Text
  //use the + operator for char array
  *this=*this+input;
  
  return *this;
}

Text& Text::operator+=(Text input){
  
  //use the = for Text
  //use the + operator for Text
  *this=*this+input;
  
  return *this;
}

Text& Text::operator+=(int input){
  
  //use the = for Text
  //use the + operator for int
  *this=*this+input;
  
  return *this;
}
Text& Text::operator+=(long input){
  
  //use the = for Text
  //use the + operator for int
  *this=*this+input;
  
  return *this;
}


//==EQUALS EQUALS OPERATOR==\\

bool Text::operator==(char input){
  if(text[0]==input && text[1]=='\0')
    return true;
  return false;
}

bool Text::operator==(const char* input){
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



//function getters

char& Text::operator[](int i) const{
  if(i>=length || i<0)
    return text[length];

  return text[i%length];
}

int Text::len() const{
  return length;
}

char* Text::val() const{
  return text;
}
Text Text::getText() const{
  return Text(*this);
}

int Text::getId() const{
  return id;
}

//alias functions

char& Text::charAt(int i) const{
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


//casting


Text::operator char*(){
  return this->val();
}

Text::operator const char*(){
  return this->val();
}

Text::operator char(){
  return (*this)[0];
}





//reverse operators


std::ostream &operator <<(std::ostream &stream, Text right){
    stream << right.val();
    return stream;
}
Text operator+(const char* left, Text right){
  //use char* constructor and Text+Text concatenation
  return Text(left)+right;
} 
Text operator+(char left, Text right){
  //use char constructor and Text+Text concatenation
  return Text(left)+right;
}

Text operator+(int left, Text right){
  //use int constructor and Text+Text concatenation
  return Text(left)+right;
}
Text operator+(long left, Text right){
  //use int constructor and Text+Text concatenation
  return Text(left)+right;
}


//reverse operators
// /*
// char*& Text::operator=(char*& left, Text& right){
//   strcpy(left, right.val());
//   return left;
// }
// */



