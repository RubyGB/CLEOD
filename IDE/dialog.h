#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui{
class Dialog;
}

class Dialog : public QDialog{
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
