QT       += core gui\
            xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
TARGET   = McleodIDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../

SOURCES += \
    dialog.cpp \
    main.cpp \
    mcleodide.cpp \
    texteditor.cpp \
    ../Frontend/Scanner.cpp \
    ../MiddleEnd/Compiler.cpp \
    ../Backend/VirtualMachine.cpp \
    ../Frontend/Token.cpp \
    ../MiddleEnd/Bytecode.cpp \
    ../Backend/GarbageCollector.cpp

HEADERS += \
    dialog.h \
    linenumberarea.h \
    mcleodide.h \
    texteditor.h \
    ../Frontend/Scanner.h \
    ../MiddleEnd/Compiler.h \
    ../Backend/VirtualMachine.h \
    ../Frontend/Token.h \
    ../MiddleEnd/Bytecode.h \
    ../MiddleEnd/Object.h \
    ../Backend/GarbageCollector.h

FORMS += \
    dialog.ui \
    mcleodide.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
