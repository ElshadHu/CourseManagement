/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *icantseethest;
    QWidget *Student;
    QFormLayout *formLayout_3;
    QLabel *label_2;
    QLineEdit *lineEditStudentName;
    QLabel *label_3;
    QLineEdit *lineEditStudentId;
    QPushButton *pushButtonAddStudent;
    QWidget *Professor;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLineEdit *lineEditProfessorName;
    QLineEdit *lineEditProfessorId;
    QLabel *label_5;
    QPushButton *pushButton;
    QWidget *Course;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_6;
    QLineEdit *lineEditCourseName;
    QLabel *label_7;
    QLineEdit *lineEditCourseCode;
    QPushButton *addCourse;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        icantseethest = new QTabWidget(centralwidget);
        icantseethest->setObjectName("icantseethest");
        icantseethest->setGeometry(QRect(230, 30, 205, 164));
        Student = new QWidget();
        Student->setObjectName("Student");
        formLayout_3 = new QFormLayout(Student);
        formLayout_3->setObjectName("formLayout_3");
        label_2 = new QLabel(Student);
        label_2->setObjectName("label_2");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::SpanningRole, label_2);

        lineEditStudentName = new QLineEdit(Student);
        lineEditStudentName->setObjectName("lineEditStudentName");

        formLayout_3->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditStudentName);

        label_3 = new QLabel(Student);
        label_3->setObjectName("label_3");

        formLayout_3->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        lineEditStudentId = new QLineEdit(Student);
        lineEditStudentId->setObjectName("lineEditStudentId");

        formLayout_3->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEditStudentId);

        pushButtonAddStudent = new QPushButton(Student);
        pushButtonAddStudent->setObjectName("pushButtonAddStudent");

        formLayout_3->setWidget(4, QFormLayout::ItemRole::SpanningRole, pushButtonAddStudent);

        icantseethest->addTab(Student, QString());
        Professor = new QWidget();
        Professor->setObjectName("Professor");
        formLayout_2 = new QFormLayout(Professor);
        formLayout_2->setObjectName("formLayout_2");
        label_4 = new QLabel(Professor);
        label_4->setObjectName("label_4");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, label_4);

        lineEditProfessorName = new QLineEdit(Professor);
        lineEditProfessorName->setObjectName("lineEditProfessorName");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditProfessorName);

        lineEditProfessorId = new QLineEdit(Professor);
        lineEditProfessorId->setObjectName("lineEditProfessorId");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditProfessorId);

        label_5 = new QLabel(Professor);
        label_5->setObjectName("label_5");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::SpanningRole, label_5);

        pushButton = new QPushButton(Professor);
        pushButton->setObjectName("pushButton");

        formLayout_2->setWidget(3, QFormLayout::ItemRole::SpanningRole, pushButton);

        icantseethest->addTab(Professor, QString());
        Course = new QWidget();
        Course->setObjectName("Course");
        layoutWidget = new QWidget(Course);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 10, 191, 111));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(7);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_6);

        lineEditCourseName = new QLineEdit(layoutWidget);
        lineEditCourseName->setObjectName("lineEditCourseName");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditCourseName);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_7);

        lineEditCourseCode = new QLineEdit(layoutWidget);
        lineEditCourseCode->setObjectName("lineEditCourseCode");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditCourseCode);

        addCourse = new QPushButton(layoutWidget);
        addCourse->setObjectName("addCourse");

        formLayout->setWidget(2, QFormLayout::ItemRole::SpanningRole, addCourse);

        icantseethest->addTab(Course, QString());
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(290, 10, 161, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        icantseethest->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Name:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        pushButtonAddStudent->setText(QCoreApplication::translate("MainWindow", "Add Student", nullptr));
        icantseethest->setTabText(icantseethest->indexOf(Student), QCoreApplication::translate("MainWindow", "Student", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "name:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Add Professor", nullptr));
        icantseethest->setTabText(icantseethest->indexOf(Professor), QCoreApplication::translate("MainWindow", "Professor", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "name:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Code:", nullptr));
        addCourse->setText(QCoreApplication::translate("MainWindow", "Add Course", nullptr));
        icantseethest->setTabText(icantseethest->indexOf(Course), QCoreApplication::translate("MainWindow", "Course", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Student/Professor/Course", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
