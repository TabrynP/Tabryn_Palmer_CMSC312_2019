/********************************************************************************
** Form generated from reading UI file 'OperatingSystemGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATINGSYSTEMGUI_H
#define UI_OPERATINGSYSTEMGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperatingSystemGUIClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OperatingSystemGUIClass)
    {
        if (OperatingSystemGUIClass->objectName().isEmpty())
            OperatingSystemGUIClass->setObjectName(QString::fromUtf8("OperatingSystemGUIClass"));
        OperatingSystemGUIClass->resize(1535, 1131);
        centralWidget = new QWidget(OperatingSystemGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 1010, 1491, 41));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 530, 721, 461));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(780, 530, 721, 461));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 0, 1491, 521));
        OperatingSystemGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OperatingSystemGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1535, 22));
        OperatingSystemGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OperatingSystemGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OperatingSystemGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OperatingSystemGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OperatingSystemGUIClass->setStatusBar(statusBar);

        retranslateUi(OperatingSystemGUIClass);

        QMetaObject::connectSlotsByName(OperatingSystemGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *OperatingSystemGUIClass)
    {
        OperatingSystemGUIClass->setWindowTitle(QApplication::translate("OperatingSystemGUIClass", "OperatingSystemGUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OperatingSystemGUIClass: public Ui_OperatingSystemGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATINGSYSTEMGUI_H
