/********************************************************************************
** Form generated from reading UI file 'Muzica_faraRank.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUZICA_FARARANK_H
#define UI_MUZICA_FARARANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Muzica_faraRankClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Muzica_faraRankClass)
    {
        if (Muzica_faraRankClass->objectName().isEmpty())
            Muzica_faraRankClass->setObjectName(QString::fromUtf8("Muzica_faraRankClass"));
        Muzica_faraRankClass->resize(600, 400);
        menuBar = new QMenuBar(Muzica_faraRankClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Muzica_faraRankClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Muzica_faraRankClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Muzica_faraRankClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Muzica_faraRankClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Muzica_faraRankClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Muzica_faraRankClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Muzica_faraRankClass->setStatusBar(statusBar);

        retranslateUi(Muzica_faraRankClass);

        QMetaObject::connectSlotsByName(Muzica_faraRankClass);
    } // setupUi

    void retranslateUi(QMainWindow *Muzica_faraRankClass)
    {
        Muzica_faraRankClass->setWindowTitle(QCoreApplication::translate("Muzica_faraRankClass", "Muzica_faraRank", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Muzica_faraRankClass: public Ui_Muzica_faraRankClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUZICA_FARARANK_H
