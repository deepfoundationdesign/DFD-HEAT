/****************************************************************************
** Meta object code from reading C++ file 'SelectionManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/SelectionManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectionManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectionManager_t {
    const uint offsetsAndSize[20];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SelectionManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SelectionManager_t qt_meta_stringdata_SelectionManager = {
    {
QT_MOC_LITERAL(0, 16), // "SelectionManager"
QT_MOC_LITERAL(17, 16), // "selectionChanged"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 11), // "modeChanged"
QT_MOC_LITERAL(47, 13), // "SelectionMode"
QT_MOC_LITERAL(61, 4), // "mode"
QT_MOC_LITERAL(66, 15), // "ObjectSelection"
QT_MOC_LITERAL(82, 15), // "VertexSelection"
QT_MOC_LITERAL(98, 13), // "EdgeSelection"
QT_MOC_LITERAL(112, 13) // "FaceSelection"

    },
    "SelectionManager\0selectionChanged\0\0"
    "modeChanged\0SelectionMode\0mode\0"
    "ObjectSelection\0VertexSelection\0"
    "EdgeSelection\0FaceSelection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectionManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       1,   30, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x06,    1 /* Public */,
       3,    1,   27,    2, 0x06,    2 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // enums: name, alias, flags, count, data
       4,    4, 0x0,    4,   35,

 // enum data: key, value
       6, uint(SelectionManager::ObjectSelection),
       7, uint(SelectionManager::VertexSelection),
       8, uint(SelectionManager::EdgeSelection),
       9, uint(SelectionManager::FaceSelection),

       0        // eod
};

void SelectionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectionManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged(); break;
        case 1: _t->modeChanged((*reinterpret_cast< std::add_pointer_t<SelectionMode>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SelectionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectionManager::selectionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SelectionManager::*)(SelectionMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectionManager::modeChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SelectionManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SelectionManager.offsetsAndSize,
    qt_meta_data_SelectionManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SelectionManager_t
, QtPrivate::TypeAndForceComplete<SelectionManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<SelectionMode, std::false_type>



>,
    nullptr
} };


const QMetaObject *SelectionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectionManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SelectionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SelectionManager::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SelectionManager::modeChanged(SelectionMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
