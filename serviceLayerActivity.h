#ifndef SERVICELAYERACTIVITY_H
#define SERVICELAYERACTIVITY_H
#include <QString>
#include<chrono>
#include<optional>
#include <string_view>
#include <QSqlQueryModel>

#include "ActivityTypes.h"

    namespace serviceLayer::activity {

    //professors use these apis
    bool add(std::string_view id,std::string_view course,activities::ActivityType type,
             std::string_view title,std::chrono::system_clock::time_point due,
             std::optional <double> totalIfGradable,QString *err = nullptr);
    bool rename(std::string_view id,std::string_view newTitle,QString*err =nullptr);
    bool reschedule(std::string_view id,std::chrono::system_clock::time_point,QString*err);
    bool grade(std::string_view id, std::string_view studentId, activities::Grade g, QString* err = nullptr);
    bool markAttendance(std::string_view id, std::string_view studentId, activities::AttendanceStatus s, QString* err = nullptr);


    //read Apis student/UI use these; return ready to bind models
    QSqlQueryModel* modelCourseActivities(std::string_view course);
    QSqlQueryModel* modelStudentGrades(std::string_view studentId,std::string_view course);
    QSqlQueryModel* modelStudentAttendance(std::string_view studentId,std::string_view course);




    }

#endif // SERVICELAYERACTIVITY_H
