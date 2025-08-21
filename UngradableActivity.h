#ifndef UNGRADABLEACTIVITY_H
#define UNGRADABLEACTIVITY_H
#include "CourseActivity.h"
#include <unordered_map>
#include <string>
#include <chrono>
#include <string_view>
namespace activity{

enum class attendanceStatus { P,A,L,MA,FE,FT };
std::string_view toString(attendanceStatus a);

enum class ungradableCategory {Attendance,Discussion};

inline std::string_view ungradableToString(ungradableCategory cat){
    switch(cat){
    case ungradableCategory::Attendance: return "Attendance";
    case ungradableCategory::Discussion: return "Discussion";
    }
    return "Unknown";
}

class UngradableActivity:public CourseActivity{
        ungradableCategory m_category;
        std::unordered_map<std::string,attendanceStatus>m_status;//id->attendance status
        std::unordered_map<std::string,int>m_discussion;//id->adding discussion
    public:
        UngradableActivity(std::string_view title,ungradableCategory category, std::chrono::system_clock::time_point due);
        std::string_view getType()const override {return ungradableToString(m_category);}
        std::string_view getStatus(std::string_view studentId)const override;
        void print(std::ostream& os) const override;
        ungradableCategory category() const {return m_category;}
       //PROFESSOR FACING API
        void setStatus(const std::string&studentId,attendanceStatus s);
        // this is for wrapping instead of writing for every status
        void markAttendance (const std::string &id,attendanceStatus s){setStatus(id,s);}
        void addContribution(const std::string& studentId,int delta = 1);//for counting the contribution by the student
        int getContributionCount(const std::string& studentId)const;

    };





}



#endif // UNGRADABLEACTIVITY_H
