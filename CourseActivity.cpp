#include "CourseActivity.h"
#include <string>
#include <iostream>
#include<string_view>

namespace activity
{
CourseActivity::CourseActivity(std::string_view title, std::chrono::system_clock::time_point due):m_title(title),
    m_dueTime(due){}

std::string_view CourseActivity::getTitle() const{ return m_title; }
std::chrono::system_clock::time_point CourseActivity::getDueDate()const { return m_dueTime;}
//double CourseActivity::getTotal()const { return m_scoreTotal; }

void  CourseActivity::setTitle(std::string_view title) { m_title = title; }
void CourseActivity::setDueDate(std::chrono::system_clock::time_point timestamp) { m_dueTime = timestamp; }

bool CourseActivity::isPastDue() const {
    return std::chrono::system_clock::now() > m_dueTime;
}


}

