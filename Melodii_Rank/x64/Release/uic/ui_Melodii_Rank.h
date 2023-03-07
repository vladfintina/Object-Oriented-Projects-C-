/********************************************************************************
** Form generated from reading UI file 'Melodii_Rank.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MELODII_RANK_H
#define UI_MELODII_RANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Melodii_RankClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Melodii_RankClass)
    {
        if (Melodii_RankClass->objectName().isEmpty())
            Melodii_RankClass->setObjectName(QString::fromUtf8("Melodii_RankClass"));
        Melodii_RankClass->resize(600, 400);
        menuBar = new QMenuBar(Melodii_RankClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Melodii_RankClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Melodii_RankClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Melodii_RankClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Melodii_RankClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Melodii_RankClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Melodii_RankClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Melodii_RankClass->setStatusBar(statusBar);

        retranslateUi(Melodii_RankClass);

        QMetaObject::connectSlotsByName(Melodii_RankClass);
    } // setupUi

    void retranslateUi(QMainWindow *Melodii_RankClass)
    {
        Melodii_RankClass->setWindowTitle(QCoreApplication::translate("Melodii_RankClass", "Melodii_Rank", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Melodii_RankClass: public Ui_Melodii_RankClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MELODII_RANK_H
