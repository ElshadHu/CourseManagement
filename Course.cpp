#include "Course.h"
#include "Student.h"
#include "Professor.h"
namespace common {
    Course::Course(std::string_view courseName, std::string_view courseCode)
        : m_courseName(courseName), m_courseCode(courseCode) {}

    void Course::addStudent(std::weak_ptr<Student> student) {
        if (auto ptr = student.lock()) {
            for (auto& chosen : m_chosenStudents) {
                if (auto exist = chosen.lock()) {
                    if (ptr.get() == exist.get()) {
                        std::cout << "Student is already enrolled.\n";
                        return;
                    }
                }
            }
            m_chosenStudents.push_back(student);
        }
    }

    std::string Course::getCourseName() const { return m_courseName; }
    std::string Course::getCourseCode() const { return m_courseCode; }

    void Course::print() const {
        std::cout << "Course: " << m_courseName << " (" << m_courseCode << ")\n";
        std::cout << "Enrolled Students:\n";
        for (const auto& student : m_chosenStudents) {
            if (auto s = student.lock()) {
                std::cout << " - " << s->getName() << "\n";
            }
        }
        std::cout<<"Enrolled profs\n";
        for (const auto& professor : m_chosenProfessor) {
            if (auto p = professor.lock()) {
                std::cout << " - " << p->getName() << "\n";
            }
        }
    }

    void Course::addTeacher(std::weak_ptr<Professor> professor) {
        if (auto profPtr = professor.lock()) {
            for (const auto& existing : m_chosenProfessor) {
                if (auto existingProf = existing.lock()) {
                    if (existingProf.get() == profPtr.get()) {
                        std::cout << "Professor already added to course.\n";
                        return;
                    }
                }
            }
            m_chosenProfessor.push_back(professor);
        }
    }


    std::shared_ptr<Student> Course::findStudentById(std::string_view id) const{
        for(auto&weakStudent:m_chosenStudents){
            if(auto s = weakStudent.lock()){
                if(s->getId() == id){
                    return s;
                }
            }
        }
        return nullptr;
    }

}
