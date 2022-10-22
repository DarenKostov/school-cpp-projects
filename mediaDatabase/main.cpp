/*

   Daren Kostov
   Classes
   10/13/2022

resources used:

https://stackoverflow.com/questions/5660527/how-do-i-return-a-char-array-from-a-function
https://stackoverflow.com/questions/3473438/return-array-in-a-function
https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
https://stackoverflow.com/questions/19342155/how-to-store-characters-into-a-char-pointer-using-the-strcpy-function
*/
#include <iostream>
#include <vector>
#include "./movies.h"
//#include "./music.h"
//#include "./videoGames.h"

using namespace std;

void addMedia(vector<Media*> &media);
void printMedia(vector<Media*> media);
void cignorre();

int main (){
   
   vector<Media*> DataBase;
   //vector<Media> *DataBasePtr=&DataBase;
   
   
   
   
   
   
 while(true){
   char input[20];
      cin >> input;
         
      if(input[0]=='A')
         if(input[1]=='D')
             if(input[2]=='D'){
            addMedia(DataBase);
      }
      
      
      
   if(input[0]=='P')
      if(input[1]=='R')
         if(input[2]=='I')
            if(input[3]=='N')
               if(input[4]=='T')
                  printMedia(DataBase);
                  
                  
      if(input[0]=='S')
         if(input[1]=='E')
            if(input[2]=='A')
               if(input[3]=='R')
                  if(input[4]=='C')
                     if(input[5]=='H')
                        return 0;
                        
                              
      if(input[0]=='R')
         if(input[1]=='E')
            if(input[2]=='M')
               if(input[3]=='O')
                  if(input[4]=='V')
                     if(input[5]=='E')
                        return 0;
                              
                              
                              
      if(input[0]=='Q')
         if(input[1]=='U')
            if(input[2]=='I')
               if(input[3]=='T')
                  return 0;
                                 
                              
         
   }
return 0;

}


void addMedia(vector<Media*> &media){
   cignorre();

   char title[80];
   int date;
   char type[80];
   cout << "Title: ";
   cin.get(title, 80);
   cout << title << endl;
   cignorre();
   
   cout << "\nDate: ";
   cin >> date;
   
   while(!cin){
      cignorre();
      cout << date << "\nType the year. (ex 2012)\nDate: ";
      cin >> date;
   }
   
   
    
   while(true){
      cout << "\nMedia: ";
      cin >> type;
      cignorre();
      if(type[0]=='v'){
//          media->push_back(Video(title, date, title, title, title));
         break;
      }else if(type[0]=='m'){
         if(type[1]=='u'){       
         
            break;
         }else if(type[1]=='o'){
            char director[80];
            char duration[80];
            char rating[80];
            cout << "\nDirector: ";
            cin.get(director, 80);
            cignorre();
            cout << "\nDuration: ";
            cin.get(duration, 80);
            cignorre();
            cout << "\nrating: ";
            cin.get(rating, 80);
            media.push_back(new Movie(title, date, director, duration, rating));
            break;
         }
      }

      cout << "\nType a media type, there are 'video games', 'music', and 'movies'";
   }
   cignorre();
   
   cout << "added\n";
   

}

void printMedia(vector<Media*> media){
   for(std::vector<Media*>::iterator i=media.begin(); i!=media.end(); i++){
      
      (*i)->printAll();
   
   }
}
void cignorre(){
   cin.clear();
   cin.ignore(99999,'\n');
}
