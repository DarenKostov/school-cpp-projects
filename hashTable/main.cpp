/*
  name sources:
  https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt&downloadcode=yes
  https://github.com/arineng/arincli/blob/master/lib/last-names.txt

*/


#include "scr.h"
#include "studentDatabase.h"
#include <cmath>




using namespace std;






void promtForRandomStudents(StudentDatabase&);




int main(){

  StudentDatabase database;

  cout << "Hello! this is the student more efficient Student Database!\n";
  cout << "Please provide us with a file containing \n";
    
  promtForRandomStudents(database);

  database.printAll();

  return 0;

}


void promtForRandomStudents(StudentDatabase& db){

  //I use char* because getline doesnt use Text ¯\_(ツ)_/¯ no real way to fix unless I make my own getline

  
  //=add random students?


  cout << "Would you like to insert random student for testing purposes?\n";
  cout << "[Y/n]:";

  {
    char* input=new char[2];
    cin.getline(input, 2);
    switch(input[0]){
      case '\0':
      case 'Y':
      case 'y':
        break;
      default:
        return;
    }
    
    delete[] input;
   } 


  //=from where to add random students?
  
  int amountOfRandomStudents=0;
  char* path=new char[50];
  SCR reader;

  
  cout << "\nPlease prove a path to an svg file containing random first and last names\n"; 
  cout << "(The 1st column should be first names, 2nd should be last names.)\n";
  cout << "[default is \"names.csv\"]:";

  cin.getline(path, 50);
  cout << "\n";
  
  if(path[0]=='\0'){
    cout << "default is chosen (\"names.csv\")\n";
    strcpy(path, "names.csv");
  }else
    cout << path <<" is chosen\n";

  
  if(reader.open(path)){
    cout << "There was a problem reading the file.....\n";  
    cout << "And I was too lazy making a while loop for this...\n";
    cout <<"...so you'll have to start over...\n";  
    cout << "Better luck reading the file next time!\n";
    exit(1);
  }

  delete[] path;

  //=load students
  vector<Text> firstNames, lastNames;

  reader.read(0, firstNames);
  reader.read(0, lastNames);
  

  //=how many random student to add?

  cout << "How may random students should be added?\n";
  cout << "[default is 25]:";

  
  {
    char* input=new char[7];
    cin.getline(input, 7); //who would put a number that has more than 7 digits

    //only if the user has inputted something
    if(!(input[0]=='\0')){
      //TODO add this to the main Text class
      for(int i=0; i<strlen(input); i++){
        amountOfRandomStudents+=(input[i]-'0')*pow(10,((strlen(input)-i)-1));
      }
    //if the user hasn't inputted anything
    }else
      amountOfRandomStudents=111;
    delete[] input;  
  }

  
  //add the students
  for(int i=0; i<amountOfRandomStudents; i++){
    db.insert(firstNames[rand()%firstNames.size()],lastNames[rand()%lastNames.size()], ((double)rand()/RAND_MAX)*4);
  }


  reader.close();

}


