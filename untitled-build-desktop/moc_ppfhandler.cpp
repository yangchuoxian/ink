/****************************************************************************
** Meta object code from reading C++ file 'ppfhandler.h'
**
** Created: Tue May 28 17:16:14 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Development/QtProject/Ink/untitled/ppfhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ppfhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PPFHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      34,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PPFHandler[] = {
    "PPFHandler\0\0progressRange(qint64)\0"
    "percentage(qint64)\0"
};

void PPFHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PPFHandler *_t = static_cast<PPFHandler *>(_o);
        switch (_id) {
        case 0: _t->progressRange((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: _t->percentage((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PPFHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PPFHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PPFHandler,
      qt_meta_data_PPFHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PPFHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PPFHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PPFHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PPFHandler))
        return static_cast<void*>(const_cast< PPFHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int PPFHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PPFHandler::progressRange(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PPFHandler::percentage(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
