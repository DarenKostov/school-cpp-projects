#include <iostream>
#include "./videoGames.h"

using namespace std;

VideoGame::VideoGame(char Title[80], int Date, char Rating[80], char Publisher[80]):Media(Title, Date){
  for(int i=0; i<80; i++){
    rating[i]=Rating[i];
    publisher[i]=Publisher[i];
  }
  
  
};
void VideoGame::printAll(){
  cout << "VideoGame: [Title: " << title << "; Year: " << date << "; Artist: "
       << rating << "; Publisher: " << publisher << "]\n";
}



