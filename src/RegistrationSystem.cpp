// Emre Dinç, 22103624, sec 2

#include "RegistrationSystem.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
using namespace std;

RegistrationSystem::RegistrationSystem() : studentHead(nullptr), studentTail(nullptr), courseHead(nullptr) {}

RegistrationSystem::~RegistrationSystem() {
    Student* temp = studentHead;
    while(studentHead != nullptr) {
        temp = studentHead;
        studentHead = studentHead->next;
        delete temp;
    }
}

void RegistrationSystem::addStudent(const int studentId, const std::string firstName, const std::string lastName) {
    // Check if the student already exists
    Student* current = studentHead;
    while(current != nullptr) {
        if(current->studentId == studentId) {
            std::cout << "Student " << studentId << " already exists" << std::endl;
            return;
        }
        current = current->next;
    }

    // If student doesn't exist, create and add the student
    Student* newStudent = new Student(studentId, firstName, lastName);

    // If the list is empty, set newStudent as head
    if(studentHead == nullptr) {
        studentHead = newStudent;
        std::cout << "Student " << studentId << " has been added" << std::endl;
        return;
    }

    // If the list isn't empty, find the correct place to insert newStudent
    current = studentHead;
    while(current->next != nullptr && current->next->studentId < studentId) {
        current = current->next;
    }

    // If newStudent has to be inserted at the beginning
    if(current == studentHead && studentId < current->studentId) {
        newStudent->next = current;
        current->prev = newStudent;
        studentHead = newStudent;
    }
    // Else, insert newStudent in the correct position
    else {
        newStudent->next = current->next;
        newStudent->prev = current;
        if(current->next != nullptr)
            current->next->prev = newStudent;
        current->next = newStudent;
    }

    std::cout << "Student " << studentId << " has been added" << std::endl;
}

void RegistrationSystem::deleteStudent(const int studentId) {
    // Check if the list is empty
    if(studentHead == nullptr) {
        std::cout << "Student " << studentId << " does not exist" << std::endl;
        return;
    }

    // Check if the student to be deleted is the first student
    if(studentHead->studentId == studentId) {
        Student* temp = studentHead;
        studentHead = studentHead->next;
        if(studentHead != nullptr) {
            studentHead->prev = nullptr;
        }
        delete temp;
        std::cout << "Student " << studentId << " has been deleted" << std::endl;
        return;
    }

    // Find the student in the list
    Student* current = studentHead;
    while(current != nullptr && current->studentId != studentId) {
        current = current->next;
    }

    // If student is not found
    if(current == nullptr) {
        std::cout << "Student " << studentId << " does not exist" << std::endl;
        return;
    }

    // If student is found, delete the student
    current->prev->next = current->next;
    if(current->next != nullptr) {
        current->next->prev = current->prev;
    }
    delete current;
    std::cout << "Student " << studentId << " has been deleted" << std::endl;
}

void RegistrationSystem::addCourse(const int studentId, const int courseId, const std::string courseName) {
    Student* tempStudent = studentHead;
    Student *tempStudent2 = studentHead;
    while (tempStudent) {
        if (tempStudent->studentId == studentId) {
            if(tempStudent->isEnrolled(courseId)) {
                std::cout << "Student " << studentId << " is already enrolled in course " << courseId << std::endl;
                return;
            } else {
                while(tempStudent2) {
                    if(tempStudent2->isEnrolled(courseId)) {
                        if(!tempStudent2->isEnrolled2(courseName)) {
                            cout << "Course " << courseId << " exists with another name" << endl;
                            return;
                        }
                    }
                    tempStudent2 = tempStudent2->next;
                }
                tempStudent->addCourse(courseId, courseName);
                std::cout << "Course " << courseId << " has been added to student " << studentId << std::endl;
                return;
            }
        }
        tempStudent = tempStudent->next;
    }
    std::cout << "Student " << studentId << " does not exist" << std::endl;
}

void RegistrationSystem::showStudent(const int studentId) {
    // Traverse through the student list
    Student* tempStudent = studentHead;
    while (tempStudent) {
        if (tempStudent->studentId == studentId) {
            // If student is found, print their details
            std::cout << "Student id " << "First name " << "Last name\n" << 
                    tempStudent->studentId << " " << tempStudent->firstName << 
                    " " << tempStudent->lastName << std::endl;
            // Print all courses of the student
            tempStudent->showAllCourses();
            return;
        }
        tempStudent = tempStudent->next;
    }
    // If student with the given id does not exist
    std::cout << "Student " << studentId << " does not exist" << std::endl;
}

void RegistrationSystem::showAllStudents() {
    // If there are no students
    if (studentHead == nullptr) {
        std::cout << "There are no students in the system" << std::endl;
        return;
    }
    int count = 0;
    // If there are students, traverse through the list and print their details
    Student* tempStudent = studentHead;
    while (tempStudent) {
        if (count== 0) {
            std::cout << "Student id " << "First name " << "Last name\n";
            count++;
        }
        cout << tempStudent->studentId << " " << tempStudent->firstName << " " << tempStudent->lastName << std::endl;
        // Print all courses of the student
        tempStudent->showAllCourses();
        tempStudent = tempStudent->next;
    }
}

void RegistrationSystem::withdrawCourse(const int studentId, const int courseId) {
    Student* tempStudent = studentHead;
    while (tempStudent) {
        if (tempStudent->studentId == studentId) {
            if(tempStudent->isEnrolled(courseId)) {
                tempStudent->deleteCourse(courseId);
                std::cout << "Student " << studentId << " has been withdrawn from course " << courseId << "\n";
                return;
            } else {
                std::cout << "Student " << studentId << " is not enrolled in course " << courseId << "\n";
                return;
            }
        }
        tempStudent = tempStudent->next;
    }
    std::cout << "Student " << studentId << " does not exist\n";
}

void RegistrationSystem::cancelCourse(const int courseId) {
    Student* tempStudent = studentHead;
    bool courseExists = false;
    while (tempStudent) {
        if(tempStudent->isEnrolled(courseId)) {
            tempStudent->deleteCourse(courseId);
            courseExists = true;
        }
        tempStudent = tempStudent->next;
    }
    if(courseExists) {
        std::cout << "Course " << courseId << " has been cancelled\n";
    } else {
        std::cout << "Course " << courseId << " does not exist\n";
    }
}

void RegistrationSystem::showCourse(const int courseId) {
    Student* tempStudent = studentHead;
    bool courseFound = false;
    while (tempStudent) {
        Course* tempCourse = tempStudent->courseHead;
        while (tempCourse) {
            if (tempCourse->courseId == courseId) {
                int n = 0;
                if (n == 0) {
                    std::cout << "Course id " << "Course name" << endl;
                    n++;
                }
                std::cout << tempCourse->courseId  << tempCourse->courseName;
                courseFound = true;
                // print all students taking this course
                Student* currStudent = studentHead;
                while(currStudent) {
                    int count = 0;
                    if(currStudent->isEnrolled(courseId)) {
                        if (count== 0) {
                            std::cout << "Student id First name Last name\n";
                            count++;
                        }
                        std::cout << currStudent->studentId << " " << currStudent->firstName << " " << currStudent->lastName << std::endl;
                    }
                    currStudent = currStudent->next;
                }
                break;
            }
            tempCourse = tempCourse->next;
        }
        if(courseFound) {
            break;
        }
        tempStudent = tempStudent->next;
    }
    if(!courseFound) {
        std::cout << "Course " << courseId << " does not exist" << std::endl;
    }
}

