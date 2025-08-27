#include "serviceLayerActivity.h"
#include "ActivityTypes.h"
#include "DbManager.h"
#include <QSqlQuery>
#include <QSqlError>
using namespace activities;
    static qint64 to_ms(std::chrono::system_clock::time_point tp){
        return std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
    }
    inline QString q(std::string_view s) {return QString::fromUtf8(s.data(),int(s.size()));}

namespace serviceLayer::activity {

    bool add(std::string_view id,std::string_view course,activities::ActivityType type,
             std::string_view title,std::chrono::system_clock::time_point due,
             std::optional <double> totalIfGradable,QString *err){

        auto&db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        //this is kind of stype is important espescially if my strings have some special characters
        qy.prepare(R"SQL(INSERT INTO activity(activity_id,course_code,type,title,due_timestamp,total) VALUES(?,?,?,?,?,?))SQL");
        qy.addBindValue(q(id));
        qy.addBindValue(q(course));
       qy.addBindValue(QString::fromUtf8(to_string(type).data()));
        qy.addBindValue(q(title)) ;
       qy.addBindValue(to_ms(due));
        if(totalIfGradable) qy.addBindValue(*totalIfGradable);
        else qy.addBindValue(QVariant(QVariant::Double));//NULL for ungradable
        if(!qy.exec()){  if(err) *err = qy.lastError().text(); return false; }
        return true;
    }


    bool rename(std::string_view id,std::string_view newTitle,QString*err){
        auto&db = database::DbSimple::instance().db();
         QSqlQuery qy(db);
        qy.prepare("UPDATE activity SET title=? WHERE activity_id=?");
         qy.addBindValue(q(newTitle));
        qy.addBindValue(q(id));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return qy.numRowsAffected() > 0;
    }


    bool reschedule(std::string_view id, std::chrono::system_clock::time_point due, QString* err) {
        auto& db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare("UPDATE activity SET due_timestamp=? WHERE activity_id=?");
        qy.addBindValue(to_ms(due));
        qy.addBindValue(q(id));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return qy.numRowsAffected() > 0;
    }

    bool grade(std::string_view id,std::string_view studentId,Grade g,QString*err){
        auto &db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare(R"SQL(
        INSERT INTO grade(activity_id, student_id, grade, submitted_at)
        VALUES(?,?,?,strftime('%s','now')*1000)
        ON CONFLICT(activity_id, student_id) DO UPDATE SET
            grade=excluded.grade, submitted_at=excluded.submitted_at
    )SQL");

        qy.addBindValue(q(id));
        qy.addBindValue(q(studentId));
        qy.addBindValue(QString::fromUtf8(to_string(g).data()));          // enum -> TEXT
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return true;
    }

    bool markAttendance(std::string_view id, std::string_view studentId, activities::AttendanceStatus s, QString* err){
        auto& db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare(R"SQL(INSERT INTO attendance_mark(activity_id,student_id,status) VALUES(?,?,?)
            ON CONLICT (activity_id,student_id) DO UPDATE SET status = excluded.status)SQL");
        qy.addBindValue(q(id));
        qy.addBindValue(q(studentId));
        qy.addBindValue(QString::fromUtf8(to_string(s).data()));
        if (!qy.exec()) { if (err) *err = qy.lastError().text(); return false; }
        return true;

    }

    QSqlQueryModel* modelCourseActivities(std::string_view course){
        auto*m = new QSqlQueryModel();
        auto& db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare(R"SQL(SELECT activity_id,title,type,due_timestamp,total
                FROM activity
    WHERE course_code = ?
    ORDER BY due_timestamp)SQL");
        qy.addBindValue(q(course));
        qy.exec();
        //do i have to pass via move?
        m->setQuery(qy);
        return m;
    }

    QSqlQueryModel* modelStudentGrades(std::string_view studentId,std::string_view course){
        auto* m = new QSqlQueryModel();
        auto&db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare(R"SQL(SELECT a.title,g.grade,g.submitted_at,a.total
                FROM grade g
                JOIN activity a ON  a.activity_id = g.activity_id
                    WHERE g.student_id = ? AND a.course_code = ?
                    ORDER BY a.due_timestamp)SQL");
        qy.addBindValue(q(studentId));
        qy.addBindValue(q(course));
        qy.exec();
        m->setQuery(qy);
        return m;
    }

    QSqlQueryModel* modelStudentAttendance(std::string_view studentId,std::string_view course){
        auto *m = new QSqlQueryModel();
        auto&db = database::DbSimple::instance().db();
        QSqlQuery qy(db);
        qy.prepare(R"SQL(SELECT a.title,status
                            FROM attendance_mark am
                    JOIN activity a ON a.activity_id = am.activity_id
                    WHERE am.student_id = ? AND a.course_code = ?
                            ORDER BY a.due_timestamp)SQL");
        qy.addBindValue(q(studentId));
        qy.addBindValue(q(course));
        qy.exec();
        m->setQuery(qy);
        return m;



    }

}
