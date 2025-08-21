#include "Professor.h"
#include "Course.h"
//#include<memory>
//#include <iostream>
//#include <string_view>
// #include <string>
#include <vector>

namespace common
{
    Professor::Professor(std::string_view name, std::string_view id) :Person(name, id){}

    void Professor::assignCourse(std::weak_ptr<Course>course)
    {
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

    bool Professor::addGradableActivityToCourse(
        std::string_view courseCode,
        activity::ActivityCategory category,
        std::string_view title,
        std::chrono::system_clock::time_point due,
        double totalScore)
    {
        for (auto& weakCourse : m_taughtCourses) {
            auto course = weakCourse.lock();
            if (!course) continue; // skip if expired

            if (course->getCourseCode() != courseCode) continue; // skip if not match

            course->activities().addActivity(
                std::make_unique<activity::GradableActivity>(
                    category, title, due, totalScore
                    )
                );
            return true;
        }
        return false;
    }

    //helper function for finding the course or send nullptr
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

    //find the course and go to its activities and find the activity by title
        activity::CourseActivity* Professor::findActivity(std::string_view courseCode,std::string_view activityTitle){
            auto course = findCourseByCode(courseCode);
            if(!course) return nullptr;
            return course->activities().findActivityByTitle(activityTitle);
        }

    bool Professor:: addUngradableActivityToCourse(std::string_view courseCode,activity::ungradableCategory category,
                                                  std::string_view title,std::chrono::system_clock::time_point due){

        auto course = findCourseByCode(courseCode);
        if(!course) return false;

        if(course){
            course->activities().addActivity(
                std::make_unique<activity::UngradableActivity>(
                    title,category,due));
        }
            return true;

    }
    bool Professor:: editActivityTitle(std::string_view courseCode,std::string_view activityTitle,std::string_view newTitle){
        auto course = findCourseByCode(courseCode);
        if(!course) return false;

            if( auto*activity = course->activities().findActivityByTitle(activityTitle)){
                activity->setTitle(newTitle);
            }
            return true;

    }

    bool Professor:: editActivityDue(std::string_view courseCode,std::string_view activityTitle,std::chrono::system_clock::time_point due){
        auto course = findCourseByCode(courseCode);
        if(!course) return false;
            if(auto*activity = course->activities().findActivityByTitle(activityTitle)){
                activity->setDueDate(due);
            }
            return true;
    }

    //if i wrote auto* stud it will not be correct becuase that is the shared_ptr i have to do dynamic cast to make it gradable
    bool Professor:: gradeStudent(std::string_view courseCode,std::string_view activityTitle,std::string_view studentId,activity::Grades grade){

        auto course = findCourseByCode(courseCode);
        if(!course) return false;

        auto stud = course->findStudentById(studentId);
        if(!stud) return false;

        auto *act =findActivity(courseCode,activityTitle);
        if(!act) return false;
        if(auto *gradableAct = dynamic_cast<activity::GradableActivity*>(act)){
            gradableAct->submitGrade(stud->getId(),grade);
            return true;
        }
        return false;

        }
    bool Professor:: setActivityTotal(std::string_view courseCode,std::string_view activityTitle,double newTotal){
        auto course = findCourseByCode(courseCode);
        if(!course) return false;
        auto *act = findActivity(courseCode,activityTitle);
        if(!act) return false;
        if(auto *gradableAct = dynamic_cast<activity::GradableActivity*>(act)){
            gradableAct->setTotal(newTotal);
            return true;
        }
        return false;
    }

    bool Professor::markStudentPresent(std::string_view courseCode,std::string_view activityTitle,const std::string &studentId){
        auto course = findCourseByCode(courseCode);
        if(!course) return false;
        auto *act = findActivity(courseCode,activityTitle);
        if(!act) return false;
        if(auto*ungradableAct = dynamic_cast<activity::UngradableActivity*>(act)){
            ungradableAct->markAttendance(studentId,activity::attendanceStatus::P);
            return true;
        }
        return false;
    }

    bool Professor:: addStudentContribution(std::string_view courseCode,std::string_view activityTitle,const std::string&studentId){
        auto course = findCourseByCode(courseCode);
        if(!course) return false;
        auto *act = findActivity(courseCode,activityTitle);
        if(auto* ungradableAct = dynamic_cast<activity::UngradableActivity*>(act)){
            ungradableAct->addContribution(studentId);
            return true;
        }
        return false;
    }


}
