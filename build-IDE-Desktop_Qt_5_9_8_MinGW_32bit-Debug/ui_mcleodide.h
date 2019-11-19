/********************************************************************************
** Form generated from reading UI file 'mcleodide.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MCLEODIDE_H
#define UI_MCLEODIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            McleodIDE->setObjectName(QStringLiteral("McleodIDE"));
        McleodIDE->resize(728, 486);
        centralwidget = new QWidget(McleodIDE);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        McleodIDE->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(McleodIDE);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        McleodIDE->setStatusBar(statusbar);
        toolBar = new QToolBar(McleodIDE);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        McleodIDE->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar = new QMenuBar(McleodIDE);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 728, 22));
        McleodIDE->setMenuBar(menubar);

        retranslateUi(McleodIDE);

        QMetaObject::connectSlotsByName(McleodIDE);
    } // setupUi

    void retranslateUi(QMainWindow *McleodIDE)
    {
        McleodIDE->setWindowTitle(QApplication::translate("McleodIDE", "McleodIDE", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("McleodIDE", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class McleodIDE: public Ui_McleodIDE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MCLEODIDE_H
