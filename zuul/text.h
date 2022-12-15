/*
  Daren Kostov
  Text- string but made by me  
  
  code should be hosted on:
  https://github.com/DarenKostov/DAK-cpp-utils

  
  You are free to use it for any purpose, as long as it doesn't violate the GPL3 licence.
  (you might want to use this if you don't have access to std::string)

  resources used:
  https://www.geeksforgeeks.org/operator-overloading-c/
  https://stackoverflow.com/questions/56387509/this-argument-to-member-function-select-has-type-const-selectparam-but-fu


*/



//watch out for the capitalization of "text" in the comments
//"Text" refers to the class, "text" refers to where the the char array is stored

class Text{
  public:
    //whenever I say char array I mean char pointer pointing to a char array

    Text(); //make an empty Text
    Text(char); //make a Text from a single char
    Text(char*); //make a Text from a char array
    Text(const Text&); //make a Text from a Text
    // Text(Text); //make a Text from Text, from Text, from Text that is also made from Test....
    ~Text(); //deconstructor, makes sure no memory leaks occur
  
    Text operator+(char); //Concatenates the text and a char into a Text
    Text operator+(char*); //Concatenates the text and char array into a Text
    Text operator+(Text); //Concatenates the 2 texts into a Text
    
    void operator=(char); //sets our text to the data in a char
    void operator=(char*); //sets our text to the data in a char array
    void operator=(Text); //sets our text to the data in the Text input
    
    Text operator+=(char); // Concatenates the char given to this text, returns the result
    Text operator+=(char*); // Concatenates the char array given to this text, returns the result
    Text operator+=(Text); // Concatenates the text given to this text, returns the result
    
    bool operator==(char); //returns weather the text is equal to a char
    bool operator==(char*); //returns weather the text is equal to a char array
    bool operator==(Text); //returns weather the text is equal to a text in a Text

    //functions that dont modify anything
    char operator[](int) const; //returns the character at that index
    int len()const; //returns the length of this text
    char* val()const; //returns the text in the form of a char array
    Text getText()const; //returns a copy Text of the class itself (why whould you use that, just use the class itself without the getText())
    int getId()const; //returns the id of the Text, purely for debugging purposes
   
     //alias functions
    char charAt(int)const; //returns the character at this index
    char getCharAt(int)const; //returns the character at this index
    int getLength()const; //returns the length of this text
    char* getCharArr()const; //returns the text in the form of a char array
    char* charArr()const; //returns the text in the form of a char array
    
    /*
      note:
      Want to concatinate 2 Texts into a char array? Just do:
      (text1+text2).val()
  
      what to concatinate 2 char arrays into a char array? just do:
      (Text(char1)+char2).val()
  
    */
  
  private:
    char* text; //the char array
    int length; //the length of the char array
    int id; //the id of this Text, purely for debugging purposes
    
    
};