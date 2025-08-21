#ifndef STUDENT_H
#define STUDENT_H

#include <string_view>
#include <vector>
#include <memory>
#include "Course.h"
#include "Person.h"

namespace common {
class Course; // Forward declaration

class Student: public Person {

    std::vector<std::weak_ptr<Course>> m_takenCourses;
public:
    Student(std::string_view name, std::string_view id);
    void addCourse(std::weak_ptr<Course> course);
    void print(std::ostream& os = std::cout) const override;
};
}
#endif // STUDENT_H
