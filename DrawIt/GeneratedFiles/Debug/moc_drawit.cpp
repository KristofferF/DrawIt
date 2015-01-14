/****************************************************************************
** Meta object code from reading C++ file 'drawit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../drawit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DrawIt_t {
    QByteArrayData data[17];
    char stringdata[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawIt_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawIt_t qt_meta_stringdata_DrawIt = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 4),
QT_MOC_LITERAL(2, 12, 0),
QT_MOC_LITERAL(3, 13, 4),
QT_MOC_LITERAL(4, 18, 18),
QT_MOC_LITERAL(5, 37, 10),
QT_MOC_LITERAL(6, 48, 5),
QT_MOC_LITERAL(7, 54, 15),
QT_MOC_LITERAL(8, 70, 17),
QT_MOC_LITERAL(9, 88, 11),
QT_MOC_LITERAL(10, 100, 5),
QT_MOC_LITERAL(11, 106, 11),
QT_MOC_LITERAL(12, 118, 12),
QT_MOC_LITERAL(13, 131, 12),
QT_MOC_LITERAL(14, 144, 14),
QT_MOC_LITERAL(15, 159, 4),
QT_MOC_LITERAL(16, 164, 4)
    },
    "DrawIt\0open\0\0save\0setBackgroundColor\0"
    "clearImage\0about\0setPrimaryColor\0"
    "setSecondaryColor\0setPenWidth\0index\0"
    "setPenStyle\0setEmptyFill\0setColorFill\0"
    "setDrawingMode\0undo\0redo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawIt[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    1,   91,    2, 0x0a /* Public */,
      11,    1,   94,    2, 0x0a /* Public */,
      12,    0,   97,    2, 0x0a /* Public */,
      13,    0,   98,    2, 0x0a /* Public */,
      14,    1,   99,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DrawIt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DrawIt *_t = static_cast<DrawIt *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->save(); break;
        case 2: _t->setBackgroundColor(); break;
        case 3: _t->clearImage(); break;
        case 4: _t->about(); break;
        case 5: _t->setPrimaryColor(); break;
        case 6: _t->setSecondaryColor(); break;
        case 7: _t->setPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setPenStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setEmptyFill(); break;
        case 10: _t->setColorFill(); break;
        case 11: _t->setDrawingMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->undo(); break;
        case 13: _t->redo(); break;
        default: ;
        }
    }
}

const QMetaObject DrawIt::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DrawIt.data,
      qt_meta_data_DrawIt,  qt_static_metacall, 0, 0}
};


const QMetaObject *DrawIt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawIt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DrawIt.stringdata))
        return static_cast<void*>(const_cast< DrawIt*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DrawIt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
