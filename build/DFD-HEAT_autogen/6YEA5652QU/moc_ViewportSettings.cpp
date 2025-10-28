/****************************************************************************
** Meta object code from reading C++ file 'ViewportSettings.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/ViewportSettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ViewportSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ViewportSettings_t {
    const uint offsetsAndSize[26];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ViewportSettings_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ViewportSettings_t qt_meta_stringdata_ViewportSettings = {
    {
QT_MOC_LITERAL(0, 16), // "ViewportSettings"
QT_MOC_LITERAL(17, 15), // "showGridChanged"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 15), // "showAxisChanged"
QT_MOC_LITERAL(50, 15), // "gridSizeChanged"
QT_MOC_LITERAL(66, 20), // "gridDivisionsChanged"
QT_MOC_LITERAL(87, 17), // "axisLengthChanged"
QT_MOC_LITERAL(105, 22), // "backgroundColorChanged"
QT_MOC_LITERAL(128, 8), // "showGrid"
QT_MOC_LITERAL(137, 8), // "showAxis"
QT_MOC_LITERAL(146, 8), // "gridSize"
QT_MOC_LITERAL(155, 13), // "gridDivisions"
QT_MOC_LITERAL(169, 10) // "axisLength"

    },
    "ViewportSettings\0showGridChanged\0\0"
    "showAxisChanged\0gridSizeChanged\0"
    "gridDivisionsChanged\0axisLengthChanged\0"
    "backgroundColorChanged\0showGrid\0"
    "showAxis\0gridSize\0gridDivisions\0"
    "axisLength"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewportSettings[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       5,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    6 /* Public */,
       3,    0,   51,    2, 0x06,    7 /* Public */,
       4,    0,   52,    2, 0x06,    8 /* Public */,
       5,    0,   53,    2, 0x06,    9 /* Public */,
       6,    0,   54,    2, 0x06,   10 /* Public */,
       7,    0,   55,    2, 0x06,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::Bool, 0x00015103, uint(0), 0,
       9, QMetaType::Bool, 0x00015103, uint(1), 0,
      10, QMetaType::Float, 0x00015103, uint(2), 0,
      11, QMetaType::Int, 0x00015103, uint(3), 0,
      12, QMetaType::Float, 0x00015103, uint(4), 0,

       0        // eod
};

void ViewportSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ViewportSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showGridChanged(); break;
        case 1: _t->showAxisChanged(); break;
        case 2: _t->gridSizeChanged(); break;
        case 3: _t->gridDivisionsChanged(); break;
        case 4: _t->axisLengthChanged(); break;
        case 5: _t->backgroundColorChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ViewportSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewportSettings::showGridChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ViewportSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewportSettings::showAxisChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ViewportSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewportSettings::gridSizeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ViewportSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewportSettings::gridDivisionsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ViewportSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewportSettings::axisLengthChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ViewportSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewportSettings::backgroundColorChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ViewportSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->showGrid(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->showAxis(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->gridSize(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->gridDivisions(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->axisLength(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ViewportSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setShowGrid(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setShowAxis(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setGridSize(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setGridDivisions(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setAxisLength(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject ViewportSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ViewportSettings.offsetsAndSize,
    qt_meta_data_ViewportSettings,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ViewportSettings_t
, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<float, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<float, std::true_type>, QtPrivate::TypeAndForceComplete<ViewportSettings, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *ViewportSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewportSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ViewportSettings.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ViewportSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ViewportSettings::showGridChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ViewportSettings::showAxisChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ViewportSettings::gridSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ViewportSettings::gridDivisionsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ViewportSettings::axisLengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ViewportSettings::backgroundColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
