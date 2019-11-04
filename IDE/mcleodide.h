#ifndef MCLEODIDE_H
#define MCLEODIDE_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTabWidget>

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
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

private:
    Ui::McleodIDE *ui;
    QString currentFile = "";
};
#endif // MCLEODIDE_H
