/****************************************************************************
** Meta object code from reading C++ file 'TopWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../UIFolder/TopWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TopWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_hGCPDialog_t {
    QByteArrayData data[5];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hGCPDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hGCPDialog_t qt_meta_stringdata_hGCPDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "hGCPDialog"
QT_MOC_LITERAL(1, 11, 9), // "chooseEnd"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "yesclose"
QT_MOC_LITERAL(4, 31, 7) // "noclose"

    },
    "hGCPDialog\0chooseEnd\0\0yesclose\0noclose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hGCPDialog[] = {

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
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void hGCPDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hGCPDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->chooseEnd(); break;
        case 1: _t->yesclose(); break;
        case 2: _t->noclose(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hGCPDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hGCPDialog::chooseEnd)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject hGCPDialog::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hGCPDialog.data,
    qt_meta_data_hGCPDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hGCPDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hGCPDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hGCPDialog.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hGCPDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void hGCPDialog::chooseEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_hUpdateDialog_t {
    QByteArrayData data[3];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hUpdateDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hUpdateDialog_t qt_meta_stringdata_hUpdateDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "hUpdateDialog"
QT_MOC_LITERAL(1, 14, 14), // "windowIsClosed"
QT_MOC_LITERAL(2, 29, 0) // ""

    },
    "hUpdateDialog\0windowIsClosed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hUpdateDialog[] = {

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

void hUpdateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hUpdateDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->windowIsClosed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hUpdateDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hUpdateDialog::windowIsClosed)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject hUpdateDialog::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hUpdateDialog.data,
    qt_meta_data_hUpdateDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hUpdateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hUpdateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hUpdateDialog.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hUpdateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void hUpdateDialog::windowIsClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_hFirstPage_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hFirstPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hFirstPage_t qt_meta_stringdata_hFirstPage = {
    {
QT_MOC_LITERAL(0, 0, 10) // "hFirstPage"

    },
    "hFirstPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hFirstPage[] = {

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

void hFirstPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject hFirstPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hFirstPage.data,
    qt_meta_data_hFirstPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hFirstPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hFirstPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hFirstPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hFirstPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_hSettingsPage_t {
    QByteArrayData data[4];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hSettingsPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hSettingsPage_t qt_meta_stringdata_hSettingsPage = {
    {
QT_MOC_LITERAL(0, 0, 13), // "hSettingsPage"
QT_MOC_LITERAL(1, 14, 14), // "showDevSetPage"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17) // "showNormalSetPage"

    },
    "hSettingsPage\0showDevSetPage\0\0"
    "showNormalSetPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hSettingsPage[] = {

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

void hSettingsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hSettingsPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showDevSetPage(); break;
        case 1: _t->showNormalSetPage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject hSettingsPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hSettingsPage.data,
    qt_meta_data_hSettingsPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hSettingsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hSettingsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hSettingsPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hSettingsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_hToolsPage_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hToolsPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hToolsPage_t qt_meta_stringdata_hToolsPage = {
    {
QT_MOC_LITERAL(0, 0, 10) // "hToolsPage"

    },
    "hToolsPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hToolsPage[] = {

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

void hToolsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject hToolsPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hToolsPage.data,
    qt_meta_data_hToolsPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hToolsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hToolsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hToolsPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hToolsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_hCreatePage_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hCreatePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hCreatePage_t qt_meta_stringdata_hCreatePage = {
    {
QT_MOC_LITERAL(0, 0, 11), // "hCreatePage"
QT_MOC_LITERAL(1, 12, 17), // "showSPOLDevWindow"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "hCreatePage\0showSPOLDevWindow\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hCreatePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void hCreatePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hCreatePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showSPOLDevWindow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject hCreatePage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hCreatePage.data,
    qt_meta_data_hCreatePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hCreatePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hCreatePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hCreatePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hCreatePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_hAboutPage_t {
    QByteArrayData data[3];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hAboutPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hAboutPage_t qt_meta_stringdata_hAboutPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "hAboutPage"
QT_MOC_LITERAL(1, 11, 16), // "showMoreInfoPage"
QT_MOC_LITERAL(2, 28, 0) // ""

    },
    "hAboutPage\0showMoreInfoPage\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hAboutPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void hAboutPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hAboutPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMoreInfoPage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject hAboutPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_hAboutPage.data,
    qt_meta_data_hAboutPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hAboutPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hAboutPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hAboutPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hAboutPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_TopDef_t {
    QByteArrayData data[1];
    char stringdata0[7];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TopDef_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TopDef_t qt_meta_stringdata_TopDef = {
    {
QT_MOC_LITERAL(0, 0, 6) // "TopDef"

    },
    "TopDef"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TopDef[] = {

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

void TopDef::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TopDef::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TopDef.data,
    qt_meta_data_TopDef,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TopDef::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TopDef::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TopDef.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TopDef::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TopWindow_t {
    QByteArrayData data[33];
    char stringdata0[423];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TopWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TopWindow_t qt_meta_stringdata_TopWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TopWindow"
QT_MOC_LITERAL(1, 10, 11), // "checkUpdate"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 18), // "updateDialogClosed"
QT_MOC_LITERAL(4, 42, 14), // "chooseLangFile"
QT_MOC_LITERAL(5, 57, 13), // "openAnyFolder"
QT_MOC_LITERAL(6, 71, 15), // "clearWrongImage"
QT_MOC_LITERAL(7, 87, 18), // "clearAllCacheImage"
QT_MOC_LITERAL(8, 106, 11), // "showAnyInfo"
QT_MOC_LITERAL(9, 118, 9), // "infoGroup"
QT_MOC_LITERAL(10, 128, 10), // "needToShow"
QT_MOC_LITERAL(11, 139, 11), // "nativeEvent"
QT_MOC_LITERAL(12, 151, 9), // "eventType"
QT_MOC_LITERAL(13, 161, 7), // "message"
QT_MOC_LITERAL(14, 169, 5), // "long*"
QT_MOC_LITERAL(15, 175, 6), // "result"
QT_MOC_LITERAL(16, 182, 17), // "showNormalSetPage"
QT_MOC_LITERAL(17, 200, 14), // "showDevSetPage"
QT_MOC_LITERAL(18, 215, 16), // "showMoreInfoPage"
QT_MOC_LITERAL(19, 232, 13), // "showFirstPage"
QT_MOC_LITERAL(20, 246, 13), // "hideFirstPage"
QT_MOC_LITERAL(21, 260, 14), // "showCreatePage"
QT_MOC_LITERAL(22, 275, 14), // "hideCreatePage"
QT_MOC_LITERAL(23, 290, 13), // "showToolsPage"
QT_MOC_LITERAL(24, 304, 13), // "hideToolsPage"
QT_MOC_LITERAL(25, 318, 16), // "showSettingsPage"
QT_MOC_LITERAL(26, 335, 16), // "hideSettingsPage"
QT_MOC_LITERAL(27, 352, 13), // "showAboutPage"
QT_MOC_LITERAL(28, 366, 13), // "hideAboutPage"
QT_MOC_LITERAL(29, 380, 12), // "launchUIPage"
QT_MOC_LITERAL(30, 393, 11), // "exitProgram"
QT_MOC_LITERAL(31, 405, 8), // "exitPage"
QT_MOC_LITERAL(32, 414, 8) // "exitType"

    },
    "TopWindow\0checkUpdate\0\0updateDialogClosed\0"
    "chooseLangFile\0openAnyFolder\0"
    "clearWrongImage\0clearAllCacheImage\0"
    "showAnyInfo\0infoGroup\0needToShow\0"
    "nativeEvent\0eventType\0message\0long*\0"
    "result\0showNormalSetPage\0showDevSetPage\0"
    "showMoreInfoPage\0showFirstPage\0"
    "hideFirstPage\0showCreatePage\0"
    "hideCreatePage\0showToolsPage\0hideToolsPage\0"
    "showSettingsPage\0hideSettingsPage\0"
    "showAboutPage\0hideAboutPage\0launchUIPage\0"
    "exitProgram\0exitPage\0exitType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TopWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  149,    2, 0x0a /* Public */,
       3,    0,  150,    2, 0x0a /* Public */,
       4,    0,  151,    2, 0x0a /* Public */,
       5,    0,  152,    2, 0x0a /* Public */,
       6,    0,  153,    2, 0x0a /* Public */,
       7,    0,  154,    2, 0x0a /* Public */,
       8,    2,  155,    2, 0x0a /* Public */,
       8,    1,  160,    2, 0x2a /* Public | MethodCloned */,
       8,    0,  163,    2, 0x2a /* Public | MethodCloned */,
      11,    3,  164,    2, 0x0a /* Public */,
      16,    0,  171,    2, 0x0a /* Public */,
      17,    0,  172,    2, 0x0a /* Public */,
      18,    0,  173,    2, 0x0a /* Public */,
      19,    0,  174,    2, 0x0a /* Public */,
      20,    0,  175,    2, 0x0a /* Public */,
      21,    0,  176,    2, 0x0a /* Public */,
      22,    0,  177,    2, 0x0a /* Public */,
      23,    0,  178,    2, 0x0a /* Public */,
      24,    0,  179,    2, 0x0a /* Public */,
      25,    0,  180,    2, 0x0a /* Public */,
      26,    0,  181,    2, 0x0a /* Public */,
      27,    0,  182,    2, 0x0a /* Public */,
      28,    0,  183,    2, 0x0a /* Public */,
      29,    0,  184,    2, 0x0a /* Public */,
      30,    0,  185,    2, 0x0a /* Public */,
      31,    1,  186,    2, 0x0a /* Public */,
      31,    0,  189,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QByteArray, QMetaType::VoidStar, 0x80000000 | 14,   12,   13,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void,

       0        // eod
};

void TopWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TopWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkUpdate(); break;
        case 1: _t->updateDialogClosed(); break;
        case 2: _t->chooseLangFile(); break;
        case 3: _t->openAnyFolder(); break;
        case 4: _t->clearWrongImage(); break;
        case 5: _t->clearAllCacheImage(); break;
        case 6: _t->showAnyInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->showAnyInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->showAnyInfo(); break;
        case 9: { bool _r = _t->nativeEvent((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< long*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->showNormalSetPage(); break;
        case 11: _t->showDevSetPage(); break;
        case 12: _t->showMoreInfoPage(); break;
        case 13: _t->showFirstPage(); break;
        case 14: _t->hideFirstPage(); break;
        case 15: _t->showCreatePage(); break;
        case 16: _t->hideCreatePage(); break;
        case 17: _t->showToolsPage(); break;
        case 18: _t->hideToolsPage(); break;
        case 19: _t->showSettingsPage(); break;
        case 20: _t->hideSettingsPage(); break;
        case 21: _t->showAboutPage(); break;
        case 22: _t->hideAboutPage(); break;
        case 23: _t->launchUIPage(); break;
        case 24: _t->exitProgram(); break;
        case 25: _t->exitPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->exitPage(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TopWindow::staticMetaObject = { {
    &TopDef::staticMetaObject,
    qt_meta_stringdata_TopWindow.data,
    qt_meta_data_TopWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TopWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TopWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TopWindow.stringdata0))
        return static_cast<void*>(this);
    return TopDef::qt_metacast(_clname);
}

int TopWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TopDef::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 27;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
