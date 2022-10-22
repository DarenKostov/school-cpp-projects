#include <iostream>
#include <cstring>
#include "./media.h"

using namespace std;

Media::Media(char Title[80], int Date){
  strcpy(title, Title);  
  date=Date;
  
  
};
//returns the date
int Media::getDate(){
return date;
}

//not ideal, returns the index of a char array
char* Media::getTitle(){
  return title;
}
//prints all info about the media
void Media::printAll(){}

