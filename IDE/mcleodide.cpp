#include "mcleodide.h"
#include "ui_mcleodide.h"

McleodIDE::McleodIDE(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::McleodIDE)
{
    ui->setupUi(this);
}

McleodIDE::~McleodIDE()
{
    delete ui;
}

