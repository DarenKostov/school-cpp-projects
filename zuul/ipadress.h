/*
  Daren Kostov
  a class that generates and stores an ip adress
*/
#ifndef q
#define q
#include "./text.h"
#endif

#include <vector>

class IPAdress{
  public:
    //generates a completly random ip adress
    IPAdress();

    //generates an ip adress that does not match any of the ones provided
    IPAdress(std::vector<IPAdress>);

    //gives you the ip adress in Text form
    Text getIPAdressText();

    //get the octed from left to right starting from 0
    int getOctet(int);

    //compare 2 ip adresses
    bool operator==(IPAdress);


  private:
    //stores the ip adress
    int octet[4];
};
