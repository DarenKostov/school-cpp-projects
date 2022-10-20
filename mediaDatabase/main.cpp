/*

   Daren Kostov
   Classes
   10/13/2022
*/
#include <iostream>
#include <vector>
#include "./movies.h"
//#include "./music.h"
//#include "./videoGames.h"

using namespace std;

void addMedia(vector<Media>* media);
void printMedia(vector<Media> media);


int main (){
   
   vector<Media> DataBase;
   vector<Media> *DataBasePtr=&DataBase;
   
   
   
   
   
   
 while(true){
   char input[20];
      cin >> input;
         
      if(input[0]=='A')
         if(input[1]=='D')
             if(input[2]=='D'){
            addMedia(DataBasePtr);
               cout << "adding\n";
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


void addMedia(vector<Media>* media){

   char title[80];
   int date;
   cout << "Title: ";
   cin >> title;
   cout << "\nDate: ";
   cin >> date;
   
   media->push_back(Media(title, date));
   cout << "added\n";
   

}

void printMedia(vector<Media> media){
   for(std::vector<Media>::iterator i=media.begin(); i!=media.end(); i++){
      cout << "=============================\n";
      cout << "Date: " << i->getDate() << endl;
   }
}

