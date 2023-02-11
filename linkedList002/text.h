/*
  Daren Kostov
  Text- string but made by me  
  
  code should be hosted on:
  https://github.com/DarenKostov/DAK-cpp-utils

  
  You are free to use it for any purpose, as long as it doesn't violate the GPLv3 licence.
  (you might want to use this if you don't have access to std::string)

  resources used:
  https://www.geeksforgeeks.org/operator-overloading-c/
  https://stackoverflow.com/questions/56387509/this-argument-to-member-function-select-has-type-const-selectparam-but-fu
  https://stackoverflow.com/questions/39808976/operator-overloading-for-primitive-types-in-c
  https://stackoverflow.com/questions/72142269/how-to-interpret-the-explicit-cast-operator
  https://www.geeksforgeeks.org/getline-string-c/

  http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
  https://www.geeksforgeeks.org/difference-between-const-int-const-int-const-and-int-const/
  https://stackoverflow.com/questions/25274312/is-it-a-good-practice-to-define-c-functions-inside-header-files


*/



//watch out for the capitalization of "text" in the comments
//"Text" refers to the class, "text" refers to where the the char array is stored

#include <iostream>


#ifndef TEXT
#define TEXT


class Text{
  public:
    //whenever I say char array I mean char pointer pointing to a char array
  
    //=constructors
  
    // make an empty Text
    Text(); 
  
    // make a Text from a single char
    Text(char); 
  
    // make a Text from a char array
    Text(const char*);
  
    // make a Text from a Text
    Text(const Text&);
  
    // make a Text from an int, long
    Text(int);   
    Text(long);   
  
    // deconstructor, makes sure no memory leaks occur
    ~Text();
  
    //=plus operator
  
    // Concatenates the text and a char into a Text
    Text operator+(char); 
  
    // Concatenates the text and char array into a Text
    Text operator+(const char*); 
  
    // Concatenates the 2 texts into a Text
    Text operator+(Text);     
  
    // Concatenates the text and an int, long into a Text
    Text operator+(int);     
    Text operator+(long);     
  
    //=equals operator
  
    // sets our text to the data in a char
    Text& operator=(char);
  
    // sets our text to the data in a char array
    Text& operator=(const char*);
    
    // sets our text to the data in the Text input
    Text& operator=(Text);
      
    // sets our text to an int, long
    Text& operator=(int);
    Text& operator=(long);

    //=plus equals operator
  
    // Concatenates the char given to this text, returns the result
    Text& operator+=(char);
  
    // Concatenates the char array given to this text, returns the result
    Text& operator+=(const char*); 
  
    // Concatenates the text given to this text, returns the result
    Text& operator+=(Text);
   
    // Concatenates the int, long given to this text, returns the result
    Text& operator+=(int);     
    Text& operator+=(long);     
  
    //=equals equals operator
  
    //returns weather the text is equal to a char
    bool operator==(char);
  
    //returns weather the text is equal to a char array
    bool operator==(const char*); 
  
    //returns weather the text is equal to a text in a Text
    bool operator==(Text); 

    //=getters and setters
  
    //returns the character at that index; reference
    char& operator[](int) const; 
  
    //returns the length of this text
    int len()const; 

    //returns the text in the form of a char array
    char* val()const; 
  
    //returns a copy Text of the class itself
    Text getText()const; 
  
    //returns the id of the Text, purely for debugging purposes
    int getId()const; 
   
    //=alias functions
  
    //returns the character at this index; reference
    char& charAt(int)const; 
  
    //returns the character at this index
    char getCharAt(int)const; 
  
    //returns the length of this text
    int getLength()const; 
  
    //returns the text in the form of a char array
    char* getCharArr()const; 
  
    //returns the text in the form of a char array
    char* charArr()const; 
    
  
  //=casts
  
  //cast it to a char array, essentially the same as ".val()"
  explicit operator char*(); 
  
  //cast it to a const char array, essentially the same as ".val()"... but a const
  explicit operator const char*(); 
  
  //cast it to a single character, if the length is more than 1 itll cast the 1st character, essentally the same as "[0]" BUT you make a copy here
  explicit operator char(); 
  

  bool operator<(Text a)const{return true;};     
  
  private:
  
    //the char array
    char* text; 
  
    //the length of the char array
    int length;
  
    //the id of this Text, purely for debugging purposes
    int id;     
    
};


//overload functions usualy used with string or char* to work with Text

//makes Text automatically work with cout
std::ostream& operator<<(std::ostream&, Text);

//makes Text automatically work with cin
std::istream& operator>>(std::istream&, Text&);

//makes Text work with getline, by default it uses std::string
std::istream& getline (std::istream&, Text&);
std::istream& getline (std::istream&, Text&, char);

//working in reverse, concatenating, setting, etc other things with Text

//makes char*+Text possible, returns Text
Text operator+(const char*, Text);

//makes char+Text possible, returns Text
Text operator+(char, Text);

//makes int,long+Text possible, returns Text
Text operator+(int, Text);
Text operator+(long, Text);

#endif


