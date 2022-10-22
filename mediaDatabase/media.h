class Media{
   public:
      Media(char title[80], int);
      int getDate();
      char* getTitle();
      virtual void printAll();
      
   protected:
      char title[80];
      int date;
};




