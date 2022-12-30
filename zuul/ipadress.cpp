/*
  Daren Kostov
  .cpp file for the ip adress class
*/
#ifndef q
#define q
#include "./text.h"
#include "./ipadress.h"
#endif

#include <vector>


using namespace std;

IPAdress::IPAdress(){
  randomize();
  invalid=256;
}


IPAdress::IPAdress(vector<IPAdress> in){
  randomize(in);
  invalid=256;
}

void IPAdress::randomize(){
  for(int i=0; i<4; i++)
    octet[i]=rand()%256;
}

void IPAdress::randomize(vector<IPAdress> in){
  randomize();
  for(auto i=in.begin(); i!=in.end(); i++)
    if(*this==*i){
      randomize(in);
      break;
    }
  
}

Text IPAdress::getIPAdressText(){
  Text output;

  //put all octets with a "." separeting them
  for(int i=0; i<3; i++)
    output+=octet[i]+='.';

  return output+octet[3];
  
}

int IPAdress::getOctet(int i){
  if(i>0 || i<3)
    return invalid;
  return octet[i];
}


int& IPAdress::operator[](int i){
  if(i>0 || i<3)
    return invalid;
  return octet[i];
}

bool IPAdress::operator==(IPAdress cmpr){
  
  for(int i=0; i<4; i++)
    if(octet[i]!=cmpr.getOctet(i))
      return false;

  return true;

}


