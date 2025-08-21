#ifndef COURSEACTIVITY_H
#define COURSEACTIVITY_H
#include <string>
#include <iostream>
#include <string_view>
#include <chrono>
//this class will help me for polymorphic behaviour and i will use it for ungradable and gradable activities
namespace activity
{
class CourseActivity
{
    std::string m_title;
    std::chrono::system_clock::time_point m_dueTime;
      //i removed total becuase it does not make sense to derive from this class in that case for ungradableActivity
    //i took the setter function  which are    void setScore(double score);void setTotal(double total);
    //i will use them in the professor class to put the grade and total when it comes to ungradableActivities they will be able
    //derive from this class
public:
    CourseActivity(std::string_view title, std::chrono::system_clock::time_point due);
    std::string_view getTitle() const;
    std::chrono::system_clock::time_point getDueDate() const;
    //double getTotal()const;
    virtual std::string_view getType()const = 0;
    virtual std::string_view getStatus(std::string_view) const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual ~CourseActivity() = default;
    void setTitle(std::string_view title);
    void setDueDate(std::chrono::system_clock::time_point);
    bool isPastDue() const;


};

}

#endif
