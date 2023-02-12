/*
  name sources:
  https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt&downloadcode=yes
  https://github.com/arineng/arincli/blob/master/lib/last-names.txt

*/


#include "scr.h"

using namespace std;

int main(){


  SCR reader;

  if(reader.open("names.csv")==1){
    // printf("file didnt load\n");
    return 1;
  
  }

  printf("opened file\n");

  std::vector<Text> firstNames;

  reader.read(0, firstNames);

  printf("outputting data\n");

  cout << firstNames[0] << '\n';

  reader.close();

  return 0;

}




