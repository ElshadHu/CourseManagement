#pragma once
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include "DbManager.h"
#include <chrono>
#include <string_view>
// i am also using the singleton design pattern no matter how many times i call instance .db() i am getting the same instance
//here basically i use inline functions because i avoid multiple definition errors  and i implement them in the header
namespace serviceLayer{

//i dont need to wrtie everywhere QString for database and i convert them into QString i mean my cheap strings
    inline QString q(std::string_view s) {return QString::fromUtf8(s.data(),int(s.size()));}

    //because i am using some modern features of c++ qsqlite does not understand that is why i need to convert them into 64 bit integer
    inline qint64 ms(std::chrono::system_clock::time_point tp){
        return std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
    }
    //core entities

    inline bool addStudent(std::string_view id,std::string_view name,QString*err = nullptr){
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("INSERT INTO student(student_id,name) VALUES(?,?)");
        qy.addBindValue(q(id)); qy.addBindValue(q(name));
        if(!qy.exec()){if(err) *err = qy.lastError().text(); return false; }
        return true;
    }

    inline bool addProfessor(std::string_view id,std::string_view name,QString *err = nullptr){
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("INSERT INTO professor(prof_id,name) VALUES(?,?)");
        qy.addBindValue(q(id)); qy.addBindValue(q(name));
        if(!qy.exec()){ if(err) *err = qy.lastError().text(); return false; }
        return true;
    }


    inline bool addCourse(std::string_view code, std::string_view name, QString* err=nullptr) {
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("INSERT INTO course(course_code,name) VALUES(?,?)");
        qy.addBindValue(q(code)); qy.addBindValue(q(name));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return true;
    }

    inline bool enrollStudent(std::string_view sid, std::string_view code, QString* err=nullptr) {
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("INSERT INTO enrollment(student_id,course_code) VALUES(?,?)");
        qy.addBindValue(q(sid)); qy.addBindValue(q(code));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return true;
    }

    inline bool assignProfessor(std::string_view pid, std::string_view code, QString* err=nullptr) {
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("INSERT INTO teaches(prof_id,course_code) VALUES(?,?)");
        qy.addBindValue(q(pid)); qy.addBindValue(q(code));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return true;
    }


    inline bool addGradable(std::string_view actId,std::string_view courseCode,
                            std::string_view category,std::string_view title,
                            std::chrono::system_clock::time_point due,double total,
                            QString* err = nullptr){
        auto db = database::DbSimple::instance().db();
        QSqlQuery(db).exec("BEGIN");
        //activity,grade
        QSqlQuery a(db),g(db);

        a.prepare("INSERT INTO activity(activity_id,course_code,type,title,due_timestamp)"
                  " VALUES(?, ?, 'GRADABLE', ?, ?)");
        a.addBindValue(q(actId));
        a.addBindValue(q(courseCode));
        a.addBindValue(q(title));
        a.addBindValue(ms(due));
        if (!a.exec()) { if (err) *err = a.lastError().text(); QSqlQuery(db).exec("ROLLBACK"); return false; }

        g.prepare("INSERT INTO gradable_activity(activity_id,category,total) VALUES(?,?,?)");
        g.addBindValue(q(actId));
        g.addBindValue(q(category));
        g.addBindValue(total);
        if(!g.exec()){ if(err) *err = g.lastError().text(); QSqlQuery(db).exec("ROLLBACK"); return false; }
        QSqlQuery(db).exec("COMMIT");
        return true;
    }

    inline bool addAttendanceAct(std::string_view actId,std::string_view courseCode,
                                std::string_view title,std::chrono::system_clock::time_point when,
                                 QString* err = nullptr){

        auto db = database::DbSimple::instance().db();
        QSqlQuery(db).exec("BEGIN");
        //attendance status
        QSqlQuery a(db),s(db);
        a.prepare("INSERT INTO activity(activity_id,course_code,type,title,due_timestamp)"
                  " VALUES(?, ?, 'UNGRADABLE', ?, ?)") ;

        a.addBindValue(q(actId)); a.addBindValue(q(courseCode)); a.addBindValue(q(title)); a.addBindValue(ms(when));
        if (!a.exec()) { if (err) *err = a.lastError().text(); QSqlQuery(db).exec("ROLLBACK"); return false; }

        s.prepare("INSERT INTO attendance_activity(activity_id) VALUES(?)");
        s.addBindValue(q(actId));
        if (!s.exec()) { if (err) *err = s.lastError().text(); QSqlQuery(db).exec("ROLLBACK"); return false; }

        QSqlQuery(db).exec("COMMIT");
        return true;
    }

    inline bool markAttendance(std::string_view actId,std::string_view sid,std::string_view status,QString*err = nullptr){
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        //basically this will avoid the conflict for unique key which we will try to add the same student id and activity id instead
        //sqlite will override it
        qy.prepare("INSERT INTO attendance_mark(activity_id,student_id,status) VALUES(?,?,?) "
                   "ON CONFLICT(activity_id,student_id) DO UPDATE SET status=excluded.status");

        qy.addBindValue(q(actId)); qy.addBindValue(q(sid)); qy.addBindValue(q(status));//P, A  L
        if(!qy.exec()){ if(err) *err = qy.lastError().text(); return false; }
        return true;
    }

    inline bool addDiscussionAct(std::string_view actId,std::string_view courseCode,
                            std::string_view title,std::chrono::system_clock::time_point when,
                            QString* err = nullptr){
        auto db = database::DbSimple::instance().db();
        QSqlQuery(db).exec("BEGIN");
        QSqlQuery a(db),s(db);
        a.prepare("INSERT INTO activity(activity_id,course_code,type,title,due_timestamp)"
                  " VALUES(?, ?, 'UNGRADABLE', ?, ?)");
        a.addBindValue(q(actId)); a.addBindValue(q(courseCode)); a.addBindValue(q(title)); a.addBindValue(ms(when));
        if (!a.exec()) { if (err) *err = a.lastError().text(); QSqlQuery(db).exec("ROLLBACK"); return false; }
        s.prepare("INSERT INTO discussion_activity(activity_id) VALUES(?)");
        s.addBindValue(q(actId));
        if (!s.exec()) { if (err) *err = s.lastError().text(); QSqlQuery(db).exec("ROLLBACK"); return false; }

        QSqlQuery(db).exec("COMMIT");
        return true;
    }

    inline bool editActivityTitle(std::string_view actId,std::string_view newTitle,QString* err = nullptr){
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("UPDATE activity SET title=? WHERE activity_id=?");
        qy.addBindValue(q(newTitle)); qy.addBindValue(q(actId));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return qy.numRowsAffected() > 0;

    }


    inline bool editActivityDue(std::string_view actId, std::chrono::system_clock::time_point due, QString* err=nullptr) {
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("UPDATE activity SET due_timestamp=? WHERE activity_id=?");
        qy.addBindValue(ms(due)); qy.addBindValue(q(actId));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return qy.numRowsAffected() > 0;
    }

    inline bool setActivityTotal(std::string_view actId,double total,QString*err = nullptr){
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("UPDATE gradable_activity SET total=? WHERE activity_id=?");
        qy.addBindValue(total); qy.addBindValue(q(actId));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return qy.numRowsAffected() > 0;
    }

    inline bool gradeStudent(std::string_view actId, std::string_view sid, std::string_view letter, QString* err=nullptr) {
        auto db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("INSERT INTO grade(activity_id,student_id,grade,submitted_at)"
                   " VALUES(?,?,?, strftime('%s','now')*1000)"
                   " ON CONFLICT(activity_id,student_id) DO UPDATE SET "
                   "   grade=excluded.grade, submitted_at=excluded.submitted_at");
        qy.addBindValue(q(actId)); qy.addBindValue(q(sid)); qy.addBindValue(q(letter));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return true;
    }

}
