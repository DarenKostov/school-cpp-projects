/*
  Daren Kostov
  Student Database- a hash table that manages students gpa, id, etc

*/


#include "student.h"
#include "node.h"

#ifndef DATABASE
#define DATABASE


class StudentDatabase{
  public:

    //default database, table size is 100
    StudentDatabase();
  
    //constructor that takes the size of the table as an argument  
    StudentDatabase(int);

    //adds a student to the database | first name, last name, gpa
    void insert(Text, Text, double);

    //adds a student by a direct Student pointer. Don't use this, might cause duplicates or fragmentation. 
    void insert(Student*);

    //gives a student based on their id. No access to change it, just read/view it.
    Student getStudent(int);
    Student locate(int);
    Student find(int);
    
    //removes a student from the database
    void remove(int);

  private:

    //hashes an id  
    int hash(int);

    //recalculates the best spot for a new student
    void recalculateBestNewSpot();

    //doubles the tables and rehashes them
    int ExpandAndRehash();

    //returns you the slot where a student should be, given their id
    Node<Student>* getSlot(int);

    //adds a student to a slot (I didn't design my node class very well so it doesn't completly manage it on itself)
    void addStudent(Node<Student>*, Student*);
  
    int bestSlotForANewStudent;
    int tableSize;
    int amountOfTables;

    // A linked list of arrays of linked lists that store students, a 3d array of students if you will
    Node<Node<Student>*>* slots =nullptr;//new Node<Student*>*[100];
    
};


#endif