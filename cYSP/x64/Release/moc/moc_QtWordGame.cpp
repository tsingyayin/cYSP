/****************************************************************************
** Meta object code from reading C++ file 'QtWordGame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../UIFolder/QtWordGame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtWordGame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SingleInfo_t {
    QByteArrayData data[16];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleInfo_t qt_meta_stringdata_SingleInfo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SingleInfo"
QT_MOC_LITERAL(1, 11, 9), // "needEnter"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "willExit"
QT_MOC_LITERAL(4, 31, 7), // "gTicker"
QT_MOC_LITERAL(5, 39, 10), // "disConnect"
QT_MOC_LITERAL(6, 50, 8), // "tickslot"
QT_MOC_LITERAL(7, 59, 9), // "flashThis"
QT_MOC_LITERAL(8, 69, 6), // "moveIn"
QT_MOC_LITERAL(9, 76, 6), // "moveTo"
QT_MOC_LITERAL(10, 83, 4), // "Step"
QT_MOC_LITERAL(11, 88, 7), // "_moveTo"
QT_MOC_LITERAL(12, 96, 11), // "waitForward"
QT_MOC_LITERAL(13, 108, 7), // "moveOut"
QT_MOC_LITERAL(14, 116, 7), // "exitNow"
QT_MOC_LITERAL(15, 124, 8) // "_moveOut"

    },
    "SingleInfo\0needEnter\0\0willExit\0gTicker\0"
    "disConnect\0tickslot\0flashThis\0moveIn\0"
    "moveTo\0Step\0_moveTo\0waitForward\0moveOut\0"
    "exitNow\0_moveOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,
       5,    0,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    1,   91,    2, 0x0a /* Public */,
       9,    0,   94,    2, 0x0a /* Public */,
      11,    0,   95,    2, 0x0a /* Public */,
      12,    1,   96,    2, 0x0a /* Public */,
      13,    0,   99,    2, 0x0a /* Public */,
      14,    0,  100,    2, 0x0a /* Public */,
      15,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SingleInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SingleInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->needEnter(); break;
        case 1: _t->willExit(); break;
        case 2: _t->gTicker(); break;
        case 3: _t->disConnect(); break;
        case 4: _t->tickslot(); break;
        case 5: _t->flashThis(); break;
        case 6: _t->moveIn(); break;
        case 7: _t->moveTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->moveTo(); break;
        case 9: _t->_moveTo(); break;
        case 10: _t->waitForward((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->moveOut(); break;
        case 12: _t->exitNow(); break;
        case 13: _t->_moveOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SingleInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleInfo::needEnter)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SingleInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleInfo::willExit)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SingleInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleInfo::gTicker)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SingleInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleInfo::disConnect)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SingleInfo::staticMetaObject = { {
    &QFrame::staticMetaObject,
    qt_meta_stringdata_SingleInfo.data,
    qt_meta_data_SingleInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SingleInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SingleInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SingleInfo.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int SingleInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SingleInfo::needEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SingleInfo::willExit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SingleInfo::gTicker()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SingleInfo::disConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_uInfoWidget_t {
    QByteArrayData data[13];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uInfoWidget_t qt_meta_stringdata_uInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "uInfoWidget"
QT_MOC_LITERAL(1, 12, 7), // "timeout"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "tickslot"
QT_MOC_LITERAL(4, 30, 10), // "addNewInfo"
QT_MOC_LITERAL(5, 41, 5), // "Title"
QT_MOC_LITERAL(6, 47, 8), // "Subtitle"
QT_MOC_LITERAL(7, 56, 7), // "RawInfo"
QT_MOC_LITERAL(8, 64, 4), // "EIFL"
QT_MOC_LITERAL(9, 69, 5), // "E_IFL"
QT_MOC_LITERAL(10, 75, 17), // "disConnectSignals"
QT_MOC_LITERAL(11, 93, 8), // "tellStep"
QT_MOC_LITERAL(12, 102, 11) // "moveForward"

    },
    "uInfoWidget\0timeout\0\0tickslot\0addNewInfo\0"
    "Title\0Subtitle\0RawInfo\0EIFL\0E_IFL\0"
    "disConnectSignals\0tellStep\0moveForward"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uInfoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x0a /* Public */,
       4,    4,   46,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x0a /* Public */,
      11,    0,   56,    2, 0x0a /* Public */,
      12,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 8,    5,    6,    7,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void uInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<uInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeout(); break;
        case 1: _t->tickslot(); break;
        case 2: _t->addNewInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< EIFL(*)>(_a[4]))); break;
        case 3: _t->disConnectSignals(); break;
        case 4: _t->tellStep(); break;
        case 5: _t->moveForward(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (uInfoWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uInfoWidget::timeout)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject uInfoWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_uInfoWidget.data,
    qt_meta_data_uInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int uInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void uInfoWidget::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_uFirstPage_t {
    QByteArrayData data[6];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uFirstPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uFirstPage_t qt_meta_stringdata_uFirstPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "uFirstPage"
QT_MOC_LITERAL(1, 11, 17), // "chooseFileClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "exitProgramClicked"
QT_MOC_LITERAL(4, 49, 14), // "getLoadingInfo"
QT_MOC_LITERAL(5, 64, 4) // "Info"

    },
    "uFirstPage\0chooseFileClicked\0\0"
    "exitProgramClicked\0getLoadingInfo\0"
    "Info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uFirstPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void uFirstPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<uFirstPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->chooseFileClicked(); break;
        case 1: _t->exitProgramClicked(); break;
        case 2: _t->getLoadingInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (uFirstPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uFirstPage::chooseFileClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (uFirstPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uFirstPage::exitProgramClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject uFirstPage::staticMetaObject = { {
    &QFrame::staticMetaObject,
    qt_meta_stringdata_uFirstPage.data,
    qt_meta_data_uFirstPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uFirstPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uFirstPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uFirstPage.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int uFirstPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
void uFirstPage::chooseFileClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void uFirstPage::exitProgramClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_uTitlePage_t {
    QByteArrayData data[12];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uTitlePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uTitlePage_t qt_meta_stringdata_uTitlePage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "uTitlePage"
QT_MOC_LITERAL(1, 11, 7), // "timeout"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "setTitleInfo"
QT_MOC_LITERAL(4, 33, 10), // "Main_Title"
QT_MOC_LITERAL(5, 44, 9), // "Sub_Title"
QT_MOC_LITERAL(6, 54, 10), // "Background"
QT_MOC_LITERAL(7, 65, 4), // "Logo"
QT_MOC_LITERAL(8, 70, 8), // "showPage"
QT_MOC_LITERAL(9, 79, 13), // "playAnimation"
QT_MOC_LITERAL(10, 93, 14), // "_playAnimation"
QT_MOC_LITERAL(11, 108, 8) // "hidePage"

    },
    "uTitlePage\0timeout\0\0setTitleInfo\0"
    "Main_Title\0Sub_Title\0Background\0Logo\0"
    "showPage\0playAnimation\0_playAnimation\0"
    "hidePage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uTitlePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    4,   45,    2, 0x0a /* Public */,
       8,    0,   54,    2, 0x0a /* Public */,
       9,    0,   55,    2, 0x0a /* Public */,
      10,    0,   56,    2, 0x0a /* Public */,
      11,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void uTitlePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<uTitlePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeout(); break;
        case 1: _t->setTitleInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->showPage(); break;
        case 3: _t->playAnimation(); break;
        case 4: _t->_playAnimation(); break;
        case 5: _t->hidePage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (uTitlePage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uTitlePage::timeout)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject uTitlePage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_uTitlePage.data,
    qt_meta_data_uTitlePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uTitlePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uTitlePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uTitlePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int uTitlePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void uTitlePage::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_uScrollPage_t {
    QByteArrayData data[12];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uScrollPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uScrollPage_t qt_meta_stringdata_uScrollPage = {
    {
QT_MOC_LITERAL(0, 0, 11), // "uScrollPage"
QT_MOC_LITERAL(1, 12, 12), // "EmitJumpLine"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "initObject"
QT_MOC_LITERAL(4, 37, 11), // "setLineList"
QT_MOC_LITERAL(5, 49, 9), // "StoryLine"
QT_MOC_LITERAL(6, 59, 9), // "setScroll"
QT_MOC_LITERAL(7, 69, 13), // "UpdateLineNum"
QT_MOC_LITERAL(8, 83, 8), // "LineInfo"
QT_MOC_LITERAL(9, 92, 10), // "MoveBigPad"
QT_MOC_LITERAL(10, 103, 3), // "num"
QT_MOC_LITERAL(11, 107, 11) // "EmitLineNum"

    },
    "uScrollPage\0EmitJumpLine\0\0initObject\0"
    "setLineList\0StoryLine\0setScroll\0"
    "UpdateLineNum\0LineInfo\0MoveBigPad\0num\0"
    "EmitLineNum"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uScrollPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   52,    2, 0x0a /* Public */,
       4,    1,   53,    2, 0x0a /* Public */,
       6,    0,   56,    2, 0x0a /* Public */,
       7,    1,   57,    2, 0x0a /* Public */,
       9,    1,   60,    2, 0x0a /* Public */,
      11,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void uScrollPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<uScrollPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EmitJumpLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->initObject(); break;
        case 2: _t->setLineList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->setScroll(); break;
        case 4: _t->UpdateLineNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->MoveBigPad((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->EmitLineNum(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (uScrollPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uScrollPage::EmitJumpLine)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject uScrollPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_uScrollPage.data,
    qt_meta_data_uScrollPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uScrollPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uScrollPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uScrollPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int uScrollPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void uScrollPage::EmitJumpLine(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_uPlayerPage_t {
    QByteArrayData data[53];
    char stringdata0[619];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uPlayerPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uPlayerPage_t qt_meta_stringdata_uPlayerPage = {
    {
QT_MOC_LITERAL(0, 0, 11), // "uPlayerPage"
QT_MOC_LITERAL(1, 12, 12), // "UserSpeedSet"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "UserChooseWhich"
QT_MOC_LITERAL(4, 42, 11), // "NowInBranch"
QT_MOC_LITERAL(5, 54, 10), // "NeedWakeUp"
QT_MOC_LITERAL(6, 65, 8), // "NowInLog"
QT_MOC_LITERAL(7, 74, 10), // "initObject"
QT_MOC_LITERAL(8, 85, 15), // "searchParameter"
QT_MOC_LITERAL(9, 101, 13), // "Parametername"
QT_MOC_LITERAL(10, 115, 15), // "setBranchButton"
QT_MOC_LITERAL(11, 131, 10), // "BranchList"
QT_MOC_LITERAL(12, 142, 14), // "showPlayerPage"
QT_MOC_LITERAL(13, 157, 15), // "setCurrentFrame"
QT_MOC_LITERAL(14, 173, 12), // "FrameOpacity"
QT_MOC_LITERAL(15, 186, 13), // "setCurrentAvg"
QT_MOC_LITERAL(16, 200, 18), // "QList<QStringList>"
QT_MOC_LITERAL(17, 219, 12), // "CharaPicList"
QT_MOC_LITERAL(18, 232, 8), // "Charanum"
QT_MOC_LITERAL(19, 241, 16), // "updateCurrentAvg"
QT_MOC_LITERAL(20, 258, 8), // "whichAvg"
QT_MOC_LITERAL(21, 267, 7), // "OpFloat"
QT_MOC_LITERAL(22, 275, 18), // "updateCurrentWords"
QT_MOC_LITERAL(23, 294, 4), // "Name"
QT_MOC_LITERAL(24, 299, 12), // "WordsCurrent"
QT_MOC_LITERAL(25, 312, 8), // "FirstSet"
QT_MOC_LITERAL(26, 321, 13), // "setCurrentBGP"
QT_MOC_LITERAL(27, 335, 10), // "BGPSetList"
QT_MOC_LITERAL(28, 346, 16), // "updateCurrentBGP"
QT_MOC_LITERAL(29, 363, 13), // "Opacity_Float"
QT_MOC_LITERAL(30, 377, 9), // "BGSetList"
QT_MOC_LITERAL(31, 387, 14), // "setCurrentFree"
QT_MOC_LITERAL(32, 402, 10), // "textsetlst"
QT_MOC_LITERAL(33, 413, 7), // "wordset"
QT_MOC_LITERAL(34, 421, 17), // "updateCurrentFree"
QT_MOC_LITERAL(35, 439, 5), // "Words"
QT_MOC_LITERAL(36, 445, 16), // "clearCurrentFree"
QT_MOC_LITERAL(37, 462, 3), // "end"
QT_MOC_LITERAL(38, 466, 8), // "clearAll"
QT_MOC_LITERAL(39, 475, 10), // "wheelEvent"
QT_MOC_LITERAL(40, 486, 12), // "QWheelEvent*"
QT_MOC_LITERAL(41, 499, 5), // "event"
QT_MOC_LITERAL(42, 505, 10), // "_ShakeRect"
QT_MOC_LITERAL(43, 516, 2), // "sX"
QT_MOC_LITERAL(44, 519, 2), // "sY"
QT_MOC_LITERAL(45, 522, 11), // "_FlashWhite"
QT_MOC_LITERAL(46, 534, 11), // "_AutoChange"
QT_MOC_LITERAL(47, 546, 17), // "repaintAutoButton"
QT_MOC_LITERAL(48, 564, 12), // "_SpeedChange"
QT_MOC_LITERAL(49, 577, 12), // "_Chooselabel"
QT_MOC_LITERAL(50, 590, 8), // "showNext"
QT_MOC_LITERAL(51, 599, 7), // "_ToNext"
QT_MOC_LITERAL(52, 607, 11) // "showLogPage"

    },
    "uPlayerPage\0UserSpeedSet\0\0UserChooseWhich\0"
    "NowInBranch\0NeedWakeUp\0NowInLog\0"
    "initObject\0searchParameter\0Parametername\0"
    "setBranchButton\0BranchList\0showPlayerPage\0"
    "setCurrentFrame\0FrameOpacity\0setCurrentAvg\0"
    "QList<QStringList>\0CharaPicList\0"
    "Charanum\0updateCurrentAvg\0whichAvg\0"
    "OpFloat\0updateCurrentWords\0Name\0"
    "WordsCurrent\0FirstSet\0setCurrentBGP\0"
    "BGPSetList\0updateCurrentBGP\0Opacity_Float\0"
    "BGSetList\0setCurrentFree\0textsetlst\0"
    "wordset\0updateCurrentFree\0Words\0"
    "clearCurrentFree\0end\0clearAll\0wheelEvent\0"
    "QWheelEvent*\0event\0_ShakeRect\0sX\0sY\0"
    "_FlashWhite\0_AutoChange\0repaintAutoButton\0"
    "_SpeedChange\0_Chooselabel\0showNext\0"
    "_ToNext\0showLogPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uPlayerPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  159,    2, 0x06 /* Public */,
       3,    1,  162,    2, 0x06 /* Public */,
       4,    0,  165,    2, 0x06 /* Public */,
       5,    0,  166,    2, 0x06 /* Public */,
       6,    0,  167,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  168,    2, 0x0a /* Public */,
       8,    1,  169,    2, 0x0a /* Public */,
      10,    1,  172,    2, 0x0a /* Public */,
      12,    0,  175,    2, 0x0a /* Public */,
      13,    1,  176,    2, 0x0a /* Public */,
      15,    2,  179,    2, 0x0a /* Public */,
      19,    2,  184,    2, 0x0a /* Public */,
      22,    3,  189,    2, 0x0a /* Public */,
      26,    1,  196,    2, 0x0a /* Public */,
      28,    2,  199,    2, 0x0a /* Public */,
      31,    2,  204,    2, 0x0a /* Public */,
      34,    1,  209,    2, 0x0a /* Public */,
      36,    1,  212,    2, 0x0a /* Public */,
      38,    0,  215,    2, 0x0a /* Public */,
      39,    1,  216,    2, 0x0a /* Public */,
      42,    3,  219,    2, 0x0a /* Public */,
      45,    2,  226,    2, 0x0a /* Public */,
      46,    0,  231,    2, 0x0a /* Public */,
      47,    0,  232,    2, 0x0a /* Public */,
      48,    0,  233,    2, 0x0a /* Public */,
      49,    0,  234,    2, 0x0a /* Public */,
      50,    0,  235,    2, 0x0a /* Public */,
      51,    0,  236,    2, 0x0a /* Public */,
      52,    0,  237,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QStringList,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   17,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,   20,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   23,   24,   25,
    QMetaType::Void, QMetaType::QStringList,   27,
    QMetaType::Void, QMetaType::Float, QMetaType::QStringList,   29,   30,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList,   32,   33,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 40,   41,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   44,   37,
    QMetaType::Void, QMetaType::Float, QMetaType::Int,   29,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void uPlayerPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<uPlayerPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UserSpeedSet((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->UserChooseWhich((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->NowInBranch(); break;
        case 3: _t->NeedWakeUp(); break;
        case 4: _t->NowInLog(); break;
        case 5: _t->initObject(); break;
        case 6: { int _r = _t->searchParameter((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setBranchButton((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->showPlayerPage(); break;
        case 9: _t->setCurrentFrame((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setCurrentAvg((*reinterpret_cast< QList<QStringList>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->updateCurrentAvg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 12: _t->updateCurrentWords((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 13: _t->setCurrentBGP((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 14: _t->updateCurrentBGP((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 15: _t->setCurrentFree((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 16: _t->updateCurrentFree((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->clearCurrentFree((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->clearAll(); break;
        case 19: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 20: _t->_ShakeRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 21: _t->_FlashWhite((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->_AutoChange(); break;
        case 23: _t->repaintAutoButton(); break;
        case 24: _t->_SpeedChange(); break;
        case 25: _t->_Chooselabel(); break;
        case 26: _t->showNext(); break;
        case 27: _t->_ToNext(); break;
        case 28: _t->showLogPage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QStringList> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (uPlayerPage::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uPlayerPage::UserSpeedSet)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (uPlayerPage::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uPlayerPage::UserChooseWhich)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (uPlayerPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uPlayerPage::NowInBranch)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (uPlayerPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uPlayerPage::NeedWakeUp)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (uPlayerPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&uPlayerPage::NowInLog)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject uPlayerPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_uPlayerPage.data,
    qt_meta_data_uPlayerPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uPlayerPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uPlayerPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uPlayerPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int uPlayerPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void uPlayerPage::UserSpeedSet(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void uPlayerPage::UserChooseWhich(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void uPlayerPage::NowInBranch()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void uPlayerPage::NeedWakeUp()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void uPlayerPage::NowInLog()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
struct qt_meta_stringdata_uSoundService_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uSoundService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uSoundService_t qt_meta_stringdata_uSoundService = {
    {
QT_MOC_LITERAL(0, 0, 13) // "uSoundService"

    },
    "uSoundService"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uSoundService[] = {

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

void uSoundService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject uSoundService::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_uSoundService.data,
    qt_meta_data_uSoundService,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uSoundService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uSoundService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uSoundService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int uSoundService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
