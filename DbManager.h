#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
namespace database{

class DbSimple{
    QSqlDatabase db_;
    DbSimple() = default;
    ~DbSimple(){if(db_.isOpen()) db_.close();};
    DbSimple(const DbSimple&) = delete;
    DbSimple& operator = (const DbSimple&) = delete;

public:
    static DbSimple& instance(){
        static DbSimple s; return s;
    }

    bool open( const QString& path){
        if(db_.isOpen()) return true;
        db_ = QSqlDatabase::addDatabase("QSQLITE","main");
        db_.setDatabaseName(path);
        if(!db_.isOpen()) return false;
        QSqlQuery q(db_);
        q.exec("PRAGMA foreign_keys = On;");
        q.exec("PRAGMA journal_mode = WAL;");
        q.exec("PRAGMA synchronous = NORMAL;");
        return true;
    }
    QSqlDatabase& db(){return db_;}

};



}

#endif // DBMANAGER_H
