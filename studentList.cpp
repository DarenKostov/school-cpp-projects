/*

   Daren Kostov
   Student List
   9/23/2022
*/
#include <iostream>
//#include <cstring>
#include <vector>
//#include <fstream>

using namespace std;
//https://stackoverflow.com/questions/42724722/how-to-iterate-through-vector-passed-as-pointer
//https://stackoverflow.com/questions/13467241/struct-initialization-arguments
//https://www.geeksforgeeks.org/vector-in-cpp-stl/i



struct Student{
	char name[20];
	char lastName[20];
	int id;
	float gpa;
	
	Student(char *Name, char *LastName, int Id, float Gpa){
		
		for(int i=0; i<20; i++){
		name[i]=Name[i];
		lastName[i]=LastName[i];		
		}		
		id=Id;
		gpa=Gpa;
	
	}
	
	
	
}; 



void ADD(vector<Student>* student);

void PRINT(vector<Student> student);

void REMOVE(vector<Student>* student);

int main(){

	
	
		
	cout << "ADD to add, EDIT to edit, PRINT to print, REMOVE to delete\n";	
	
	vector<Student> student;
	vector<Student> *studentP=&student;	
	while(true){
		char input[20];
		cin >> input;
		
		if(input[0]=='A')
			if(input[1]=='D')
				if(input[2]=='D')	
  				ADD(studentP);
		
		
		if(input[0]=='P')
			if(input[1]=='R')
				if(input[2]=='I')
					if(input[3]=='N')
						if(input[4]=='T')
							PRINT(student);			
						
						
		if(input[0]=='R')
			if(input[1]=='E')
				if(input[2]=='M')
					if(input[3]=='O')
						if(input[4]=='V')
							if(input[5]=='E')
								REMOVE(studentP);

		
		if(input[0]=='Q')
			if(input[1]=='U')
				if(input[2]=='I')
					if(input[3]=='T')
						return 0;
		
			}
}

void ADD(vector<Student>* student){

		char first[20];
		char last[20];
		int id;
		float gpa;
		cout << "First name: ";
		cin >> first;
		cout << "\nLast name: ";
		cin >> last;
		cout << "\nID: ";
		cin >> id;
		cout << "\nGPA: ";
		cin >> gpa;
		student->push_back(Student(first,last,id,gpa));
		cout << "Student added!\n";
}

void PRINT(vector<Student> student){

	for(std::vector<Student>::iterator i=student.begin(); i!=student.end(); i++){
		cout << "=============================\n";
		cout << i->name << endl;
		cout << i->lastName << endl;
		cout << i->id << endl;
		cout << i->gpa << endl;
	}
	
	cout << "Printing done!\n";
	
	
}

void REMOVE(vector<Student>* student){

	cout << "Student ID: ";
	int id;	
	cin >> id;
	for(std::vector<Student>::iterator i=student->begin(); i!=student->end(); i++){
		if(i->id==id){	
		student->erase(i);
		cout << "Student removed\n";
		return;
			
		}
	}
	cout << "Cannot find student!\n";
	
	
}

	
	
	
	

