/****************************************************************************
** Meta object code from reading C++ file 'Custom3DWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/Custom3DWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Custom3DWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Custom3DWindow_t {
    const uint offsetsAndSize[16];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Custom3DWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Custom3DWindow_t qt_meta_stringdata_Custom3DWindow = {
    {
QT_MOC_LITERAL(0, 14), // "Custom3DWindow"
QT_MOC_LITERAL(15, 14), // "orbitRequested"
QT_MOC_LITERAL(30, 0), // ""
QT_MOC_LITERAL(31, 6), // "deltaX"
QT_MOC_LITERAL(38, 6), // "deltaY"
QT_MOC_LITERAL(45, 12), // "panRequested"
QT_MOC_LITERAL(58, 13), // "zoomRequested"
QT_MOC_LITERAL(72, 5) // "delta"

    },
    "Custom3DWindow\0orbitRequested\0\0deltaX\0"
    "deltaY\0panRequested\0zoomRequested\0"
    "delta"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Custom3DWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   32,    2, 0x06,    1 /* Public */,
       5,    2,   37,    2, 0x06,    4 /* Public */,
       6,    1,   42,    2, 0x06,    7 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Float,    7,

       0        // eod
};

void Custom3DWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Custom3DWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->orbitRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->panRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->zoomRequested((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Custom3DWindow::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Custom3DWindow::orbitRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Custom3DWindow::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Custom3DWindow::panRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Custom3DWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Custom3DWindow::zoomRequested)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Custom3DWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<Qt3DExtras::Qt3DWindow::staticMetaObject>(),
    qt_meta_stringdata_Custom3DWindow.offsetsAndSize,
    qt_meta_data_Custom3DWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Custom3DWindow_t
, QtPrivate::TypeAndForceComplete<Custom3DWindow, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>



>,
    nullptr
} };


const QMetaObject *Custom3DWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Custom3DWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Custom3DWindow.stringdata0))
        return static_cast<void*>(this);
    return Qt3DExtras::Qt3DWindow::qt_metacast(_clname);
}

int Custom3DWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Qt3DExtras::Qt3DWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Custom3DWindow::orbitRequested(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Custom3DWindow::panRequested(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Custom3DWindow::zoomRequested(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
