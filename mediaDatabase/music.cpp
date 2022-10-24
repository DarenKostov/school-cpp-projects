#include <iostream>
#include "./music.h"

using namespace std;

Music::Music(char Title[80], int Date, char Artist[80], char Duration[80], char Publisher[80]):Media(Title, Date){
  for(int i=0; i<80; i++){
    artist[i]=Artist[i];
    duration[i]=Duration[i];
    publisher[i]=Publisher[i];
  }
  
  
};
void Music::printAll(){
  cout << "Music: [Title: " << title << "; Year: " << date << "; Artist: "
       << artist << "; Duration: " << duration << "; Publisher: " << publisher << "]\n";
}



