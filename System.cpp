#include "System.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "ServiceLayer.h"
#include "QString"

//that is for internal helper functions
namespace {//i never need to declare this namespace  that is why it does not have a name
    std::shared_ptr<common::Student>
    findStudentById(std::vector<std::shared_ptr<common::Student>>&stud,std::string_view id){
        for(auto&s:stud){
            if(s->getId() == id) return s;
        }
        return nullptr;
    }

    std::shared_ptr<common::Course>
    findCourseByCode(std::vector<std::shared_ptr<common::Course>>& v, std::string_view code) {
        for (auto& c : v) if (c->getCourseCode() == code) return c;
        return nullptr;
    }

    std::shared_ptr<common::Professor>
    findProfessorById(std::vector<std::shared_ptr<common::Professor>>& v, std::string_view id) {
        for (auto& p : v) if (p->getId() == id) return p;
        return nullptr;
    }

}
namespace common {

void System::addStudent(std::string_view studentName,std::string_view student_id){
    if(findStudentById(colOfStudents,student_id)){
        std::cout<<"Student already exists\n";
        return;
    }
    QString err;

    if(!serviceLayer::addStudent(student_id,studentName,&err)){
        std::cerr<<"Db error addStudent()"<<err.toStdString()<<'\n';
        return;
    }

    colOfStudents.push_back(std::make_shared<Student>(studentName,student_id));
}


void System::addCourse(std::string_view courseName,std::string_view courseCode){
    if(findCourseByCode(colOfCourses,courseCode)){
        std::cout<<"Course already exists\n";
        return;
    }

    QString err;
    if(!serviceLayer::addCourse(courseCode,courseName,&err)){
        std::cerr<<"db error addCourse()"<<err.toStdString()<<'\n';
    }

    colOfCourses.push_back(std::make_shared<Course>(courseName,courseCode));

}

void System::addProfessor(std::string_view profName, std::string_view profId) {
    if (findProfessorById(colOfProfessors, profId)) {
        std::cout << "Professor already exists: " << profId << "\n";
        return;
    }
    QString err;
    if (!serviceLayer::addProfessor(profId, profName, &err)) {
        std::cerr << "DB error (addProfessor): " << err.toStdString() << "\n";
        return;
    }
    colOfProfessors.push_back(std::make_shared<Professor>(profName, profId));
}

void System::enrollStudentInCourse(std::string_view student_id,std::string_view course_code){
    auto student = findStudentById(colOfStudents,student_id);
    auto course = findCourseByCode(colOfCourses,course_code);

    if(!student || !course){
        std::cout<<"Either student or course not found\n";
        return;
    }
    QString err;
    if(!serviceLayer::enrollStudent(student_id,course_code,&err)){
         std::cerr << "DB error (enrollStudent): " << err.toStdString() << "\n";
    }

    student->addCourse(course);
    course->addStudent(student);

}

void System::enrollProfessorInCourse(std::string_view prof_id, std::string_view course_code) {
    auto prof  = findProfessorById(colOfProfessors, prof_id);
    auto course= findCourseByCode(colOfCourses,  course_code);
    if (!prof || !course) { std::cout << "Either professor or course not found\n"; return; }

    QString err;
    if (!serviceLayer::assignProfessor(prof_id, course_code, &err)) {
        std::cerr << "DB error (assignProfessor): " << err.toStdString() << "\n";
        // still perform idempotent in-memory link
    }

    prof->assignCourse(course);
    course->addTeacher(prof);
}

}











































