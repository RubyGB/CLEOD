/****************************************************************************
** Meta object code from reading C++ file 'mcleodide.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../IDE/mcleodide.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcleodide.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_McleodIDE_t {
    QByteArrayData data[17];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_McleodIDE_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_McleodIDE_t qt_meta_stringdata_McleodIDE = {
    {
QT_MOC_LITERAL(0, 0, 9), // "McleodIDE"
QT_MOC_LITERAL(1, 10, 20), // "ChangeTabIndexInList"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "DeleteTabFromList"
QT_MOC_LITERAL(4, 50, 18), // "UpdateCurrentIndex"
QT_MOC_LITERAL(5, 69, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 86, 26), // "UpdateCurrentIndexOnDelete"
QT_MOC_LITERAL(7, 113, 10), // "CreateFile"
QT_MOC_LITERAL(8, 124, 8), // "OpenFile"
QT_MOC_LITERAL(9, 133, 8), // "SaveFile"
QT_MOC_LITERAL(10, 142, 10), // "SaveFileAs"
QT_MOC_LITERAL(11, 153, 5), // "Close"
QT_MOC_LITERAL(12, 159, 3), // "Cut"
QT_MOC_LITERAL(13, 163, 4), // "Copy"
QT_MOC_LITERAL(14, 168, 5), // "Paste"
QT_MOC_LITERAL(15, 174, 4), // "Undo"
QT_MOC_LITERAL(16, 179, 4) // "Redo"

    },
    "McleodIDE\0ChangeTabIndexInList\0\0"
    "DeleteTabFromList\0UpdateCurrentIndex\0"
    "QListWidgetItem*\0UpdateCurrentIndexOnDelete\0"
    "CreateFile\0OpenFile\0SaveFile\0SaveFileAs\0"
    "Close\0Cut\0Copy\0Paste\0Undo\0Redo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_McleodIDE[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,  104,    2, 0x08 /* Private */,
       3,    1,  109,    2, 0x08 /* Private */,
       4,    1,  112,    2, 0x08 /* Private */,
       4,    1,  115,    2, 0x08 /* Private */,
       6,    1,  118,    2, 0x08 /* Private */,
       7,    0,  121,    2, 0x08 /* Private */,
       8,    0,  122,    2, 0x08 /* Private */,
       8,    1,  123,    2, 0x08 /* Private */,
       8,    1,  126,    2, 0x08 /* Private */,
       9,    0,  129,    2, 0x08 /* Private */,
      10,    0,  130,    2, 0x08 /* Private */,
      11,    0,  131,    2, 0x08 /* Private */,
      11,    1,  132,    2, 0x08 /* Private */,
      12,    0,  135,    2, 0x08 /* Private */,
      13,    0,  136,    2, 0x08 /* Private */,
      14,    0,  137,    2, 0x08 /* Private */,
      15,    0,  138,    2, 0x08 /* Private */,
      16,    0,  139,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void McleodIDE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        McleodIDE *_t = static_cast<McleodIDE *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ChangeTabIndexInList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->DeleteTabFromList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->UpdateCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->UpdateCurrentIndex((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->UpdateCurrentIndexOnDelete((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->CreateFile(); break;
        case 6: _t->OpenFile(); break;
        case 7: _t->OpenFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->OpenFile((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 9: _t->SaveFile(); break;
        case 10: _t->SaveFileAs(); break;
        case 11: _t->Close(); break;
        case 12: _t->Close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->Cut(); break;
        case 14: _t->Copy(); break;
        case 15: _t->Paste(); break;
        case 16: _t->Undo(); break;
        case 17: _t->Redo(); break;
        default: ;
        }
    }
}

const QMetaObject McleodIDE::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_McleodIDE.data,
      qt_meta_data_McleodIDE,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *McleodIDE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *McleodIDE::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_McleodIDE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int McleodIDE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
