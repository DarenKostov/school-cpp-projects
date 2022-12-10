#include <iostream>
#include <cstring>
#include "./text.h"





//empty Text
Text::Text(){
  //very important to difine the pointer! 
  text=new char[0];
  length=0;
  std::cout << "Creating Text object.\n";
}

//Text from char array
Text::Text(char* initText){
  length=strlen(initText);
  text=new char[length+1];    
  strcpy(text, initText);
  std::cout << "Creating Text object\n";
}

Text::~Text(){
  // std::cout << typeid(text).name() << '\n';
  std::cout << strlen(text) << '\n';
  std::cout << (text) << '\n';
  
  delete[] text;
  std::cout << "Destroying Text Class\n";
}

//gives errors, TODO: fix
// //Text from Text
// //gotta have a custom copy constructor because we are dealing with char pointers
// Text::Text(Text &initText){
//   length=initText.len();
//   strcpy(text, initText.getCharArr());
// }



//set text from char array
void Text::operator=(char* setTo){
  std::cout << "set with char*\n";
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
  // //use the += operator for Text
  // output+=text;
  
  return output;
  
}

void Text::operator+=(char* input){
  
  //use the = for Text
  //use the + operator for char
  *this=*this+input;
  
}

void Text::operator+=(Text input){
  
  //use the = for Text
  //use the + operator for Text
  *this=*this+input;
  
}


int Text::len(){
  return length;
}

char* Text::getCharArr(){
  return text;
}

Text Text::getText(){
  Text copy;
  copy=*this;
  return copy;
}

char Text::charAt(int i){
  return text[i];
}
char Text::getCharAt(int i){
  return charAt(i);
}





