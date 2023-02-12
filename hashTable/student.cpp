#include "student.h"
#include <cmath>


Student::Student(Text FirstName, Text LastName, int Id, double Gpa){
  firstName=FirstName;
  lastName=LastName;
  id=Id;
  gpa=Gpa;
}

Text Student::getName(){
  return firstName+" "+lastName;
}

int Student::getId(){
  return id;
}

double Student::getGpa(){
  return floor(gpa*100)/100;
}


