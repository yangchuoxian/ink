/****************************************************************************
** Meta object code from reading C++ file 'tiffhandler.h'
**
** Created: Wed Jan 16 18:05:47 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tiffhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tiffhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TIFFHandler[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      35,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TIFFHandler[] = {
    "TIFFHandler\0\0progressRange(qint64)\0"
    "percentage(qint64)\0"
};

const QMetaObject TIFFHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TIFFHandler,
      qt_meta_data_TIFFHandler, 0 }
};

const QMetaObject *TIFFHandler::metaObject() const
{
    return &staticMetaObject;
}

void *TIFFHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TIFFHandler))
        return static_cast<void*>(const_cast< TIFFHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int TIFFHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: progressRange((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: percentage((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TIFFHandler::progressRange(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TIFFHandler::percentage(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
