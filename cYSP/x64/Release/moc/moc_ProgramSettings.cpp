/****************************************************************************
** Meta object code from reading C++ file 'ProgramSettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../UIFolder/ProgramSettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProgramSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CurrentStyle_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CurrentStyle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CurrentStyle_t qt_meta_stringdata_CurrentStyle = {
    {
QT_MOC_LITERAL(0, 0, 12) // "CurrentStyle"

    },
    "CurrentStyle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CurrentStyle[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CurrentStyle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CurrentStyle::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CurrentStyle.data,
    qt_meta_data_CurrentStyle,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CurrentStyle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CurrentStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CurrentStyle.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CurrentStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_hProgramSettings_t {
    QByteArrayData data[10];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hProgramSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hProgramSettings_t qt_meta_stringdata_hProgramSettings = {
    {
QT_MOC_LITERAL(0, 0, 16), // "hProgramSettings"
QT_MOC_LITERAL(1, 17, 14), // "windowIsClosed"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "resetAll"
QT_MOC_LITERAL(4, 42, 13), // "applySettings"
QT_MOC_LITERAL(5, 56, 10), // "closeEvent"
QT_MOC_LITERAL(6, 67, 12), // "QCloseEvent*"
QT_MOC_LITERAL(7, 80, 5), // "event"
QT_MOC_LITERAL(8, 86, 9), // "showEvent"
QT_MOC_LITERAL(9, 96, 11) // "QShowEvent*"

    },
    "hProgramSettings\0windowIsClosed\0\0"
    "resetAll\0applySettings\0closeEvent\0"
    "QCloseEvent*\0event\0showEvent\0QShowEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hProgramSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,    7,

       0        // eod
};

void hProgramSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hProgramSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->windowIsClosed(); break;
        case 1: _t->resetAll(); break;
        case 2: _t->applySettings(); break;
        case 3: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 4: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hProgramSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hProgramSettings::windowIsClosed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject hProgramSettings::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hProgramSettings.data,
    qt_meta_data_hProgramSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hProgramSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hProgramSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hProgramSettings.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hProgramSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void hProgramSettings::windowIsClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_hDevSettings_t {
    QByteArrayData data[10];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hDevSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hDevSettings_t qt_meta_stringdata_hDevSettings = {
    {
QT_MOC_LITERAL(0, 0, 12), // "hDevSettings"
QT_MOC_LITERAL(1, 13, 14), // "windowIsClosed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "resetAll"
QT_MOC_LITERAL(4, 38, 13), // "applySettings"
QT_MOC_LITERAL(5, 52, 10), // "closeEvent"
QT_MOC_LITERAL(6, 63, 12), // "QCloseEvent*"
QT_MOC_LITERAL(7, 76, 5), // "event"
QT_MOC_LITERAL(8, 82, 9), // "showEvent"
QT_MOC_LITERAL(9, 92, 11) // "QShowEvent*"

    },
    "hDevSettings\0windowIsClosed\0\0resetAll\0"
    "applySettings\0closeEvent\0QCloseEvent*\0"
    "event\0showEvent\0QShowEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hDevSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,    7,

       0        // eod
};

void hDevSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hDevSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->windowIsClosed(); break;
        case 1: _t->resetAll(); break;
        case 2: _t->applySettings(); break;
        case 3: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 4: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hDevSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hDevSettings::windowIsClosed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject hDevSettings::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hDevSettings.data,
    qt_meta_data_hDevSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hDevSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hDevSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hDevSettings.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hDevSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void hDevSettings::windowIsClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_hMoreInfo_t {
    QByteArrayData data[8];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hMoreInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hMoreInfo_t qt_meta_stringdata_hMoreInfo = {
    {
QT_MOC_LITERAL(0, 0, 9), // "hMoreInfo"
QT_MOC_LITERAL(1, 10, 14), // "windowIsClosed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "closeEvent"
QT_MOC_LITERAL(4, 37, 12), // "QCloseEvent*"
QT_MOC_LITERAL(5, 50, 5), // "event"
QT_MOC_LITERAL(6, 56, 9), // "showEvent"
QT_MOC_LITERAL(7, 66, 11) // "QShowEvent*"

    },
    "hMoreInfo\0windowIsClosed\0\0closeEvent\0"
    "QCloseEvent*\0event\0showEvent\0QShowEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hMoreInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x0a /* Public */,
       6,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    5,

       0        // eod
};

void hMoreInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hMoreInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->windowIsClosed(); break;
        case 1: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 2: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hMoreInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hMoreInfo::windowIsClosed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject hMoreInfo::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hMoreInfo.data,
    qt_meta_data_hMoreInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hMoreInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hMoreInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hMoreInfo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hMoreInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void hMoreInfo::windowIsClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
