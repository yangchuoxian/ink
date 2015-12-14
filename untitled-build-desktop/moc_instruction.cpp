/****************************************************************************
** Meta object code from reading C++ file 'instruction.h'
**
** Created: Thu Apr 19 03:06:14 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../untitled/instruction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'instruction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Instruction[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      32,   12,   12,   12, 0x05,
      52,   12,   12,   12, 0x05,
      77,   12,   12,   12, 0x05,
     102,   12,   12,   12, 0x05,
     122,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Instruction[] = {
    "Instruction\0\0encoder_turnLeft()\0"
    "encoder_turnRight()\0buttonLastPage_pressed()\0"
    "buttonNextPage_pressed()\0buttonYes_pressed()\0"
    "buttonNo_pressed()\0"
};

const QMetaObject Instruction::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Instruction,
      qt_meta_data_Instruction, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Instruction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Instruction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Instruction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Instruction))
        return static_cast<void*>(const_cast< Instruction*>(this));
    return QThread::qt_metacast(_clname);
}

int Instruction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Instruction::encoder_turnLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Instruction::encoder_turnRight()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Instruction::buttonLastPage_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Instruction::buttonNextPage_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Instruction::buttonYes_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Instruction::buttonNo_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
