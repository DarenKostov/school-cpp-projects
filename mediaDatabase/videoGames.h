/*
Stores info about a video game media


printAll prints all of the info about the media type
*/




#include <iostream>

#ifndef MEDIA
#define MEDIA
#include "./media.h"
#endif
using namespace std;

class VideoGame : public Media{
   public:
      VideoGame(char title[80], int date, char rating[80], char publisher[80]);
      virtual void printAll();

   private:
      char rating[80];
      char publisher[80]; 
};




