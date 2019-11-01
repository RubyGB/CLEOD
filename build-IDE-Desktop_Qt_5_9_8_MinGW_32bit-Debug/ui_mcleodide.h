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
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionRestart;
    QAction *actionExit;
    QAction *actionOpen_Project;
    QAction *actionClose_Porject;
    QAction *actionBuild;
    QAction *actionRun;
    QAction *actionRun_Project;
    QAction *actionBuild_and_Run_Project;
    QAction *actionRun_Project_2;
    QAction *actionBuild_and_Run_Project_2;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFind_Word;
    QAction *actionFine_Replace;
    QAction *actionDelete;
    QAction *actionNew_Window;
    QAction *actionWelcome;
    QAction *actionMcleod_Documentation;
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuProject;
    QMenu *menuEdit;
    QMenu *menuDebugger;
    QMenu *menuWindow;
    QMenu *menuHelp;

    void setupUi(QMainWindow *McleodIDE)
    {
        if (McleodIDE->objectName().isEmpty())
            McleodIDE->setObjectName(QStringLiteral("McleodIDE"));
        McleodIDE->resize(677, 375);
        actionNew = new QAction(McleodIDE);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(McleodIDE);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(McleodIDE);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(McleodIDE);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionRestart = new QAction(McleodIDE);
        actionRestart->setObjectName(QStringLiteral("actionRestart"));
        actionExit = new QAction(McleodIDE);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOpen_Project = new QAction(McleodIDE);
        actionOpen_Project->setObjectName(QStringLiteral("actionOpen_Project"));
        actionClose_Porject = new QAction(McleodIDE);
        actionClose_Porject->setObjectName(QStringLiteral("actionClose_Porject"));
        actionBuild = new QAction(McleodIDE);
        actionBuild->setObjectName(QStringLiteral("actionBuild"));
        actionRun = new QAction(McleodIDE);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionRun_Project = new QAction(McleodIDE);
        actionRun_Project->setObjectName(QStringLiteral("actionRun_Project"));
        actionBuild_and_Run_Project = new QAction(McleodIDE);
        actionBuild_and_Run_Project->setObjectName(QStringLiteral("actionBuild_and_Run_Project"));
        actionRun_Project_2 = new QAction(McleodIDE);
        actionRun_Project_2->setObjectName(QStringLiteral("actionRun_Project_2"));
        actionBuild_and_Run_Project_2 = new QAction(McleodIDE);
        actionBuild_and_Run_Project_2->setObjectName(QStringLiteral("actionBuild_and_Run_Project_2"));
        actionUndo = new QAction(McleodIDE);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/rec/icons/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon);
        actionRedo = new QAction(McleodIDE);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/rec/icons/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon1);
        actionCut = new QAction(McleodIDE);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(McleodIDE);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(McleodIDE);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionFind_Word = new QAction(McleodIDE);
        actionFind_Word->setObjectName(QStringLiteral("actionFind_Word"));
        actionFine_Replace = new QAction(McleodIDE);
        actionFine_Replace->setObjectName(QStringLiteral("actionFine_Replace"));
        actionDelete = new QAction(McleodIDE);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        actionNew_Window = new QAction(McleodIDE);
        actionNew_Window->setObjectName(QStringLiteral("actionNew_Window"));
        actionWelcome = new QAction(McleodIDE);
        actionWelcome->setObjectName(QStringLiteral("actionWelcome"));
        actionMcleod_Documentation = new QAction(McleodIDE);
        actionMcleod_Documentation->setObjectName(QStringLiteral("actionMcleod_Documentation"));
        centralwidget = new QWidget(McleodIDE);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(50, 20, 571, 281));
        McleodIDE->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(McleodIDE);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        McleodIDE->setStatusBar(statusbar);
        toolBar = new QToolBar(McleodIDE);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        McleodIDE->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar = new QMenuBar(McleodIDE);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 677, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuProject = new QMenu(menubar);
        menuProject->setObjectName(QStringLiteral("menuProject"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuDebugger = new QMenu(menubar);
        menuDebugger->setObjectName(QStringLiteral("menuDebugger"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        McleodIDE->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuProject->menuAction());
        menubar->addAction(menuDebugger->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionRestart);
        menuFile->addAction(actionExit);
        menuProject->addAction(actionOpen_Project);
        menuProject->addAction(actionClose_Porject);
        menuProject->addSeparator();
        menuProject->addAction(actionRun);
        menuProject->addAction(actionRun_Project_2);
        menuProject->addAction(actionBuild_and_Run_Project_2);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionFind_Word);
        menuEdit->addAction(actionFine_Replace);
        menuEdit->addSeparator();
        menuWindow->addAction(actionNew_Window);
        menuHelp->addAction(actionWelcome);
        menuHelp->addAction(actionMcleod_Documentation);

        retranslateUi(McleodIDE);

        QMetaObject::connectSlotsByName(McleodIDE);
    } // setupUi

    void retranslateUi(QMainWindow *McleodIDE)
    {
        McleodIDE->setWindowTitle(QApplication::translate("McleodIDE", "McleodIDE", Q_NULLPTR));
        actionNew->setText(QApplication::translate("McleodIDE", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("McleodIDE", "Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("McleodIDE", "Save", Q_NULLPTR));
        actionSave_as->setText(QApplication::translate("McleodIDE", "Save as", Q_NULLPTR));
        actionRestart->setText(QApplication::translate("McleodIDE", "Restart", Q_NULLPTR));
        actionExit->setText(QApplication::translate("McleodIDE", "Exit", Q_NULLPTR));
        actionOpen_Project->setText(QApplication::translate("McleodIDE", "Open Project", Q_NULLPTR));
        actionClose_Porject->setText(QApplication::translate("McleodIDE", "Close Project", Q_NULLPTR));
        actionBuild->setText(QApplication::translate("McleodIDE", "Save Project", Q_NULLPTR));
        actionRun->setText(QApplication::translate("McleodIDE", "Build Project", Q_NULLPTR));
        actionRun_Project->setText(QApplication::translate("McleodIDE", "Run Project", Q_NULLPTR));
        actionBuild_and_Run_Project->setText(QApplication::translate("McleodIDE", "Build and Run Project", Q_NULLPTR));
        actionRun_Project_2->setText(QApplication::translate("McleodIDE", "Run Project", Q_NULLPTR));
        actionBuild_and_Run_Project_2->setText(QApplication::translate("McleodIDE", "Build and Run Project", Q_NULLPTR));
        actionUndo->setText(QApplication::translate("McleodIDE", "Undo", Q_NULLPTR));
        actionRedo->setText(QApplication::translate("McleodIDE", "Redo", Q_NULLPTR));
        actionCut->setText(QApplication::translate("McleodIDE", "Cut", Q_NULLPTR));
        actionCopy->setText(QApplication::translate("McleodIDE", "Copy", Q_NULLPTR));
        actionPaste->setText(QApplication::translate("McleodIDE", "Paste", Q_NULLPTR));
        actionFind_Word->setText(QApplication::translate("McleodIDE", "Find Word", Q_NULLPTR));
        actionFine_Replace->setText(QApplication::translate("McleodIDE", "Fine/Replace", Q_NULLPTR));
        actionDelete->setText(QApplication::translate("McleodIDE", "Delete", Q_NULLPTR));
        actionNew_Window->setText(QApplication::translate("McleodIDE", "New Window", Q_NULLPTR));
        actionWelcome->setText(QApplication::translate("McleodIDE", "Welcome", Q_NULLPTR));
        actionMcleod_Documentation->setText(QApplication::translate("McleodIDE", "Mcleod Documentation", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("McleodIDE", "toolBar", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("McleodIDE", "File", Q_NULLPTR));
        menuProject->setTitle(QApplication::translate("McleodIDE", "Project", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("McleodIDE", "Edit", Q_NULLPTR));
        menuDebugger->setTitle(QApplication::translate("McleodIDE", "Debugger", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("McleodIDE", "Window", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("McleodIDE", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class McleodIDE: public Ui_McleodIDE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MCLEODIDE_H
