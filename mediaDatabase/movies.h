/*
Stores info about a movie media


printAll prints all of the info about the media type
*/





#include <iostream>

#ifndef MEDIA
#define MEDIA
#include "./media.h"
#endif

using namespace std;

class Movie : public Media{
   public:
      Movie(char title[80], int date, char director[80], char duration[80], char rating[80]);
      virtual void printAll();

   private:
      char director[80];
      char duration[80];
      char rating[80]; 
};




