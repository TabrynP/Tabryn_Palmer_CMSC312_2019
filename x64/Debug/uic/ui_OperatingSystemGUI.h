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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperatingSystemGUI
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTableWidget *runningWidget;
    QTableWidget *schedulerWidget;
    QLineEdit *runningTableName;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *schedulerTitle;
    QLineEdit *processTableName;
    QTableWidget *processWidget;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *OperatingSystemGUI)
    {
        if (OperatingSystemGUI->objectName().isEmpty())
            OperatingSystemGUI->setObjectName(QString::fromUtf8("OperatingSystemGUI"));
        OperatingSystemGUI->resize(1458, 1127);
        gridLayoutWidget = new QWidget(OperatingSystemGUI);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 10, 1401, 1031));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        runningWidget = new QTableWidget(gridLayoutWidget);
        runningWidget->setObjectName(QString::fromUtf8("runningWidget"));

        gridLayout->addWidget(runningWidget, 7, 0, 1, 1);

        schedulerWidget = new QTableWidget(gridLayoutWidget);
        schedulerWidget->setObjectName(QString::fromUtf8("schedulerWidget"));

        gridLayout->addWidget(schedulerWidget, 7, 2, 1, 1);

        runningTableName = new QLineEdit(gridLayoutWidget);
        runningTableName->setObjectName(QString::fromUtf8("runningTableName"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        runningTableName->setFont(font);
        runningTableName->setAlignment(Qt::AlignCenter);
        runningTableName->setReadOnly(true);

        gridLayout->addWidget(runningTableName, 6, 0, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 9, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 8, 0, 1, 3);

        schedulerTitle = new QLineEdit(gridLayoutWidget);
        schedulerTitle->setObjectName(QString::fromUtf8("schedulerTitle"));
        schedulerTitle->setFont(font);
        schedulerTitle->setAlignment(Qt::AlignCenter);
        schedulerTitle->setReadOnly(true);

        gridLayout->addWidget(schedulerTitle, 6, 2, 1, 1);

        processTableName = new QLineEdit(gridLayoutWidget);
        processTableName->setObjectName(QString::fromUtf8("processTableName"));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        processTableName->setFont(font1);
        processTableName->setAlignment(Qt::AlignCenter);
        processTableName->setReadOnly(true);

        gridLayout->addWidget(processTableName, 0, 0, 1, 3);

        processWidget = new QTableWidget(gridLayoutWidget);
        processWidget->setObjectName(QString::fromUtf8("processWidget"));

        gridLayout->addWidget(processWidget, 4, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 0, 1, 3);


        retranslateUi(OperatingSystemGUI);

        QMetaObject::connectSlotsByName(OperatingSystemGUI);
    } // setupUi

    void retranslateUi(QWidget *OperatingSystemGUI)
    {
        OperatingSystemGUI->setWindowTitle(QApplication::translate("OperatingSystemGUI", "QtGuiApplication3", nullptr));
        runningTableName->setText(QApplication::translate("OperatingSystemGUI", "Currently Running Processes", nullptr));
        lineEdit->setText(QString());
        schedulerTitle->setText(QApplication::translate("OperatingSystemGUI", "Processes In Scheduler", nullptr));
        processTableName->setText(QApplication::translate("OperatingSystemGUI", "All Initialized Processes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OperatingSystemGUI: public Ui_OperatingSystemGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATINGSYSTEMGUI_H
