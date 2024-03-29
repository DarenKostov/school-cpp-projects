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

    //decosntructor, deletes everything in the database
    ~StudentDatabase();

    //adds a student to the database | first name, last name, gpa
    void insert(Text, Text, double);

    //adds a student by a direct Student pointer. Don't use this, might cause duplicates or fragmentation. 
    void insert(Student*);


    //THIS REMOVES THE STUDENT, NOT JUST THE NODE, THE STUDENT WILL BE FOREVER LOST
    void removeStudent(int);



    //gives a student based on their id.
    Student* getStudent(int);
    Student* locate(int);
    Student* find(int);

    //prints all students on the console
    void printAll();
     
    //removes a student from the database
    void remove(int);


    //=stat getters

    //gives you how many students there are in the database
    int getStudentAmount();

    //gives you how many students there could be in the database before expanding & rehashing
    int getCapacity();

    //gives you how many table there are in the database
    int getTables();

    //gives you how many slots there are in the database
    int getTableSize();


    void printSorted();


  private:

    //hashes an id  
    int hash(int);

    //recalculates the best spot for a new student
    void recalculateBestNewSpot();

    //doubles the tables and rehashes them
    void expandAndRehash();

    //returns you the slot where a student should be, given their id
    Node<Student>*& getSlot(int);


    //gives you the node where a student is stored, if the student doesn't exist it'll give you nullptr
    Node<Student>* getNodeStudent(int);


    //injects a student NODE into tha database | acts like addStudent but with a node 
    void injectStudent(Node<Student>*&, Node<Student>*);

    //adds a student to a slot (I didn't design my node class very well so it doesn't completly manage it on itself)
    void addStudent(Node<Student>*&, Student*);
  
  
  
    int bestSlotForANewStudent;
    int tableSize;
    int amountOfTables;
    int amountOfStudents;



    // A linked list of arrays of linked lists that store students, a 3d array of students if you will
    Node<Node<Student>*>* slots =nullptr;//new Node<Student*>*[100];
    
};


#endif