/* Name: Alex Sadler
   Student ID: 001792279
 */

#include "School.hpp"
#include <fstream>  //Required for ifstream, ofstream
#include <iostream>
#include <stdexcept>
using namespace std;

//------------------- Person methods -----------------------------
void Person::readPersonInfo(ifstream *pf) {
    // get person info from file
    getline(*pf, fullname);
    getline(*pf, address);
    string tempS;
    getline(*pf, tempS);
    age = stoi(tempS);
}

void Person::printPersonInfo() {
    // print person info
    // cout << "Full name: " << fullname << endl;
    // cout << "Address: " << address << endl;
    // cout << "Age: " << age << endl;
    // cout << endl;
    cout << fullname << "\t" << address << "\t" << age;
}

//------------------- Student methods ----------------------------
void Student::readStudentInfo(ifstream *sf) {
    Person::readPersonInfo(sf);
    getline(*sf, ID);
    getline(*sf, major);
    string tempF;
    getline(*sf, tempF);
    gpa = stof(tempF);

    cout << endl;
}

void Student::printStudentInfo() {
    Person::printPersonInfo();

    // print student info
    // cout << "Student ID: " << ID << endl;
    // cout << "Major: " << major << endl;
    // cout << "GPA: " << gpa << endl;
    // cout << endl;
    cout << "\t" << ID << "\t" << major << "\t" << gpa;
}

//------------------- Course methods -----------------------------
void Course::printCourseInfo() {
    // print course info
    cout << "Course ID: " << ID << endl;
    cout << "Course title: " << title << endl;
    cout << "Credits: " << credits << endl;
}

//------------------- CourseSection methods ----------------------
CourseSection::CourseSection(string ID, string title, int credits,
                             int sectionSize)
    : Course(ID, title, credits), sectionSize(sectionSize) {
    roster = new Student[sectionSize];
    sortedNames = new Student *[sectionSize];
    sortedAges = new Student *[sectionSize];
    sortedGPAs = new Student *[sectionSize];
};

void CourseSection::fillRosterInfo(ifstream *rf) {
    // fill roster info
    Student temp;

    int i = 0;
    while ((!(*rf).eof()) && (i < sectionSize)) {
        temp.readStudentInfo(rf);
        roster[i] = temp;

        // store pointers for sorted arrays
        sortedNames[i] = &roster[i];
        sortedAges[i] = &roster[i];
        sortedGPAs[i] = &roster[i];

        i++;
    }

    // call methods to sort arrays of pointers
    CourseSection::sortNames();
    CourseSection::sortAges();
    CourseSection::sortGPAs();
}

// names methods
void CourseSection::sortNames() {
    Student *temp;
    int i;
    int j;

    // insertion-sort algorithm
    for (i = 0; i < sectionSize; i++) {
        j = i;
        while (j > 0 && (*sortedNames[j]).personName() <
                            (*sortedNames[j - 1]).personName()) {
            temp = sortedNames[j];
            sortedNames[j] = sortedNames[j - 1];
            sortedNames[j - 1] = temp;

            j--;
        }
    }
}

void CourseSection::printSectionInfoByName() {
    cout << "Section info (course and students info) sorted by students' name:"
         << endl;
    Course::printCourseInfo();
    cout << "Number of students in course section: " << sectionSize << endl;
    
    // table formatting
    cout << "Seq\t"
         << "Name\t\t"
         << "Address\t\t"
         << "Age\t"
         << "ID\t\t"
         << "Major\t"
         << "GPA" << endl;
    cout << "===\t"
         << "====\t\t"
         << "======\t\t"
         << "===\t"
         << "==\t\t"
         << "=====\t"
         << "===" << endl;
    
    // print students' info in order of names
    for (int i = 0; i < sectionSize; i++) {
        cout << i + 1 << "\t";
        (*sortedNames[i]).printStudentInfo();
        cout << endl;
    }

    cout << endl;
}

// ages methods
void CourseSection::sortAges() {
    Student *temp;
    int i;
    int j;

    // insertion-sort algorithm
    for (i = 0; i < sectionSize; i++) {
        j = i;
        while (j > 0 && (*sortedAges[j]).personAGE() <
                            (*sortedAges[j - 1]).personAGE()) {
            temp = sortedAges[j];
            sortedAges[j] = sortedAges[j - 1];
            sortedAges[j - 1] = temp;

            j--;
        }
    }
}

void CourseSection::printSectionInfoByAge() {
    cout << "Section info (course and students info) sorted by students' age:"
         << endl;
    Course::printCourseInfo();
    cout << "Number of students in course section: " << sectionSize << endl;
    
    // table formatting
    cout << "Seq\t"
         << "Name\t\t"
         << "Address\t\t"
         << "Age\t"
         << "ID\t\t"
         << "Major\t"
         << "GPA" << endl;
    cout << "===\t"
         << "====\t\t"
         << "======\t\t"
         << "===\t"
         << "==\t\t"
         << "=====\t"
         << "===" << endl;

    // print students' info in order of age
    for (int i = 0; i < sectionSize; i++) {
        cout << i + 1 << "\t";
        (*sortedAges[i]).printStudentInfo();
        cout << endl;
    }
    cout << endl;
}

// GPA methods
void CourseSection::sortGPAs() {
    Student *temp;
    int i;
    int j;

    // insertion-sort algorithm
    for (i = 0; i < sectionSize; i++) {
        j = i;
        while (j > 0 && (*sortedGPAs[j]).studentGPA() >
                            (*sortedGPAs[j - 1]).studentGPA()) {
            temp = sortedGPAs[j];
            sortedGPAs[j] = sortedGPAs[j - 1];
            sortedGPAs[j - 1] = temp;

            j--;
        }
    }
}

void CourseSection::printSectionInfoByGPA() {
       cout << "Section info (course and students info) sorted by students' GPA:"
         << endl;
    Course::printCourseInfo();
    cout << "Number of students in course section: " << sectionSize << endl;

    // table formatting
    cout << "Seq\t"
         << "Name\t\t"
         << "Address\t\t"
         << "Age\t"
         << "ID\t\t"
         << "Major\t"
         << "GPA" << endl;
    cout << "===\t"
         << "====\t\t"
         << "======\t\t"
         << "===\t"
         << "==\t\t"
         << "=====\t"
         << "===" << endl;

    // print students' info in order of gpa
    for (int i = 0; i < sectionSize; i++) {
        cout << i + 1 << "\t";
        (*sortedGPAs[i]).printStudentInfo();
        cout << endl;
    }
    cout << endl;
}


CourseSection::~CourseSection() {
    delete[] roster;
    delete[] sortedNames;
    delete[] sortedAges;
    delete[] sortedGPAs;
}
