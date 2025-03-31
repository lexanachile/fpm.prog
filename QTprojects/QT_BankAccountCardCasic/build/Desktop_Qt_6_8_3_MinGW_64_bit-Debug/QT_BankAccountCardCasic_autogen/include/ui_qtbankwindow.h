/********************************************************************************
** Form generated from reading UI file 'qtbankwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTBANKWINDOW_H
#define UI_QTBANKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTBankWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QTBankWindow)
    {
        if (QTBankWindow->objectName().isEmpty())
            QTBankWindow->setObjectName("QTBankWindow");
        QTBankWindow->resize(800, 600);
        centralwidget = new QWidget(QTBankWindow);
        centralwidget->setObjectName("centralwidget");
        QTBankWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QTBankWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        QTBankWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(QTBankWindow);
        statusbar->setObjectName("statusbar");
        QTBankWindow->setStatusBar(statusbar);

        retranslateUi(QTBankWindow);

        QMetaObject::connectSlotsByName(QTBankWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QTBankWindow)
    {
        QTBankWindow->setWindowTitle(QCoreApplication::translate("QTBankWindow", "QTBankWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTBankWindow: public Ui_QTBankWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTBANKWINDOW_H
