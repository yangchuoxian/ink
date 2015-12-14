/****************************************************************************
** Meta object code from reading C++ file 'buttondriver.h'
**
** Created: Wed Jan 16 18:05:45 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "buttondriver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buttondriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ButtonDriver[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      33,   13,   13,   13, 0x05,
      53,   13,   13,   13, 0x05,
      78,   13,   13,   13, 0x05,
     103,   13,   13,   13, 0x05,
     123,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ButtonDriver[] = {
    "ButtonDriver\0\0encoder_turnLeft()\0"
    "encoder_turnRight()\0buttonLastPage_pressed()\0"
    "buttonNextPage_pressed()\0buttonYes_pressed()\0"
    "buttonNo_pressed()\0"
};

const QMetaObject ButtonDriver::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ButtonDriver,
      qt_meta_data_ButtonDriver, 0 }
};

const QMetaObject *ButtonDriver::metaObject() const
{
    return &staticMetaObject;
}

void *ButtonDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ButtonDriver))
        return static_cast<void*>(const_cast< ButtonDriver*>(this));
    return QThread::qt_metacast(_clname);
}

int ButtonDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: encoder_turnLeft(); break;
        case 1: encoder_turnRight(); break;
        case 2: buttonLastPage_pressed(); break;
        case 3: buttonNextPage_pressed(); break;
        case 4: buttonYes_pressed(); break;
        case 5: buttonNo_pressed(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ButtonDriver::encoder_turnLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ButtonDriver::encoder_turnRight()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ButtonDriver::buttonLastPage_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ButtonDriver::buttonNextPage_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ButtonDriver::buttonYes_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ButtonDriver::buttonNo_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
