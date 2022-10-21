class Media{
   public:
      Media(char title[80], int date);
      int getDate();
      char getTitleChar(int i);
      void printAll();
      
   protected:
      char title[80];
      int date;
};




