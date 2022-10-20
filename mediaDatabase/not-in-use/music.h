#include <iostream>
#include "./media.h"

using namespace std;

class Music : public Media{
   public:
      Music();
   
   
   protected:
   char artist[80];
   int date;
   int type;
};




