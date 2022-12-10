#include <iostream>
#include <cstring>
#include "./text.h"





//empty Text
Text::Text(){}

//Text from char array
Text::Text(char* initText){
  length=strlen(initText);
  text=new char[length+1];    
  strcpy(text, initText);
}

//gives errors, TODO: fix
// //Text from Text
// //gotta have a custom copy constructor because we are dealing with char pointers
// Text::Text(Text &initText){
//   length=initText.len();
//   strcpy(text, initText.getCharArr());
// }


//set text from another Text
void Text::operator=(Text setTo){
  //set the size of the new text
  length=strlen(setTo.getCharArr()); 
  
  //free the memory in the text
  delete [] text;
  
  //create memory for our new text
  text=new char[length+1];
  
  strcpy(text, setTo.getCharArr());
}

//set text from char array
void Text::operator=(char* setTo){
  std::cout << "0th/n";
  //set the size of the new text
  length=strlen(setTo); 
  std::cout << "1st/n";
  
  
  //free the memory in the text IF it exists
  if(sizeof(text)!=0)
    delete [] text;
  
  std::cout << "2st/n";
  //create memory for our new text
  text=new char[length+1];
  
  strcpy(text, setTo);
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
  // make an output Text
  Text output(input.getCharArr()); 
  
  //use the + operator for char*
  output=output+text;
  
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



char* Text::getCharArr(){

  return text;

}

char Text::charAt(int i){
  std::cout << "jhjhjhjj\n";
  return text[i];
}
char Text::getCharAt(int i){
  return charAt(i);
}





