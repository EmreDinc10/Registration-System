// Emre Dinç, 22103624, sec 2

#include "Student.h"
#include "Course.h"
#include <iostream>
using namespace std;

Student::Student() 
    : studentId(0), firstName(""), lastName(""), next(nullptr), prev(nullptr), courseHead(nullptr) {
}

Student::Student(int studentId, const std::string& firstName, const std::string& lastName) 
    : studentId(studentId), firstName(firstName), lastName(lastName), next(nullptr), prev(nullptr), courseHead(nullptr) {
}

Student::~Student() {
    //delete courses
    while (courseHead) {
        Course* tempCourse = courseHead;
        courseHead = courseHead->next;
        delete tempCourse;
    }
}

bool Student::isEnrolled(int courseId) const {
    Course* tempCourse = courseHead;
    while (tempCourse) {
        if (tempCourse->courseId == courseId)
            return true;
        tempCourse = tempCourse->next;
    }
    return false;
}

bool Student::isEnrolled2(string courseName) {
    Course* tempCourse = courseHead;
    while (tempCourse) {
        if (tempCourse->courseName == courseName)
            return true;
        tempCourse = tempCourse->next;
    }
    return false;
}

bool Student::addCourse(int courseId, const std::string& courseName) {
    if (isEnrolled(courseId)) {
        if(isEnrolled2(courseName)) {
            cout << "Course " << courseId << " already exists with another name" << endl;
        }
        std::cout << "The student is already enrolled in this course" << std::endl;
        return false;
    }

    Course* newCourse = new Course(courseId, courseName);
    if (!courseHead || courseHead->courseId > courseId) {
        newCourse->next = courseHead;
        courseHead = newCourse;
    } else {
        Course* tempCourse = courseHead;
        while (tempCourse->next && tempCourse->next->courseId < courseId)
            tempCourse = tempCourse->next;
        newCourse->next = tempCourse->next;
        tempCourse->next = newCourse;
    }

    return true;
}


bool Student::deleteCourse(int courseId) {
    if (!isEnrolled(courseId)) {
        cout << "Student is not enrolled in this course." << endl;
        return false;
    }

    Course *currentCourse = courseHead;
    Course *prevCourse = nullptr;
    while (currentCourse) {
        if (currentCourse->courseId == courseId) {
            if (prevCourse) {
                prevCourse->next = currentCourse->next;
            } else {
                // removing the head of the list
                courseHead = currentCourse->next;
            }
            delete currentCourse;
            //cout << "Course successfully removed." << endl;
            return true;
        }
        prevCourse = currentCourse;
        currentCourse = currentCourse->next;
    }

    return false;
}

void Student::showAllCourses() const {
    Course* tempCourse = courseHead;
    int count = 0;
    while (tempCourse) {
        if (count == 0) {
            std::cout << "Course id " << "Course name" << "\n";
            count++;
        }
        std::cout << tempCourse->courseId  << " " <<  tempCourse->courseName << endl;
        tempCourse = tempCourse->next;
    }
}
