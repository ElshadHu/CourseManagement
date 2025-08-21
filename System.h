#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string_view>
#include <memory>
// #include <string>

namespace common {
class Student;
class Course;
class Professor;
class System {
    std::vector<std::shared_ptr<Student>> colOfStudents;
    std::vector<std::shared_ptr<Course>> colOfCourses;
    std::vector<std::shared_ptr<Professor>>colOfProfessors;

public:
    void addStudent(std::string_view studentName, std::string_view student_id);
    void addCourse(std::string_view courseName, std::string_view courseCode);
    void addProfessor(std::string_view profName, std::string_view profId);
    void enrollStudentInCourse(std::string_view student_id, std::string_view course_code);
    void enrollProfessorInCourse(std::string_view prof_id, std::string_view course_code);
    void showStudentSchedule(std::string_view studentName);
    void showProfSchedule(std::string_view profName);
    void showCourseRoster(std::string_view courseCode);
    void listAllStudents() const;
    void listAllCourses() const;
    void listAllProfessors()const;
};
}

#endif // SYSTEM_H
