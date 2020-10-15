/* Name: Alex Sadler
   Student ID: 001792279
 */

#include "School.hpp"
#include <iostream>
using namespace std;

//------------------- Person methods -----------------------------
void Person::readPersonInfo() {
    // get person info based off of user input
    cout << "Enter full name: " << flush;
    getline(cin, fullname);

    cout << "Enter address: " << flush;
    getline(cin, address);

    cout << "Enter age: " << flush;
    cin >> age;

    cin.ignore();
    cout << endl;
}

void Person::printPersonInfo() {
    // print person info
    cout << "Full name: " << fullname << endl;
    cout << "Address: " << address << endl;
    cout << "Age: " << age << endl;
    cout << endl;
}

//------------------- Student methods ----------------------------
void Student::readStudentInfo() {
    Person::readPersonInfo();

    // get student info based off of user input
    cout << "Enter ID: " << flush;
    getline(cin, ID);

    cout << "Enter major: " << flush;
    getline(cin, major);

    cout << "Enter GPA: " << flush;
    cin >> gpa;

    cin.ignore();
    cout << endl;
}

void Student::printStudentInfo() {
    Person::printPersonInfo();

    // print student info
    cout << "Student ID: " << ID << endl;
    cout << "Major: " << major << endl;
    cout << "GPA: " << gpa << endl;
    cout << endl;
}

//------------------- Course methods -----------------------------
void Course::printCourseInfo() {
    // print course info
    cout << "Course ID: " << ID << endl;
    cout << "Course title: " << title << endl;
    cout << "Credits: " << credits << endl;
    cout << endl;
}

//------------------- CourseSection methods ----------------------
CourseSection::CourseSection(string ID, string title, int credits,
                             int sectionSize)
    : sectionSize(sectionSize), Course(ID, title, credits) {
    roster = new Student[sectionSize];
};

void CourseSection::fillRosterInfo() {
    Student temp;
    int i;
    int j;

    // insertion-sort algorithm
    for (i = 0; i < sectionSize; i++) {
        temp.readStudentInfo();
        j = i;
        while (j > 0 && temp.personName() < roster[j].personName()) {
            roster[j] = roster[j - 1];
            j--;
        }
        roster[j] = temp;
    }
}

void CourseSection::printSectionInfo() {
    // first print course info
    Course::printCourseInfo();

    // print info of each student in the section
    for (int i = 0; i < sectionSize; i++) {
        roster[i].printStudentInfo();
    }
};

void CourseSection::printAverageGPA() {
    double sum = 0;

    // get sum of students' GPAs
    for (int i = 0; i < sectionSize; i++) {
        sum += roster[i].studentGPA();
    }

    // print average GPA of students in section
    cout << "Average GPA: " << sum / sectionSize << endl;
}

void CourseSection::printYoungestStudent() {
    Student temp = roster[0];

    // find youngest student in section
    for (int i = 0; i < sectionSize; i++) {
        if (roster[i].personAGE() < temp.personAGE()) {
            temp = roster[i];
        }
    }

    // print info of youngest student in section
    temp.printStudentInfo();
}

CourseSection::~CourseSection() { delete[] roster; }