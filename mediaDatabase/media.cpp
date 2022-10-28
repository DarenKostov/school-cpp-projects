#include <iostream>
#include <cstring>
#include "./media.h"

using namespace std;

Media::Media(char Title[80], int Date){
  strcpy(title, Title);  
  date=Date;
  id=rand();
  
};
//returns the date
int Media::getDate(){
return date;
}

//returns the title
char* Media::getTitle(){
  return title;
}
//prints all info about the media
void Media::printAll(){
cout << "Media: [Title: " << title << "; Year: " << date << "]\n";
}
//returns the uniqe id
int Media::getID(){
  return id;
}
