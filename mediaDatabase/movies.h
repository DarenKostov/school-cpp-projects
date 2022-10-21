#include <iostream>
#include "./media.h"

using namespace std;

class Movie : public Media{
   public:
      Movie(char title[80], int date, char director[80], char duration[80], char rating[80]);
      char director[80];
      char duration[80];
      char rating[80]; 
      void printAll();
};




