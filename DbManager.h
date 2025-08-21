#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QSqlQuery>
#include <QThread>

namespace database
{
class DbManager{
    QString dbPath;
    DbManager() = default;
    ~DbManager() = default;
    DbManager(const DbManager&) = delete;
    DbManager&operator = (const DbManager&) = delete;

    //every thread must have its own connection when we write the addDatabase qsqlite and main   thw threads will fight over the same connection to avoid that we generate a unique name
    static QString threadConnectionName(){
        //unique name per thread
        return QString("conn-%1").arg((qulonglong)QThread::currentThreadId());
    }

    //WAL is good  for read and write and syncronous helps us do the thigns synchronouly here readers basically dont block the writers
    static void  applyingPragmas(QSqlDatabase&db){
        QSqlQuery qu(db);
        qu.exec("PRAGMA foreign_keys = ON;");
        qu.exec("PRAGMA journal_mode = WAL;");
        qu.exec("PRAGMA synchronous = NORMAL");
    }

    public:
    static DbManager&instance(){
        static DbManager man;
        return man;
    }
    //i will  call this once at startup to set the db file path
    void setPath(const QString& path){dbPath = path;}
   //get a connection boud to the current thread and creates and opens it first use in this thread.
    QSqlDatabase connection(){
        const auto name = threadConnectionName();
        if(QSqlDatabase::contains(name)){
            auto db = QSqlDatabase::database(name);
            if(db.isOpen()) return db;
            db.open();//if needed reopen it
            return db;
        }

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",name);
        db.setDatabaseName(dbPath);
        if(!db.open()){
            //we can return anyway because caller can read the lastError() from QSqlQuery
            return db;
        }
        applyingPragmas(db);
        return db;
    }

    //close and remove the current thread connection (thread finish)

    void closeThtreadCon(){
        const auto name  = threadConnectionName();
        if(QSqlDatabase::contains(name)){
            QSqlDatabase db = QSqlDatabase::database(name);
            if(db.isOpen()) db.close();
            QSqlDatabase::removeDatabase(name);
        }
    }
};


}

#endif
