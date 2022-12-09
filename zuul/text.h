/*
  Daren Kostov
  Text- string but made by me  
  
  resources used:
  https://www.geeksforgeeks.org/operator-overloading-c/
  
*/

class Text{
  public:
    Text operator+(Text); //Concatenates the 2 texts
    Text operator=(char*); //sets the the Text to the data in char array
    //I wont be doing stuff like a=b+="c" so no need to return anything
    void operator+=(Text); // Concatenates the text given to this text
    void operator+=(char*); // Concatenates the char array given to this text 
    char charAt(int); //returns the character at this index
    //cant have the name as "length"
    int len(); //returns the length of this text
    char* getCharArr(); //returns the text in the form of a char array
    Text getText(); //returns the text class itself

  private:
    char* text;
    int length;
    
    
};