#include "Professor.h"
#include "Course.h"

#include <vector>

namespace common
{
Professor::Professor(std::string_view name,std::string_view id):Person(name,id){}

    void Professor:: assignCourse(std::weak_ptr<Course>course){
        auto cs = course.lock();
        if (!cs)
        {
            return;
        }
        for (auto& taken : m_taughtCourses)
        {
            if (auto chosen = taken.lock())
            {
                if (cs.get() == chosen.get())
                {
                    std::cout << "The lesson is already chosen\n";
                    break;
                }
            }
        }
        m_taughtCourses.push_back(course);


    }


    void Professor::print(std::ostream&os) const
    {
        //for prof i call this
        Person::print(os);
        for (const auto& course : m_taughtCourses) {
            if (auto c = course.lock()) {
                os << " - " << c->getCourseName() << "\n";
            }
        }
    }

    Course* Professor:: findCourseByCode(std::string_view courseCode){
        for(auto&weakCourse:m_taughtCourses){
            if(auto course = weakCourse.lock()){
                if(course->getCourseCode() == courseCode){
                    return course.get();
                }
            }
        }
        return nullptr;
    }


}
