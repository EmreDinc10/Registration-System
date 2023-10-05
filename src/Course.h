// Emre Dinç, 22103624, sec 2

#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
using namespace std;
class Student;  // Forward declaration

class Course {
public:
    int courseId;
    string courseName;
    Course* next;
    Student* studentHead;
    Student* studentTail;

    Course(int courseId, const string& courseName);
    ~Course();

    bool isTaken(int studentId) const;
    bool addStudent(int studentId, const string& firstName, const string& lastName);
    bool deleteStudent(int studentId);
};

#endif //COURSE_H
