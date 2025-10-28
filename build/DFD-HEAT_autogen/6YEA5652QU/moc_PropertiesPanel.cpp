/****************************************************************************
** Meta object code from reading C++ file 'PropertiesPanel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/PropertiesPanel.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertiesPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PropertiesPanel_t {
    const uint offsetsAndSize[24];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PropertiesPanel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PropertiesPanel_t qt_meta_stringdata_PropertiesPanel = {
    {
QT_MOC_LITERAL(0, 15), // "PropertiesPanel"
QT_MOC_LITERAL(16, 13), // "onNameChanged"
QT_MOC_LITERAL(30, 0), // ""
QT_MOC_LITERAL(31, 17), // "onLocationChanged"
QT_MOC_LITERAL(49, 17), // "onRotationChanged"
QT_MOC_LITERAL(67, 14), // "onScaleChanged"
QT_MOC_LITERAL(82, 19), // "onDimensionsChanged"
QT_MOC_LITERAL(102, 16), // "onVisibleChanged"
QT_MOC_LITERAL(119, 5), // "state"
QT_MOC_LITERAL(125, 15), // "onLockedChanged"
QT_MOC_LITERAL(141, 24), // "onObjectTransformChanged"
QT_MOC_LITERAL(166, 25) // "onObjectPropertiesChanged"

    },
    "PropertiesPanel\0onNameChanged\0\0"
    "onLocationChanged\0onRotationChanged\0"
    "onScaleChanged\0onDimensionsChanged\0"
    "onVisibleChanged\0state\0onLockedChanged\0"
    "onObjectTransformChanged\0"
    "onObjectPropertiesChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PropertiesPanel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    1,   73,    2, 0x08,    6 /* Private */,
       9,    1,   76,    2, 0x08,    8 /* Private */,
      10,    0,   79,    2, 0x08,   10 /* Private */,
      11,    0,   80,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PropertiesPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PropertiesPanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onNameChanged(); break;
        case 1: _t->onLocationChanged(); break;
        case 2: _t->onRotationChanged(); break;
        case 3: _t->onScaleChanged(); break;
        case 4: _t->onDimensionsChanged(); break;
        case 5: _t->onVisibleChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->onLockedChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->onObjectTransformChanged(); break;
        case 8: _t->onObjectPropertiesChanged(); break;
        default: ;
        }
    }
}

const QMetaObject PropertiesPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PropertiesPanel.offsetsAndSize,
    qt_meta_data_PropertiesPanel,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PropertiesPanel_t
, QtPrivate::TypeAndForceComplete<PropertiesPanel, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *PropertiesPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PropertiesPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PropertiesPanel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PropertiesPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
