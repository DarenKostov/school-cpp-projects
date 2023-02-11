/*
  Daren Kostov
  SCR- Simple Csv Reader

  Licenced  under GPLv3
*/






#include "scr.h"
// #include <iostream>
using namespace std;

SCR::SCR(Text path){
  // file.open(path, ios::in);
  open(path);
}

SCR::SCR(){
  //do nothing
}


  
int SCR::open(Text path){

  
  file.open(path.val(), ios::in); 

  //get the 1st line
  Text line, word;

  
  getline(file, line);

  
  stringstream ss("test,among");

  //populate our columns
  while (getline(ss, word, ',')) {
    columns.push_back(word);
  }

  //get back at the top of the file
  file.clear();
  file.seekg(0);

  
  return 1;
  //return 0 if success, 1if failuare
  return 1-(int)(bool)file;

}

int SCR::close(){
  file.close();

  //most definitly likely not the way to do it
  return (int)(bool)file;
}


//read given an idex
int SCR::read(int column, std::vector<Text>& output){
  Text line, word;
  getline(file, line);

  //loop though every line
  while (file.good()) {

      getline(file, line);
      std::stringstream ss(line.val());
      int index=0;
    
      //loop through every value
      while (getline(ss, word, ',')) {
        if(index==column)
          output.push_back(word);

        index++;
    }
  }

  //get back at the top of the file
  file.clear();
  file.seekg(0);

  return 0;

}

int SCR::read(Text column, std::vector<Text>& output){
  int columnInt=-1;

  int i=0;
  for(auto ptr=columns.begin(); ptr!=columns.end(); ptr++){
    i++;
    if(*ptr==column){
      columnInt=i;
      break;
    }
    
  }

return read(columnInt, output);

  
}



