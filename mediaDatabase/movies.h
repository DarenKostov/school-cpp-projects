#include <iostream>
#include "./media.h"

using namespace std;

class Movie : public Media{
   public:
      Movie();
      char director[80];
      char duration[80];
      char rating[80]; 
};




