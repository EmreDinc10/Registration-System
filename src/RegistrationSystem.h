// Emre Dinç, 22103624, sec 2

#ifndef REGISTRATIONSYSTEM_H
#define REGISTRATIONSYSTEM_H
#include <iostream>
#include <string>
using namespace std;
class Student;
class Course;

class RegistrationSystem {
public:
    RegistrationSystem();
    ~RegistrationSystem();

    void addStudent(const int studentId, const std::string firstName, const std::string lastName);
    void deleteStudent(const int studentId);
    void addCourse(const int studentId, const int courseId, const std::string courseName);
    void withdrawCourse(const int studentId, const int courseId);
    void cancelCourse(const int courseId);
    void showStudent(const int studentId);
    void showCourse(const int courseId);
    void showAllStudents();

    Student* studentHead;
    Student* studentTail;

    Course* courseHead;
};

#endif //REGISTRATIONSYSTEM_H
