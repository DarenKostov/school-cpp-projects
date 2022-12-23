/*
  Daren Kostov
  this file stores variables and functions that don't really belong anywgere but are use

*/

#ifndef q
#define q
#include "./text.h"
#endif



//=message colors

//white (not default) fg
const Text Info="\033[97m";
//yellow fg
const Text Warning="\033[33m";
//red fg
const Text Error="\033[31m";
//magenta fg
const Text UnexpectedIO="\033[35m";


//light blue fg
const Text folderColor="\033[94m";
//white fg
const Text fileColor="\033[97m";


//types chars one by one
void slowtalk(bool on, Text in, Text format);
void slowtalk(bool on, Text in, Text format, int speed);
void fasttalk(bool on, Text in);


//function names might and most likely will be confused with their respective colors

//prints an info
void info(bool on, Text in);
//prints a warning
void warning(bool on, Text in);
//prints an error
void error(bool on, Text in);
//prints an unexpected input/output, cant name function "unexpected"
void unexpectedIO(bool on, Text in);


// const long printSpeed=10000;
//the global speed of all custom slep commands
const long printSpeed=10000;

//SLEeP, shorter than usleep, uses less 0's
void slep();
//slep but you can specify delay
void slep(int);

//Unconfortable SLEeP, like when sleeping on an airplane, you wake up, you sleep again, etc at random
void uSlep();

//generates random Text with certain size
Text randomText(int);
//like randomText but limited to only numbers
Text randomText(int);



