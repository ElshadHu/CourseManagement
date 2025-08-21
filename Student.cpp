#include "Student.h"
// #include "Course.h"
// #include "Person.h"
// #include <iostream>

namespace common {
    Student::Student(std::string_view name, std::string_view id)
        : Person(name,id) {}

    void Student::addCourse(std::weak_ptr<Course> course) {
        if (auto ptr = course.lock()) {
            for (auto& taken : m_takenCourses) {
                if (auto exist = taken.lock()) {
                    if (exist.get() == ptr.get()) {
                        std::cout << "Course already exists in student schedule.\n";
                        return;
                    }
                }
            }
            m_takenCourses.push_back(course);
        }
    }

    void Student::print(std::ostream& os ) const {

        Person::print(os);
        for (const auto& course : m_takenCourses) {
            if (auto c = course.lock()) {
                std::cout << " - " << c->getCourseName() << "\n";
            }
        }
    }
}
