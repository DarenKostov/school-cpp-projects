/*

   Daren Kostov
   Classes
   10/26/2022

resources used:

https://stackoverflow.com/questions/5660527/how-do-i-return-a-char-array-from-a-function
https://stackoverflow.com/questions/3473438/return-array-in-a-function
https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
https://stackoverflow.com/questions/19342155/how-to-store-characters-into-a-char-pointer-using-the-strcpy-function
https://cplusplus.com/reference/cstring/strstr/



*/
#include <iostream>
#include <vector>
#include <cstring>
#include "./movies.h"
#include "./music.h"
#include "./videoGames.h"

using namespace std;

void addMedia(vector<Media*> &media);
void printMedia(vector<Media*> media);

void delMedia(vector<Media*> media, vector<Media*> &orig);
vector <Media*> searchMedia(vector<Media*> media);


void cignorre();

int main (){
   
   vector<Media*> DataBase;
   
   cout << " PRINT- prints everything in the database\n ADD- adds a media\n SEARCH- searches for media\n REMOVE- removes a media\n";
   
   
   
   
 while(true){
   char input[20];
      cin >> input;
         
      if(input[0]=='A')
         if(input[1]=='D')
             if(input[2]=='D')
               addMedia(DataBase);
      
      
      
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
                        printMedia(searchMedia(DataBase));
                        
                              
      if(input[0]=='R')
         if(input[1]=='E')
            if(input[2]=='M')
               if(input[3]=='O')
                  if(input[4]=='V')
                     if(input[5]=='E')
                        delMedia(searchMedia(DataBase), DataBase);
                     
                              
      if(input[0]=='Q')
         if(input[1]=='U')
            if(input[2]=='I')
               if(input[3]=='T')
                  return 0;
                                 
                              
         
   }
return 0;

}

//adds a media to the given vector
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
   
   
   //select and add media
   while(true){
      cout << "\nMedia: ";
      cin >> type;
      cignorre();
      if(type[0]=='v'){
         
         char rating[80];
         char publisher[80];
         cout << "\nRating: ";
         cin.get(rating, 80);
         cignorre();
         cout << "\nPublisher: ";
         cin.get(publisher, 80);
         media.push_back(new VideoGame(title, date, rating, publisher));
         
         break;
      }else if(type[0]=='m'){
         if(type[1]=='u'){       
         
            char artist[80];
            char duration[80];
            char publisher[80];
            cout << "\nArtist: ";
            cin.get(artist, 80);
            cignorre();
            cout << "\nDuration: ";
            cin.get(duration, 80);
            cignorre();
            cout << "\nPublisher: ";
            cin.get(publisher, 80);
            media.push_back(new Music(title, date, artist, duration, publisher));
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
            cout << "\nRating: ";
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

//prints the media stats in the given media vector
void printMedia(vector<Media*> media){
   for(std::vector<Media*>::iterator i=media.begin(); i!=media.end(); i++){
      
      (*i)->printAll();
   
   }
}


//returns a vector with the medias coresponding to the date or title
vector <Media*> searchMedia(vector<Media*> media){
   
   
   vector <Media*> output;
   
   while(true){
   char type[10];
   cout << "\ndate/title: ";
   cin >> type;

   if(type[0]=='D' || type[0]=='d'){
         int date;
         cout << "\nDate: ";
         cin >> date;      
         for(std::vector<Media*>::iterator i=media.begin(); i!=media.end(); i++){
            if((*i)->getDate()==date){
               output.push_back(*i);
            }   
         }   
         break;
      }else if(type[0]=='T' || type[0]=='t'){
         char title[80];
         cout << "\nTitle: ";
         cin >> title;
      
         for(std::vector<Media*>::iterator i=media.begin(); i!=media.end(); i++){
            char* compr= strstr((*i)->getTitle(), title);      
            if(compr!=NULL){
               output.push_back(*i);
            }   
         }
         break;
      }
      cout << "Type 'date' or 'title'\n";
   }
   return output;
   
}


//deletes medias in the given media vector
void delMedia(vector<Media*> media, vector<Media*> &orig){
   cout << "Medias for deletion:\n";
   printMedia(media);
   
   char confirm;
   cout << "Are you sure you want to delete these medias? [y/n]";
   cin >> confirm;
   switch (confirm){
      case 'y':
      case 'Y':
         while(media.size()>0){
            for(std::vector<Media*>::iterator i=orig.begin(); i!=orig.end(); i++){
               if((*media.begin())->getID()==(*i)->getID()){
                  delete *i;
                  orig.erase(i);
                  media.erase(media.begin());
                  break;            
               }
            }
         }
      cout << "Deleted!\n";
      return;
   }   
   cout << "Canceled\n";   
   
}

//clears and ignorres the cin
void cignorre(){
   cin.clear();
   cin.ignore(99999,'\n');
}
