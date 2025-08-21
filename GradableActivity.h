#ifndef GRADABLE_ACTIVITY_H
#define GRADABLE_ACTIVITY_H

#include "CourseActivity.h"
#include <unordered_map>
#include <string>
#include <chrono>
#include <string_view>

namespace activity {

enum class ActivityCategory { Assignment, Test, Quiz };

inline std::string_view toString(ActivityCategory c) {
    switch (c) {
    case ActivityCategory::Assignment: return "Assignment";
    case ActivityCategory::Test:       return "Test";
    case ActivityCategory::Quiz:       return "Quiz";
    }
    return "Unknown";
}

enum class Grades { A,B,C,D,F,Incomplete,Withdrawn };
std::string_view gradeToString(Grades g);

class GradableActivity : public CourseActivity {
    ActivityCategory m_category;
    double m_total = 0.0;

    // per-student data
    std::unordered_map<std::string, Grades> m_grades;        // id -> grade
    std::unordered_map<std::string, std::string> m_feedback; // id -> comment
    std::unordered_map<std::string, std::chrono::system_clock::time_point> m_submitAt;

public:
    GradableActivity(ActivityCategory category,
                     std::string_view title,
                     std::chrono::system_clock::time_point due,
                     double totalScore = 100.0);

    // Polymorphic API
    std::string_view getType() const override { return toString(m_category); }
    std::string_view getStatus(std::string_view studentId) const override;
    void print(std::ostream& os) const override;

    // Accessors
    ActivityCategory category() const { return m_category; }
    double total() const { return m_total; }
    //setter
    void setTotal(double totalScore){m_total = totalScore;}
    // Grade ops
    void submitGrade(const std::string& studentId, Grades grade,
                     std::chrono::system_clock::time_point ts = std::chrono::system_clock::now());
    bool hasGrade(std::string_view studentId) const;
    Grades getGrade(std::string_view studentId) const;


    // Stats
    int countSubmissions() const;
    int countByGrade(Grades g) const;

    // Feedback i am thinking to add this to the prof class
    void leaveFeedback(const std::string& studentId, const std::string& comment);
    std::string getFeedback(std::string_view studentId) const;

    // Late
    bool isLate(std::string_view studentId) const; // simple version (uses due vs now)
};

} // namespace activity
#endif
