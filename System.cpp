#include "System.h"
#include "Student.h"
#include "Course.h"
#include "Professor.h"
#include <iostream>
#include <string_view>

namespace common {

void System::addStudent(std::string_view studentName, std::string_view student_id) {
    colOfStudents.push_back(std::make_shared<Student>(studentName, student_id));
}

void System::addCourse(std::string_view courseName, std::string_view courseCode) {
    colOfCourses.push_back(std::make_shared<Course>(courseName, courseCode));
}
void System:: addProfessor(std::string_view profName, std::string_view profId) {
    colOfProfessors.push_back(std::make_shared<Professor>(profName, profId));
}
void System::enrollProfessorInCourse(std::string_view prof_id, std::string_view course_code){

    std::shared_ptr<Professor>professor = nullptr;
    std::shared_ptr<Course>course = nullptr;
    for (auto& tc : colOfProfessors){
        if (tc->getId() == prof_id){
            professor = tc;
            break;
        }
    }

    for (auto& cs : colOfCourses) {
        if (cs->getCourseCode() == course_code) {
            course = cs;
            break;
        }
    }

    if (course && professor){
        professor->assignCourse(course);
        course->addTeacher(professor);
    }
    else {
        std::cout << "Either professor or course not found\n";
    }

}
void System::enrollStudentInCourse(std::string_view student_id, std::string_view course_code) {
    std::shared_ptr<Student> student = nullptr;
    std::shared_ptr<Course> course = nullptr;

    for (auto& st : colOfStudents) {
        if (st->getId() == student_id) {
            student = st;
            break;
        }
    }

    for (auto& cor : colOfCourses) {
        if (cor->getCourseCode() == course_code) {
            course = cor;
            break;
        }
    }

    if (student && course) {
        student->addCourse(course);
        course->addStudent(student);
    }
    else {
        std::cout << "Either student or course not found.\n";
    }
}
void System::showProfSchedule(std::string_view profName)
{
    for (auto& teacher : colOfProfessors)
    {
        if (teacher->getName() == profName)
        {
            teacher->print();
            return;
        }
    }
}


void System::showStudentSchedule(std::string_view studentName) {
    for (auto& st : colOfStudents) {
        if (st->getName() == studentName) {
            st->print();
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void System::showCourseRoster(std::string_view courseCode) {
    for (auto& cs : colOfCourses) {
        if (cs->getCourseCode() == courseCode) {
            cs->print();
            return;
        }
    }



    std::cout << "Course not found.\n";
}

void System::listAllStudents() const {
    for (const auto& st : colOfStudents)
        std::cout << " - " << st->getName() << " [" << st->getId() << "]\n";
}

void System::listAllCourses() const {
    for (const auto& cs : colOfCourses)
        std::cout << " - " << cs->getCourseName() << " (" << cs->getCourseCode() << ")\n";
}
void  System::listAllProfessors() const
{
    for (const auto& prof : colOfProfessors)
    {
        std::cout << "- " << prof->getName() << " [" << prof->getId() << "]\n";
    }
}
}
