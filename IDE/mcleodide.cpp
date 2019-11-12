#include "mcleodide.h"
#include "ui_mcleodide.h"

McleodIDE::McleodIDE(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::McleodIDE)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}


McleodIDE::~McleodIDE()
{
    delete ui;
}



void McleodIDE::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void McleodIDE::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file: "+ file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void McleodIDE::on_actionSave_triggered()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void McleodIDE::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void McleodIDE::on_actionExit_triggered()
{
    QApplication::quit();
}

void McleodIDE::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void McleodIDE::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void McleodIDE::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void McleodIDE::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void McleodIDE::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}
/*
void McleodIDE::on_actionWelcome_triggered()
{

}

void McleodIDE::on_actionMcleod_Documentation_triggered()
{

}
**/
