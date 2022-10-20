#include <iostream>
#include <cstring>
#include "./media.h"

using namespace std;

Media::Media(char Title[80], int Date){
  strcpy(title,Title);
  date=Date;
  
};

int Media::getDate(){
return date;
}





