#ifndef ATTENDANCE_H
#define ATTENDANCE_H
#include <unordered_map>
#include <iostream>
#include <string>
#include <string_view>
#include <chrono>
#include "CourseActivity.h"
namespace activity{

class Attendance{
    std::unordered_map<std::string,bool>m_attendanceMap;

public:
    Attendance(std::string_view title, std::chrono::system_clock::time_point date);
    void markPresent(std::string_view studentId);
     bool isPresent(std::string_view studentId) const
        void  markAbsent(std::string_view studentId);

};



}

#endif // ATTENDANCE_H
