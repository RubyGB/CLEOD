#include "mcleodide.h"
#include "ui_mcleodide.h"

McLeodIDE::McLeodIDE(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::McLeodIDE)
{
    ui->setupUi(this);
}

McLeodIDE::~McLeodIDE()
{
    delete ui;
}

