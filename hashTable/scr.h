/*
  Daren Kostov
  SCR- Simple Csv Reader

  You are free to use this as long as your usage doesnt violate the GPLv3 licence

  The code should be hosted on
  https://github.com/DarenKostov/DAK-cpp-utils

  modified by Daren Kostov (me) to use Text instead of std::string

*/

#include "text.h"
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

#ifndef SIMPLE_CSV_READER
#define SIMPLE_CSV_READER


class SCR{

  private:
    //thats where we store all of the colmns
    std::vector<Text> columns;

    //the file stream
    std::fstream file;

  public:
    //constructor, takes the path to the file as an argument
    SCR(Text);

    //constructor, empty
    SCR();
    
    //opens a file, takes the path of the file as an argument, returns 0 if sucess
    int open(Text);

    //closes the file that is open, returns 0 if success
    int close();

    //reads the column at the given index and outputs the contents to a vector
    int read(int column, std::vector<Text>& output);

    //reads the column given and outputs the contents to a vector
    int read(Text column, std::vector<Text>& output);




    
};

#endif



