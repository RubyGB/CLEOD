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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_McleodIDE
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuProject;
    QMenu *menuView;
    QMenu *menuEdit;
    QMenu *menuDebugger;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *McleodIDE)
    {
        if (McleodIDE->objectName().isEmpty())
            McleodIDE->setObjectName(QStringLiteral("McleodIDE"));
        McleodIDE->resize(677, 375);
        centralwidget = new QWidget(McleodIDE);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(50, 20, 571, 281));
        McleodIDE->setCentralWidget(centralwidget);
        menubar = new QMenuBar(McleodIDE);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 677, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuProject = new QMenu(menubar);
        menuProject->setObjectName(QStringLiteral("menuProject"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuDebugger = new QMenu(menubar);
        menuDebugger->setObjectName(QStringLiteral("menuDebugger"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        McleodIDE->setMenuBar(menubar);
        statusbar = new QStatusBar(McleodIDE);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        McleodIDE->setStatusBar(statusbar);
        toolBar = new QToolBar(McleodIDE);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        McleodIDE->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuProject->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuDebugger->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(McleodIDE);

        QMetaObject::connectSlotsByName(McleodIDE);
    } // setupUi

    void retranslateUi(QMainWindow *McleodIDE)
    {
        McleodIDE->setWindowTitle(QApplication::translate("McleodIDE", "McleodIDE", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("McleodIDE", "File", Q_NULLPTR));
        menuProject->setTitle(QApplication::translate("McleodIDE", "Project", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("McleodIDE", "View", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("McleodIDE", "Edit", Q_NULLPTR));
        menuDebugger->setTitle(QApplication::translate("McleodIDE", "Debugger", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("McleodIDE", "Window", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("McleodIDE", "Help", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("McleodIDE", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class McleodIDE: public Ui_McleodIDE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MCLEODIDE_H
