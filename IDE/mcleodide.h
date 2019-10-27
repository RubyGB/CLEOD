#ifndef MCLEODIDE_H
#define MCLEODIDE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class McLeodIDE; }
QT_END_NAMESPACE

class McLeodIDE : public QMainWindow
{
    Q_OBJECT

public:
    McLeodIDE(QWidget *parent = nullptr);
    ~McLeodIDE();

private:
    Ui::McLeodIDE *ui;
};
#endif // MCLEODIDE_H
