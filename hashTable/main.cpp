/*
  name sources:
  https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt&downloadcode=yes
  https://github.com/arineng/arincli/blob/master/lib/last-names.txt

*/


#include "scr.h"
#include "studentDatabase.h"
#include <cmath>




using namespace std;






int promtForId();
void promtForRandomStudents(StudentDatabase&);
void printHelp();
void printSingle(StudentDatabase&);
void addStudent(StudentDatabase&);
void appendStudent(StudentDatabase&);
void insertStudent(StudentDatabase&);
void deleteStudent(StudentDatabase&);
void expandAndRehash(StudentDatabase&);




// void add

int main(){

  cout << "Hello! this is the student more efficient Student Database!\n";


  cout << "How big should the student databse be?\n[default is 100]:";
  int databaseSize=0;


  {
    char* input=new char[7];
    cin.getline(input, 7); //who would put a number that has more than 7 digits

    //only if the user has inputted something
    if(input[0]!='\0'){
      //TODO add this to the main Text class
      for(int i=0; i<strlen(input); i++){
        databaseSize+=(input[i]-'0')*pow(10,((strlen(input)-i)-1));
        cout << (input[i]-'0')*pow(10,((strlen(input)-i)-1))<< "\n";
      }
    //if the user hasn't inputted anything
    }else
      databaseSize=100;
    delete[] input;  
  }
  

  
  StudentDatabase database(databaseSize);

    
  promtForRandomStudents(database);

  printHelp();


  Text input;

  while(input!="QUIT" && input[0]!='q'){
    printf("[%d/%d %d] >", database.getStudentAmount(), database.getCapacity(), database.getTables());
    
    cin >> input;
  
    if(input[0]=='a' || input=="ADD"){
      addStudent(database);
      continue;
    }    
    if((input[0]=='a' && input[1]=='p') || input=="APPEND"){
      cout << "Yet to be implemented\n";
      continue;
    }    
    if(input[0]=='i' || input=="INSERT"){
      insertStudent(database);
      continue;
    }    
    if(input[0]=='h' || input=="HELP"){
      printHelp();
      continue;
    }    
    if((input[0]=='p' && input[1]=='a') || input=="PRINTALL"){
      database.printAll();
      continue;
    }    
    if((input[0]=='p' && input[1]=='s') || input=="PRINTSORTED"){
      database.printSorted();
      continue;
    }    
    if(input[0]=='p' || input=="PRINT" || input=="PRINTSINGLE"){
      printSingle(database);
      continue;
    }    
    if(input[0]=='d' || input=="DELETE"){
      cout << "Yet to be implemented\n";
      continue;
    }    
    if(input[0]=='r' || input=="ADDRANDOM"){
      promtForRandomStudents(database);
      continue;
    }    
    if(input[0]=='e' || input=="EXPANDANDREHASH"){
      cout << "Yet to be implemented\n";
      continue;
    }    
    
    
    
  }

    


  return 0;

}

void addStudent(StudentDatabase& db){
  cin.ignore(99999,'\n');
  cin.clear();

  char* firstName=new char[100];
  char* lastName=new char[100];
  double gpa=0;

  cout << "\nAdding a new student...\n";

  cout <<"first name:";
  cin.getline(firstName, 100);
  cout <<"last name:";
  cin.getline(lastName, 100);
  cin.clear();
  cout <<"gpa:";
  cin >> gpa;
  
  db.insert(firstName, lastName, gpa);
  
  printf("Student %s %s added to the database\n", firstName, lastName);

  delete[] firstName;
  delete[] lastName;

}

void insertStudent(StudentDatabase& db){
  cin.ignore(99999,'\n');
  cin.clear();
  
  char* firstName=new char[100];
  char* lastName=new char[100];
  int id=0;
  double gpa=0;

  cout << "\nAdding a new student...\n";

  cout <<"first name:";
  cin.getline(firstName, 100);
  cout <<"last name:";
  cin.getline(lastName, 100);
  cin.clear();
  cout <<"id:";
  cin >> id;
  cout <<"gpa:";
  cin >> gpa;



  db.insert(new Student(firstName, lastName, id, gpa));
  
  printf("Student %s %s added to the database\n", firstName, lastName);

  delete[] firstName;
  delete[] lastName;


}

void printSingle(StudentDatabase& db){
  cout << "id?:";
  int id=0;
  cin >> id;
  
  Student* student=db.locate(id);

  //where student? nowhere?
  if(student==nullptr){
    cout << "\nUnable to locate student... perhaps you inoutted the wrong id?\n";
    return;
  }

  printf("\n%06d: %.2f, %s\n", student->getId(), student->getGpa(), student->getName().val());
}



void deleteStudent(StudentDatabase&){

  cout << "id?:";
  int id=0;
  cin >> id;


}

void promtForRandomStudents(StudentDatabase& db){

  //I use char* because cin.getline doesnt use Text ¯\_(ツ)_/¯ no real way to fix unless I make my own cin.getline

  
  //=add random students?


  cout << "Would you like to insert random students for testing purposes?\n";
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

  
  cout << "\nPlease provide a path to an svg file containing random first and last names\n"; 
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
  reader.read(1, lastNames);
  

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
      amountOfRandomStudents=25;
    delete[] input;  
  }

  
  //add the students
  for(int i=0; i<amountOfRandomStudents; i++){

    //aint no one failing
    double gpa=((double)rand()/RAND_MAX)*1.5+2.5;
      
    db.insert(firstNames[rand()%firstNames.size()],lastNames[rand()%lastNames.size()], gpa);
  }


  reader.close();

}


void printHelp(){
  
  cout << "Commands:\n";
  
  cout << "HELP (h): This help.\n";
  
  cout << "ADD (a): Adds a student to the database, automatic ID.\n";
  
  cout << "APPEND (ap): Adds a student to the database, at the first unused id.\n";
  
  cout << "INSERT (i): Same as ADD but you specify the ID, can cause duplicates\n";
  cout << "but that's what the computer sould do, what you tell it to.\n";
  
  cout << "PRINTALL (pa): Prints every student to the console.\n";
  
  cout << "PRINTSORTED (ps): Prints every student to the console in a sorted fashion.\n";
  
  cout << "PRINT (p)(PRINTSINGLE): Prints a single student.\n";
  
  cout << "DELETE (d): Removes a student from the database.\n";
  
  cout << "ADDRANDOM (r): ADDs random students to the database.\n";
  
  cout << "EXPANDANDREHASH (e): Force the database hashtable to double and rehash all students.\n";

  cout << "QUIT (q): Quits the program.\n";

  cout << "\n[{Students}/{Current Capacity} {Slices/Tables}] >\n";

  
}


