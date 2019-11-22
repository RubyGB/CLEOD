/********************************************************************************
** Form generated from reading UI file 'mcleodide.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MCLEODIDE_H
#define UI_MCLEODIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_McleodIDE
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *McleodIDE)
    {
        if (McleodIDE->objectName().isEmpty())
            McleodIDE->setObjectName(QString::fromUtf8("McleodIDE"));
        McleodIDE->resize(728, 486);
        centralwidget = new QWidget(McleodIDE);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        McleodIDE->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(McleodIDE);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        McleodIDE->setStatusBar(statusbar);
        toolBar = new QToolBar(McleodIDE);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        McleodIDE->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar = new QMenuBar(McleodIDE);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 728, 25));
        McleodIDE->setMenuBar(menubar);

        retranslateUi(McleodIDE);

        QMetaObject::connectSlotsByName(McleodIDE);
    } // setupUi

    void retranslateUi(QMainWindow *McleodIDE)
    {
        McleodIDE->setWindowTitle(QCoreApplication::translate("McleodIDE", "McleodIDE", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("McleodIDE", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class McleodIDE: public Ui_McleodIDE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MCLEODIDE_H
