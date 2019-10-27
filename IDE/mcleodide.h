#ifndef MCLEODIDE_H
#define MCLEODIDE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class McleodIDE; }
QT_END_NAMESPACE

class McleodIDE : public QMainWindow
{
    Q_OBJECT

public:
    McleodIDE(QWidget *parent = nullptr);
    ~McleodIDE();

private:
    Ui::McleodIDE *ui;
};
#endif // MCLEODIDE_H
