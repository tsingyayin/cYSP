/****************************************************************************
** Meta object code from reading C++ file 'ArtificialUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../UIFolder/ArtificialUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArtificialUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChangeWake_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChangeWake_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChangeWake_t qt_meta_stringdata_ChangeWake = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChangeWake"
QT_MOC_LITERAL(1, 11, 8), // "willStop"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12) // "lastContinue"

    },
    "ChangeWake\0willStop\0\0lastContinue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChangeWake[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ChangeWake::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChangeWake *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->willStop(); break;
        case 1: _t->lastContinue(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ChangeWake::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ChangeWake.data,
    qt_meta_data_ChangeWake,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChangeWake::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChangeWake::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChangeWake.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChangeWake::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_TickThread_t {
    QByteArrayData data[3];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TickThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TickThread_t qt_meta_stringdata_TickThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TickThread"
QT_MOC_LITERAL(1, 11, 7), // "timeout"
QT_MOC_LITERAL(2, 19, 0) // ""

    },
    "TickThread\0timeout\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TickThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void TickThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TickThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TickThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TickThread::timeout)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TickThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_TickThread.data,
    qt_meta_data_TickThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TickThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TickThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TickThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int TickThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TickThread::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_PlayerDef_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerDef_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerDef_t qt_meta_stringdata_PlayerDef = {
    {
QT_MOC_LITERAL(0, 0, 9) // "PlayerDef"

    },
    "PlayerDef"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerDef[] = {

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

void PlayerDef::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PlayerDef::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PlayerDef.data,
    qt_meta_data_PlayerDef,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlayerDef::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerDef::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerDef.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayerDef::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PlayerWindow_t {
    QByteArrayData data[30];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerWindow_t qt_meta_stringdata_PlayerWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PlayerWindow"
QT_MOC_LITERAL(1, 13, 7), // "stopNow"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "gshow"
QT_MOC_LITERAL(4, 28, 15), // "gshowFullScreen"
QT_MOC_LITERAL(5, 44, 7), // "RUNCORE"
QT_MOC_LITERAL(6, 52, 8), // "tickslot"
QT_MOC_LITERAL(7, 61, 9), // "hideHello"
QT_MOC_LITERAL(8, 71, 3), // "num"
QT_MOC_LITERAL(9, 75, 10), // "_hideHello"
QT_MOC_LITERAL(10, 86, 12), // "reprintHello"
QT_MOC_LITERAL(11, 99, 13), // "_reprintHello"
QT_MOC_LITERAL(12, 113, 8), // "setTitle"
QT_MOC_LITERAL(13, 122, 12), // "titlesetList"
QT_MOC_LITERAL(14, 135, 9), // "showTitle"
QT_MOC_LITERAL(15, 145, 9), // "hideTitle"
QT_MOC_LITERAL(16, 155, 13), // "hideTitleLast"
QT_MOC_LITERAL(17, 169, 7), // "playBGM"
QT_MOC_LITERAL(18, 177, 8), // "filename"
QT_MOC_LITERAL(19, 186, 6), // "volume"
QT_MOC_LITERAL(20, 193, 9), // "playSound"
QT_MOC_LITERAL(21, 203, 13), // "keyPressEvent"
QT_MOC_LITERAL(22, 217, 10), // "QKeyEvent*"
QT_MOC_LITERAL(23, 228, 5), // "event"
QT_MOC_LITERAL(24, 234, 6), // "Wakeup"
QT_MOC_LITERAL(25, 241, 15), // "wakeInterpreter"
QT_MOC_LITERAL(26, 257, 11), // "exitProgram"
QT_MOC_LITERAL(27, 269, 10), // "closeEvent"
QT_MOC_LITERAL(28, 280, 12), // "QCloseEvent*"
QT_MOC_LITERAL(29, 293, 21) // "disconnectInterpreter"

    },
    "PlayerWindow\0stopNow\0\0gshow\0gshowFullScreen\0"
    "RUNCORE\0tickslot\0hideHello\0num\0"
    "_hideHello\0reprintHello\0_reprintHello\0"
    "setTitle\0titlesetList\0showTitle\0"
    "hideTitle\0hideTitleLast\0playBGM\0"
    "filename\0volume\0playSound\0keyPressEvent\0"
    "QKeyEvent*\0event\0Wakeup\0wakeInterpreter\0"
    "exitProgram\0closeEvent\0QCloseEvent*\0"
    "disconnectInterpreter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  120,    2, 0x0a /* Public */,
       4,    0,  121,    2, 0x0a /* Public */,
       5,    0,  122,    2, 0x0a /* Public */,
       6,    0,  123,    2, 0x0a /* Public */,
       7,    1,  124,    2, 0x0a /* Public */,
       9,    0,  127,    2, 0x0a /* Public */,
      10,    1,  128,    2, 0x0a /* Public */,
      11,    0,  131,    2, 0x0a /* Public */,
      12,    1,  132,    2, 0x0a /* Public */,
      14,    0,  135,    2, 0x0a /* Public */,
      15,    0,  136,    2, 0x0a /* Public */,
      16,    0,  137,    2, 0x0a /* Public */,
      17,    2,  138,    2, 0x0a /* Public */,
      20,    2,  143,    2, 0x0a /* Public */,
      21,    1,  148,    2, 0x0a /* Public */,
      24,    0,  151,    2, 0x0a /* Public */,
      25,    0,  152,    2, 0x0a /* Public */,
      26,    0,  153,    2, 0x0a /* Public */,
      27,    1,  154,    2, 0x0a /* Public */,
      29,    0,  157,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   18,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   18,   19,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   23,
    QMetaType::Void,

       0        // eod
};

void PlayerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlayerWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopNow(); break;
        case 1: _t->gshow(); break;
        case 2: _t->gshowFullScreen(); break;
        case 3: _t->RUNCORE(); break;
        case 4: _t->tickslot(); break;
        case 5: _t->hideHello((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->_hideHello(); break;
        case 7: _t->reprintHello((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->_reprintHello(); break;
        case 9: _t->setTitle((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 10: _t->showTitle(); break;
        case 11: _t->hideTitle(); break;
        case 12: _t->hideTitleLast(); break;
        case 13: _t->playBGM((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->playSound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 16: _t->Wakeup(); break;
        case 17: _t->wakeInterpreter(); break;
        case 18: _t->exitProgram(); break;
        case 19: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 20: _t->disconnectInterpreter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlayerWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWindow::stopNow)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayerWindow::staticMetaObject = { {
    &PlayerDef::staticMetaObject,
    qt_meta_stringdata_PlayerWindow.data,
    qt_meta_data_PlayerWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlayerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerWindow.stringdata0))
        return static_cast<void*>(this);
    return PlayerDef::qt_metacast(_clname);
}

int PlayerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PlayerDef::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void PlayerWindow::stopNow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
