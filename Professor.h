#ifndef PROFESSOR_H
#define PROFESSOR_H


#include "Person.h"
#include "Course.h"
#include <iostream>
#include <memory>
#include <string_view>
#include <vector>
#include <chrono>
namespace common
{
class Course;
class Professor:public Person {

    std::vector<std::weak_ptr<Course>>m_taughtCourses;

public:
    Professor(std::string_view name,std::string_view id);
    void assignCourse(std::weak_ptr<Course> course);
    void print(std::ostream&os = std::cout) const override;
    Course* findCourseByCode(std::string_view courseCode);


};



}

#endif // PROFESSOR_H
