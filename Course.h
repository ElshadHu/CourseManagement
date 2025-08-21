#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <iostream>
#include "ActivityManager.h"
// #include "Professor.h"

namespace common {
class Student; // Forward declaration
//this class and Student class is mutually dependent that is why i am using system class for  collection of them and here collections are stored in weak pointers
class Professor;
class Course {
    std::string m_courseName;
    std::string m_courseCode;
    std::vector<std::weak_ptr<Student>> m_chosenStudents;
    std::vector< std::weak_ptr<Professor>>m_chosenProfessor;
    activity::ActivityManager m_activityMngr;

public:
    Course(std::string_view courseName, std::string_view courseCode);
    void addStudent(std::weak_ptr<Student> student);
    void addTeacher(std::weak_ptr<Professor> professor);
    std::string getCourseName() const;
    std::string getCourseCode() const;
    void print() const;

    //added for managing activities
    //the main difference between  them is that compiler will choose wheter it is only for reading or it is need to write something on it
    activity::ActivityManager&activities();
    const activity::ActivityManager&activities() const;
    //temporary i will conver weak pointer into shared pointer in order to return it back wheter it exists or not then i will use in the professor class
    std::shared_ptr<Student>findStudentById(std::string_view id)const;

};
}


#endif // COURSE_H
