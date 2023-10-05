// Emre Dinç, 22103624, sec 2

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;
class Course; // forward declaration

class Student {
public:
    int studentId;
    std::string firstName;
    std::string lastName;
    Student* next;
    Student* prev;
    Course* courseHead;

    Student();
    Student(int studentId, const std::string& firstName, const std::string& lastName);
    ~Student();
    
    bool isEnrolled2(string courseName);
    bool isEnrolled(int courseId) const;
    bool addCourse(int courseId, const std::string& courseName);
    bool deleteCourse(int courseId);
    void showAllCourses() const;
};

#endif // STUDENT_H

