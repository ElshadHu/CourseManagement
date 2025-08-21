#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString dbPath = QCoreApplication::applicationDirPath() + "/oopcms.db";
    qDebug() << "Using DB path:" << dbPath;
    MainWindow w;
    w.show();

    return a.exec();
}
