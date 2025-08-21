#include "GradableActivity.h"
#include <stdexcept>

namespace activity {


std::string_view gradeToString(Grades g) {
    switch (g) {
    case Grades::A:          return "A";
    case Grades::B:          return "B";
    case Grades::C:          return "C";
    case Grades::D:          return "D";
    case Grades::F:          return "F";
    case Grades::Incomplete: return "Incomplete";
    case Grades::Withdrawn:  return "Withdrawn";
    }
    return "Unknown";
}

GradableActivity::GradableActivity(ActivityCategory category,
                                   std::string_view title,
                                   std::chrono::system_clock::time_point due,
                                   double totalScore)
    : CourseActivity(title, due),
    m_category(category),
    m_total(totalScore) {}

std::string_view GradableActivity::getStatus(std::string_view studentId) const {
    if (!hasGrade(studentId)) return "Not Submitted";
    return isLate(studentId) ? "Submitted late" : "Graded";
}

void GradableActivity::print(std::ostream& os) const {
    os << toString(m_category) << " \"" << getTitle() << "\" (total " << m_total << ")\n";
    for (const auto& [id, grade] : m_grades) {
        os << " - " << id << ": " << gradeToString(grade) << '\n';
    }
}

// Grade ops
void GradableActivity::submitGrade(const std::string& studentId, Grades grade,
                                   std::chrono::system_clock::time_point ts) {
    m_grades[studentId]   = grade;
    m_submitAt[studentId] = ts;
}

bool GradableActivity::hasGrade(std::string_view studentId) const {
    return m_grades.find(std::string(studentId)) != m_grades.end();
}

Grades GradableActivity::getGrade(std::string_view studentId) const {
    auto it = m_grades.find(std::string(studentId));
    if (it == m_grades.end())
        throw std::runtime_error("Student not found for this activity");
    return it->second;
}

// Stats
int GradableActivity::countSubmissions() const {
    return static_cast<int>(m_grades.size());
}

int GradableActivity::countByGrade(Grades g) const {
    int cnt = 0;
    for (const auto& [_, gg] : m_grades) if (gg == g) ++cnt;
    return cnt;
}

// Feedback i will think about it becuase prof does that
void GradableActivity::leaveFeedback(const std::string& studentId, const std::string& comment) {
    m_feedback[studentId] = comment;
}

std::string GradableActivity::getFeedback(std::string_view studentId) const {
    auto it = m_feedback.find(std::string(studentId));
    return (it == m_feedback.end()) ? "No feedback" : it->second;
}

// Late (simple policy: submission time after due)
bool GradableActivity::isLate(std::string_view studentId) const {
    auto it = m_submitAt.find(std::string(studentId));
    if (it == m_submitAt.end()) return false;              // no submission
    return it->second > getDueDate();                       // submitted after due
}


} // namespace activity
