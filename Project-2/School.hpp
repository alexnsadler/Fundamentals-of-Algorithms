/* Name: Alex Sadler
   Student ID: 001792279
 */

#pragma once
#include <iostream>
#include <fstream> //Required for ifstream, ofstream
#include <stdexcept>

using namespace std;

class Person {
   private:
    string fullname;
    string address;
    int age;

   public:
    void readPersonInfo(ifstream *pf);       // read person's info
    void printPersonInfo();      // print person's info
    int personAGE() { return age; };
    string personName() { return fullname; };
};

class Student : public Person {
   private:
    string ID;
    string major;
    float gpa;

   public:
    void readStudentInfo(ifstream* sf);      // read student's info
    void printStudentInfo();     // print student's info
    float studentGPA() { return gpa; };
};

class Course {
   private:
    string ID;
    string title;
    int credits;

   public:
    Course(string ID_in, string title_in, int credits_in)
        : ID(ID_in), title(title_in), credits(credits_in){};
    void printCourseInfo();      // print course info
};

class CourseSection : public Course {
   private:
    int sectionSize;
    Student *roster;
    Student **sortedNames;
    Student **sortedAges;
    Student **sortedGPAs;
    void sortNames();
    void sortAges();
    void sortGPAs();

   public:
   CourseSection(string ID, string title, int credits, int sectionSize);
   void fillRosterInfo(ifstream *rf);     // read the info of all students in the section
   void printSectionInfoByName();         // print section info, ordered by name
   void printSectionInfoByAge();          // print section info, ordered by age
   void printSectionInfoByGPA();          // print section info, ordered by gpa
   ~CourseSection();

};
