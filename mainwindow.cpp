#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
// #include <iostream>
 // using namespace common;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddStudent_clicked()
{
    QString name = ui->lineEditStudentName->text();
    QString id = ui->lineEditStudentId->text();
    if(!name.isEmpty() && !id.isEmpty())
    {
        system.addStudent(name.toStdString(),id.toStdString());
  QMessageBox::information(this,"Success"," Student added Successfuly");
        ui->lineEditStudentName->clear();
        ui ->lineEditStudentId->clear();
    }
    else
    {
        QMessageBox::warning(this,"Input error","Please fill in all fields");
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString name = ui->lineEditProfessorName->text();
    QString id = ui->lineEditProfessorId->text();
    if(!name.isEmpty() && !id.isEmpty())
    {
        system.addProfessor(name.toStdString(),id.toStdString());
          QMessageBox::information(this,"Success"," Student added Successfuly");
        ui->lineEditProfessorName->clear();
        ui->lineEditProfessorId->clear();
    }
    else
    {
        QMessageBox::warning(this,"Input error","Please fill in all fields");
    }

}


void MainWindow::on_addCourse_clicked()
{
    QString name = ui->lineEditCourseName->text();
    QString id = ui->lineEditCourseCode->text();

    if(!name.isEmpty() && !id.isEmpty())
    {
        system.addCourse(name.toStdString(),id.toStdString());
         QMessageBox::information(this,"Success"," Student added Successfuly");
        ui->lineEditCourseName->clear();
        ui->lineEditCourseCode->clear();
    }
    else
    {
        QMessageBox::warning(this,"Input error","Please fill in all fields");
    }
}


