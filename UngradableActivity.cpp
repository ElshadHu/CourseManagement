#include "UngradableActivity.h"


namespace activity{

    std::string_view toString(attendanceStatus a) {
        switch (a) {
        case attendanceStatus::P:  return "Present";
        case attendanceStatus::A:  return "Absent";
        case attendanceStatus::L:  return "Late";
        case attendanceStatus::MA: return "Medical Absence";
        case attendanceStatus::FE: return "Family Emergency";
        case attendanceStatus::FT: return "Field Trip";
        }
        return "Unknown";
    }
    UngradableActivity::UngradableActivity(std::string_view title,ungradableCategory category,
                                           std::chrono::system_clock::time_point due):CourseActivity(title,due),m_category(category){}

    void UngradableActivity::setStatus(const std::string&studentId,attendanceStatus s){
        m_status[studentId] = s;
    }

    std::string_view UngradableActivity::getStatus(std::string_view studentId) const{
        auto it = m_status.find(std::string(studentId));
        return (it==m_status.end())?"No Record ":toString(it->second);
    }

    void UngradableActivity::print(std::ostream& os) const {
        os << getType() << " \"" << getTitle() << "\"\n";
        for (const auto& [id, s] : m_status) {
            os << " - " << id << ": " << toString(s) << '\n';
        }
    }
    void UngradableActivity:: addContribution(const std::string& studentId,int delta){
        m_discussion[studentId] += delta;
    }

    int UngradableActivity::getContributionCount(const std::string &studentId) const{
        auto it = m_discussion.find(std::string(studentId));
        return (it!=m_discussion.end())?it->second:0;
    }
}
