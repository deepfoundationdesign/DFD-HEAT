/****************************************************************************
** Meta object code from reading C++ file 'ModeManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/ModeManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModeManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModeManager_t {
    const uint offsetsAndSize[20];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ModeManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ModeManager_t qt_meta_stringdata_ModeManager = {
    {
QT_MOC_LITERAL(0, 11), // "ModeManager"
QT_MOC_LITERAL(12, 11), // "modeChanged"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 4), // "Mode"
QT_MOC_LITERAL(30, 4), // "mode"
QT_MOC_LITERAL(35, 19), // "activeObjectChanged"
QT_MOC_LITERAL(55, 12), // "SceneObject*"
QT_MOC_LITERAL(68, 6), // "object"
QT_MOC_LITERAL(75, 10), // "ObjectMode"
QT_MOC_LITERAL(86, 8) // "EditMode"

    },
    "ModeManager\0modeChanged\0\0Mode\0mode\0"
    "activeObjectChanged\0SceneObject*\0"
    "object\0ObjectMode\0EditMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModeManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       1,   32, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    1 /* Public */,
       5,    1,   29,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // enums: name, alias, flags, count, data
       3,    3, 0x0,    2,   37,

 // enum data: key, value
       8, uint(ModeManager::ObjectMode),
       9, uint(ModeManager::EditMode),

       0        // eod
};

void ModeManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModeManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->modeChanged((*reinterpret_cast< std::add_pointer_t<Mode>>(_a[1]))); break;
        case 1: _t->activeObjectChanged((*reinterpret_cast< std::add_pointer_t<SceneObject*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ModeManager::*)(Mode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModeManager::modeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ModeManager::*)(SceneObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModeManager::activeObjectChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ModeManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ModeManager.offsetsAndSize,
    qt_meta_data_ModeManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ModeManager_t
, QtPrivate::TypeAndForceComplete<ModeManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Mode, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<SceneObject *, std::false_type>



>,
    nullptr
} };


const QMetaObject *ModeManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModeManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModeManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ModeManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ModeManager::modeChanged(Mode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModeManager::activeObjectChanged(SceneObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
