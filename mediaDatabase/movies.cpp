#include <iostream>
#include "./movies.h"

using namespace std;

Movie::Movie(char Title[80], int Date, char Director[80], char Duration[80], char Rating[80]):Media(Title, Date){
  for(int i=0; i<80; i++){
    director[i]=Director[i];
    duration[i]=Duration[i];
    rating[i]=Rating[i];
  }
  
  
};
void Movie::printAll(){
  cout << "Movie: [Title: " << title << "; Year: " << date << "; Director: "
       << director << "; Duration: " << duration << "; Rating: " << rating << "]\n";
}



