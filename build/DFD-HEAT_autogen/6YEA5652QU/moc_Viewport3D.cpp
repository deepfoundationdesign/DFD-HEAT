/****************************************************************************
** Meta object code from reading C++ file 'Viewport3D.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/Viewport3D.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Viewport3D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Viewport3D_t {
    const uint offsetsAndSize[34];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Viewport3D_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Viewport3D_t qt_meta_stringdata_Viewport3D = {
    {
QT_MOC_LITERAL(0, 10), // "Viewport3D"
QT_MOC_LITERAL(11, 14), // "entitySelected"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 18), // "Qt3DCore::QEntity*"
QT_MOC_LITERAL(46, 6), // "entity"
QT_MOC_LITERAL(53, 12), // "faceSelected"
QT_MOC_LITERAL(66, 9), // "faceIndex"
QT_MOC_LITERAL(76, 16), // "onOrbitRequested"
QT_MOC_LITERAL(93, 6), // "deltaX"
QT_MOC_LITERAL(100, 6), // "deltaY"
QT_MOC_LITERAL(107, 14), // "onPanRequested"
QT_MOC_LITERAL(122, 15), // "onZoomRequested"
QT_MOC_LITERAL(138, 5), // "delta"
QT_MOC_LITERAL(144, 15), // "onObjectClicked"
QT_MOC_LITERAL(160, 12), // "SceneObject*"
QT_MOC_LITERAL(173, 6), // "object"
QT_MOC_LITERAL(180, 13) // "onObjectAdded"

    },
    "Viewport3D\0entitySelected\0\0"
    "Qt3DCore::QEntity*\0entity\0faceSelected\0"
    "faceIndex\0onOrbitRequested\0deltaX\0"
    "deltaY\0onPanRequested\0onZoomRequested\0"
    "delta\0onObjectClicked\0SceneObject*\0"
    "object\0onObjectAdded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Viewport3D[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       5,    1,   59,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    2,   62,    2, 0x08,    5 /* Private */,
      10,    2,   67,    2, 0x08,    8 /* Private */,
      11,    1,   72,    2, 0x08,   11 /* Private */,
      13,    1,   75,    2, 0x08,   13 /* Private */,
      16,    1,   78,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void Viewport3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Viewport3D *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->entitySelected((*reinterpret_cast< std::add_pointer_t<Qt3DCore::QEntity*>>(_a[1]))); break;
        case 1: _t->faceSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->onOrbitRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->onPanRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->onZoomRequested((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 5: _t->onObjectClicked((*reinterpret_cast< std::add_pointer_t<SceneObject*>>(_a[1]))); break;
        case 6: _t->onObjectAdded((*reinterpret_cast< std::add_pointer_t<SceneObject*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Qt3DCore::QEntity* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Viewport3D::*)(Qt3DCore::QEntity * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Viewport3D::entitySelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Viewport3D::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Viewport3D::faceSelected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Viewport3D::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Viewport3D.offsetsAndSize,
    qt_meta_data_Viewport3D,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Viewport3D_t
, QtPrivate::TypeAndForceComplete<Viewport3D, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Qt3DCore::QEntity *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<SceneObject *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<SceneObject *, std::false_type>


>,
    nullptr
} };


const QMetaObject *Viewport3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Viewport3D::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Viewport3D.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Viewport3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Viewport3D::entitySelected(Qt3DCore::QEntity * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Viewport3D::faceSelected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
