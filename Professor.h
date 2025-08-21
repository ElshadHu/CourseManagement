#ifndef PROFESSOR_H
#define PROFESSOR_H


#include "Person.h"
#include "GradableActivity.h"
#include "UngradableActivity.h"
#include "CourseActivity.h"
#include "Student.h"
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
    Professor(std::string_view name, std::string_view id);
    void assignCourse(std::weak_ptr<Course>course);
    void print(std::ostream& os = std::cout) const override;
    //as i did here i need to do this for changing the grade and total
    bool addGradableActivityToCourse(std::string_view courseCode,activity::ActivityCategory category,
                                     std::string_view title,std::chrono::system_clock::time_point due,double totalScore);
    bool addUngradableActivityToCourse(std::string_view courseCode,activity::ungradableCategory category,
                                       std::string_view title,std::chrono::system_clock::time_point due);
    //for editing both i mean ungradable and gradable
    bool editActivityTitle(std::string_view courseCode,std::string_view activityTitle,std::string_view newTitle);
    bool editActivityDue(std::string_view courseCode,std::string_view activityTitle,std::chrono::system_clock::time_point due);
        //for gradable activities
    bool gradeStudent(std::string_view courseCode,std::string_view activityTitle,std::string_view studentId,activity::Grades grade);
    bool setActivityTotal(std::string_view courseCode,std::string_view activityTitle,double newTotal);
    //for helper  i mean wheter courseExists or not and wheter activity exists or not in the course
    Course* findCourseByCode(std::string_view courseCode);
    activity::CourseActivity*findActivity(std::string_view courseCode,std::string_view activityTitle);
    //for ungradable activity
    bool markStudentPresent(std::string_view courseCode,std::string_view activityTitle,const std::string &studentId);
    bool addStudentContribution(std::string_view courseCode,std::string_view activityTitle,const std::string&studentId);
};



}

#endif // PROFESSOR_H
