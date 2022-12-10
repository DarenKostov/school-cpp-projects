/*
  Daren Kostov
  Text- string but made by me  
  
  resources used:
  https://www.geeksforgeeks.org/operator-overloading-c/
  
*/



//watch out for capitalization of "text" in the comments
//"Text" refers to the class, "text" refers to where the the char array is stored

class Text{
  public:
    //whenever I say char array I mean char pointer pointing to a char array
    Text(); //make an empty Text
    Text(char*); //make a Text from a char array
    // Text(Text&); //make a Text from a Text | gives errors, TODO: fix
    // Text(Text); //make a Text from Text, from Text, from Text that is also made from Test....
    ~Text(); //deconstructor, makes sure no memory leaks occur
    Text operator+(char*); //Concatenates the text and char array into a Text
    Text operator+(Text); //Concatenates the 2 texts into a Text
    void operator=(char*); //sets our text to the data in a char array
    void operator=(Text); //sets our text to the data in the Text input
    //I wont be doing stuff like a=b+="c" so no need to return anything
    void operator+=(Text); // Concatenates the text given to this text
    void operator+=(char*); // Concatenates the char array given to this text 
    char charAt(int); //returns the character at this index
    char getCharAt(int); //returns the character at this index
    int len(); //returns the length of this text
    char* getCharArr(); //returns the text in the form of a char array
    Text getText(); //returns a copy Text of the class itself (why whould you use that, just use the class itself without the getText())
  
  //note:
  //want to concatinate 2 Texts into a char array? just do:
  //(text1+text2).getCharArr()
  
  
  private:
    char* text;
    int length;
    
    
};