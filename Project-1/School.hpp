/* Name: Alex Sadler
   Student ID: 001792279
 */

#pragma once
#include <iostream>

using namespace std;

class Person {
   private:
    string fullname;
    string address;
    int age;

   public:
    void readPersonInfo();       // read person's info
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
    void readStudentInfo();      // read student's info
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

   public:
   CourseSection(string ID, string title, int credits, int sectionSize);
   void fillRosterInfo();        // read the info of all students in the section one at a time
   void printSectionInfo();      // print section info, starting with course info
   void printAverageGPA();       // print the average GPA of the students in the section
   void printYoungestStudent();  // print info of youngest stduent in section
   ~CourseSection();

};
