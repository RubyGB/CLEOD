#ifndef MCLEODIDE_H
#define MCLEODIDE_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QTabWidget>
#include <QString>
#include <QMenu>
#include <QMessageBox>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDockWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeView>
#include <QDirModel>
#include <QModelIndex>
#include <QToolBar>
#include <QTabBar>
#include <QAction>
#include <QToolButton>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>

#include <sstream>

#include "linenumberarea.h"
#include "texteditor.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class McleodIDE; }
QT_END_NAMESPACE

class McleodIDE : public QMainWindow
{
    Q_OBJECT

public:
    McleodIDE(QWidget *parent = nullptr);
    ~McleodIDE();

private slots:

    void ChangeTabIndexInList(int, int);

    void DeleteTabFromList(int);

    void UpdateCurrentIndex(int);

    void UpdateCurrentIndex(QListWidgetItem*);

    void UpdateCurrentIndexOnDelete(int);

    void CreateFile();
    void OpenFile();
    void OpenFile(const QString&);
    void OpenFile(QModelIndex);
    void SaveFile();
    void SaveFileAs();
    void Close();
    void Close(int);
    void Cut();
    void Copy();
    void Paste();
    void Undo();
    void Redo();

    void CompileAndExecute();

private:
    Ui::McleodIDE *ui;
    QString currentFile = "";
    QTabWidget* tabs;

    QDirModel* file_system_model;
    QTreeView* file_system_view;
    QListWidget* opened_docs_widget;

    QDockWidget* file_explorer_dock;
    QDockWidget* opened_docs_dock;

    QTabWidget* textEdit;
    void SetupTabWidget();
    void SetupFileDock();
    void CreateDocWindows();
    void SetupMenu();

    QMenu *viewMenu;
    Dialog *dialog;

    std::stringstream consoleStream;
};
#endif // MCLEODIDE_H
