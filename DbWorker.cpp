#include "DbWorker.h"
#include "DbManager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace database{
DbWorker::DbWorker(QObject* parent) : QObject(parent) {}
void DbWorker::open(){
    //obtainging a connection bound to this thread
    auto db = database::DbManager::instance().connection();
    if(!db.isOpen()){
        emit error(QStringLiteral("DB open Failed : %1").arg(db.lastError().text()));
        return;
    }
    emit ready();
}

void DbWorker::addStudent(QString id,QString name){
    auto db = database::DbManager::instance().connection();
    QSqlQuery qu(db);
    qu.prepare(QStringLiteral("INSERT INTO student(student_id,name) VALUES(?,?)"));
    qu.addBindValue(id);
    qu.addBindValue(name);
    if(!qu.exec()){
               emit error(QStringLiteral("addStudent Failed : %1").arg(db.lastError().text()));
        return;
    }
    emit studentAdded(id,name);
}
void DbWorker::listStudents(){
    auto db = database::DbManager::instance().connection();
    QVector<QPair<QString,QString>> rows;
    QSqlQuery q(QStringLiteral("SELECT student_id, name FROM student ORDER BY student_id"), db);
    while (q.next()) {
        rows.push_back({ q.value(0).toString(), q.value(1).toString() });
    }
    // (If q.exec() had failed, while() wouldn’t iterate; you could also check q.lastError())
    emit studentListed(rows);
}

}
