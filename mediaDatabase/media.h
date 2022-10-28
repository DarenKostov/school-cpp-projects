/*
getDate returns the date
getTitle returns the title
printAll prints all of the info about the media type
getID returns the uniqe id the media has
*/

class Media{
   public:
      Media(char title[80], int date);
      int getDate();
      char* getTitle();
      virtual void printAll();
      int getID();
   protected:
      char title[80];
      int date;
      int id;
};




