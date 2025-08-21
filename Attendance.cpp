#include"Attendance.h"

namespace activity{
Attendance:: Attendance(std::string_view title, std::chrono::system_clock::time_point date):CourseActivity(title,date){}

void Attendance:: markPresent(std::string_view studentId){
    for(auto&[id,presence]:m_attendanceMap){
        if( id== studentId){
            presence = true;
            break;
        }
    }
}

bool Attendance:: isPresent(std::string_view studentId) const{
    
    for(auto&[id,presence]:m_attendanceMap){
        if( id  == studentId){
            return true;
            break;
        }
    }
    return false;
}

void Attendance:: markAbsent(std::string_view studentId){
    for(auto&[id,presence]:m_attendanceMap){
        if( id  == studentId){
            presence = false;
            break;
        }
    }
    
}

    std::string_view Attendance:: getType() const{ return "Attendance";}

}
