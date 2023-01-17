#include "text.h"




class Student{
  public:
    
    //initializes Student with a name, id, and gpa
    Student(Text, Text, int, double);
    
    //gives you the name of the student
    Text getName();

    //gives you the name of the student
    int getId();

    //gives you the gpa of the student
    double getGpa();
    
  private:
    Text firstName;
    Text lastName;
    int id;
    double gpa;
};