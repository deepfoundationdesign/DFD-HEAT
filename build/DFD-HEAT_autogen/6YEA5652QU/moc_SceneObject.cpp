/****************************************************************************
** Meta object code from reading C++ file 'SceneObject.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/SceneObject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SceneObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SceneObject_t {
    const uint offsetsAndSize[32];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SceneObject_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SceneObject_t qt_meta_stringdata_SceneObject = {
    {
QT_MOC_LITERAL(0, 11), // "SceneObject"
QT_MOC_LITERAL(12, 16), // "transformChanged"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 17), // "propertiesChanged"
QT_MOC_LITERAL(48, 16), // "selectionChanged"
QT_MOC_LITERAL(65, 8), // "selected"
QT_MOC_LITERAL(74, 7), // "clicked"
QT_MOC_LITERAL(82, 12), // "SceneObject*"
QT_MOC_LITERAL(95, 6), // "object"
QT_MOC_LITERAL(102, 15), // "onObjectClicked"
QT_MOC_LITERAL(118, 8), // "location"
QT_MOC_LITERAL(127, 8), // "rotation"
QT_MOC_LITERAL(136, 5), // "scale"
QT_MOC_LITERAL(142, 4), // "name"
QT_MOC_LITERAL(147, 7), // "visible"
QT_MOC_LITERAL(155, 6) // "locked"

    },
    "SceneObject\0transformChanged\0\0"
    "propertiesChanged\0selectionChanged\0"
    "selected\0clicked\0SceneObject*\0object\0"
    "onObjectClicked\0location\0rotation\0"
    "scale\0name\0visible\0locked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SceneObject[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       6,   53, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    7 /* Public */,
       3,    0,   45,    2, 0x06,    8 /* Public */,
       4,    1,   46,    2, 0x06,    9 /* Public */,
       6,    1,   49,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   52,    2, 0x08,   13 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QVector3D, 0x00015103, uint(0), 0,
      11, QMetaType::QVector3D, 0x00015103, uint(0), 0,
      12, QMetaType::QVector3D, 0x00015103, uint(0), 0,
      13, QMetaType::QString, 0x00015103, uint(1), 0,
      14, QMetaType::Bool, 0x00015103, uint(1), 0,
      15, QMetaType::Bool, 0x00015103, uint(1), 0,

       0        // eod
};

void SceneObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SceneObject *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->transformChanged(); break;
        case 1: _t->propertiesChanged(); break;
        case 2: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->clicked((*reinterpret_cast< std::add_pointer_t<SceneObject*>>(_a[1]))); break;
        case 4: _t->onObjectClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< SceneObject* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SceneObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneObject::transformChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SceneObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneObject::propertiesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SceneObject::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneObject::selectionChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SceneObject::*)(SceneObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneObject::clicked)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SceneObject *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVector3D*>(_v) = _t->location(); break;
        case 1: *reinterpret_cast< QVector3D*>(_v) = _t->rotation(); break;
        case 2: *reinterpret_cast< QVector3D*>(_v) = _t->scale(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->isVisible(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isLocked(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SceneObject *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLocation(*reinterpret_cast< QVector3D*>(_v)); break;
        case 1: _t->setRotation(*reinterpret_cast< QVector3D*>(_v)); break;
        case 2: _t->setScale(*reinterpret_cast< QVector3D*>(_v)); break;
        case 3: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setLocked(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject SceneObject::staticMetaObject = { {
    QMetaObject::SuperData::link<Qt3DCore::QEntity::staticMetaObject>(),
    qt_meta_stringdata_SceneObject.offsetsAndSize,
    qt_meta_data_SceneObject,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SceneObject_t
, QtPrivate::TypeAndForceComplete<QVector3D, std::true_type>, QtPrivate::TypeAndForceComplete<QVector3D, std::true_type>, QtPrivate::TypeAndForceComplete<QVector3D, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<SceneObject, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<SceneObject *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *SceneObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SceneObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SceneObject.stringdata0))
        return static_cast<void*>(this);
    return Qt3DCore::QEntity::qt_metacast(_clname);
}

int SceneObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Qt3DCore::QEntity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SceneObject::transformChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SceneObject::propertiesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SceneObject::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SceneObject::clicked(SceneObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
