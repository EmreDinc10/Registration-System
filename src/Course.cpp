// Emre Dinç, 22103624, sec 2

#include "Student.h"
#include "Course.h"
#include <iostream>
using namespace std;

Course::Course(int courseId, const string& courseName)
: courseId(courseId), courseName(courseName), next(nullptr), studentHead(nullptr), studentTail(nullptr) {}

Course::~Course() {
    Student *currentStudent = studentHead;
    while (currentStudent) {
        Student *toDelete = currentStudent;
        currentStudent = currentStudent->next;
        delete toDelete;
    }
}

bool Course::isTaken(int studentId) const {
    Student *currentStudent = studentHead;
    while (currentStudent) {
        if (currentStudent->studentId == studentId) {
            return true;
        }
        currentStudent = currentStudent->next;
    }
    return false;
}

bool Course::addStudent(int studentId, const string& firstName, const string& lastName) {
    if (isTaken(studentId)) {
        cout << "The student is already enrolled in this course." << endl;
        return false;
    }
    Student* newStudent = new Student(studentId, firstName, lastName);
    
    // Insert newStudent into the list in ascending order.
    if (studentHead == nullptr || studentHead->studentId > studentId) {
        newStudent->next = studentHead;
        if (studentHead != nullptr)
            studentHead->prev = newStudent;
        studentHead = newStudent;
    } else {
        Student* current = studentHead;
        while (current->next != nullptr && current->next->studentId < studentId) {
            current = current->next;
        }
        newStudent->next = current->next;
        if (current->next != nullptr)
            current->next->prev = newStudent;
        current->next = newStudent;
        newStudent->prev = current;
    }
    return true;
}

bool Course::deleteStudent(int studentId) {
    if (!isTaken(studentId)) {
        cout << "Student is not enrolled in this course." << endl;
        return false;
    }

    Student *currentStudent = studentHead;
    while (currentStudent) {
        if (currentStudent->studentId == studentId) {
            // Connect the previous and next students, if they exist.
            if (currentStudent->prev != nullptr) {
                currentStudent->prev->next = currentStudent->next;
            } else {
                // We're removing the head of the list.
                studentHead = currentStudent->next;
            }
            if (currentStudent->next != nullptr) {
                currentStudent->next->prev = currentStudent->prev;
            }
            delete currentStudent;
            cout << "Student successfully removed from the course." << endl;
            return true;
        }
        currentStudent = currentStudent->next;
    }

    return false;
}
