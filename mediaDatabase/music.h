#include <iostream>

#ifndef MEDIA
#define MEDIA
#include "./media.h"
#endif
using namespace std;

class Music : public Media{
   public:
      Music(char title[80], int date, char artist[80], char duration[80], char Publisher[80]);
      virtual void printAll();

   private:
      char artist[80];
      char duration[80];
      char publisher[80]; 
};




