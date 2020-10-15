#include "School.hpp"
#include <iostream>
#include <fstream> //Required for ifstream, ofstream
#include <stdexcept>

using namespace std;


int main() { //reads from a text file that contains three lines: string, an integer, and a float
	
    ifstream inf;
    string tempS;

	// inf.open("/Users/alexsadler/Desktop/homework2/src/section01.txt");
    inf.open("/Users/Student/asadler/Homework2/section01.txt");

    // Person person;
	// person.readPersonInfo(&inf);
	// person.printPersonInfo();
    // return 0;

	// Student student;
	// student.readStudentInfo(&inf);
	// student.printStudentInfo();
	
	CourseSection cs("eece", "2560", 4, 4);
	cs.fillRosterInfo(&inf);
	cs.printSectionInfoByName();
	// cout << endl;
	cs.printSectionInfoByAge();
	// cout << endl;
	cs.printSectionInfoByGPA();
	

	return 0;




   /*  string s;
	int i;
	float f;
	ifstream inf;

	inf.open("/Users/alexsadler/Desktop/homework2/src/myfile.txt");
	if (inf.fail()) 	{ 
		cerr << "Error: Could not open input file\n";
		exit(1);
	}

	inf.exceptions(ifstream::failbit | ifstream::badbit); //activate the exception handling of inf stream 

	string tempS;
	try {
		getline(inf, s);
		getline(inf, tempS); i = stoi(tempS); //convert string to an integer
		getline(inf, tempS); f = stof(tempS); //convert string to a float
	}
	catch (ifstream::failure e) {
		cerr << "Error: File does not have enough data\n";
		exit(1);
	}
	catch (invalid_argument e) { //if stoi or stof cannot convert tempS to a number
		cerr << "Error: File contains invalid data\n";
		exit(1);
	}

	cout << "s = " << s << endl;
	cout << "i = " << i << endl;
	cout << "f = " << f << endl;
	return 0; */
}