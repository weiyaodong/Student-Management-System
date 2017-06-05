/********************************************************************************
** Form generated from reading UI file 'studentmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTMAINWINDOW_H
#define UI_STUDENTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentMainWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StudentMainWindow)
    {
        if (StudentMainWindow->objectName().isEmpty())
            StudentMainWindow->setObjectName(QStringLiteral("StudentMainWindow"));
        StudentMainWindow->resize(400, 300);
        menuBar = new QMenuBar(StudentMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        StudentMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StudentMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        StudentMainWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(StudentMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        StudentMainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(StudentMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        StudentMainWindow->setStatusBar(statusBar);

        retranslateUi(StudentMainWindow);

        QMetaObject::connectSlotsByName(StudentMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StudentMainWindow)
    {
        StudentMainWindow->setWindowTitle(QApplication::translate("StudentMainWindow", "StudentMainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StudentMainWindow: public Ui_StudentMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTMAINWINDOW_H
