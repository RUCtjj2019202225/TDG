/********************************************************************************
** Form generated from reading UI file 'mw1.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MW1_H
#define UI_MW1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MW1
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MW1)
    {
        if (MW1->objectName().isEmpty())
            MW1->setObjectName(QString::fromUtf8("MW1"));
        MW1->resize(1023, 937);
        centralwidget = new QWidget(MW1);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MW1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MW1);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1023, 29));
        MW1->setMenuBar(menubar);
        statusbar = new QStatusBar(MW1);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MW1->setStatusBar(statusbar);

        retranslateUi(MW1);

        QMetaObject::connectSlotsByName(MW1);
    } // setupUi

    void retranslateUi(QMainWindow *MW1)
    {
        MW1->setWindowTitle(QCoreApplication::translate("MW1", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MW1: public Ui_MW1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MW1_H
