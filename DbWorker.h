#ifndef DBWORKER_H
#define DBWORKER_H
#include <QObject>
#include <QVector>
#include <QPair>
#include <QString>

namespace database{

class DbWorker:public QObject{
    Q_OBJECT
public:
    explicit DbWorker(QObject*parent = nullptr);

public slots:
    void open();//open per thread connection
    void addStudent(QString id,QString name);
    void listStudents();
signals:
    void ready();//emitted after open()success
    void error(QString message); //emitted on any SQL error
    void studentAdded(QString id,QString name);
    void studentListed(QVector<QPair<QString,QString>> rows);

};



}


#endif // DBWORKER_H
