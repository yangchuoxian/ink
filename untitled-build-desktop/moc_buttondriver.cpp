/****************************************************************************
** Meta object code from reading C++ file 'buttondriver.h'
**
** Created: Tue May 28 17:16:13 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Development/QtProject/Ink/untitled/buttondriver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buttondriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ButtonDriver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

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

void ButtonDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ButtonDriver *_t = static_cast<ButtonDriver *>(_o);
        switch (_id) {
        case 0: _t->encoder_turnLeft(); break;
        case 1: _t->encoder_turnRight(); break;
        case 2: _t->buttonLastPage_pressed(); break;
        case 3: _t->buttonNextPage_pressed(); break;
        case 4: _t->buttonYes_pressed(); break;
        case 5: _t->buttonNo_pressed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ButtonDriver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ButtonDriver::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ButtonDriver,
      qt_meta_data_ButtonDriver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ButtonDriver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ButtonDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
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
