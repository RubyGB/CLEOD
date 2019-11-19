#include "mcleodide.h"

#include <QApplication>

#ifdef DEBUG
    #include <windows.h>
    #include <stdio.h>
#endif

int main(int argc, char *argv[])
{
#ifdef DEBUG

    FreeConsole();

    AllocConsole();

    AttatchConsole(GetCurrentProcessId());

    freopen("CON", "w", stout);
    freopen("CON", "w", stderr);
    freopen("CON", "r", stdin);
#endif

    QApplication a(argc, argv);    
    McleodIDE w;
    w.show();
    return a.exec();
}
