/****************************************************************************
** Meta object code from reading C++ file 'GameWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/GameWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_GameWindow_t {
    uint offsetsAndSizes[22];
    char stringdata0[11];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[20];
    char stringdata5[16];
    char stringdata6[22];
    char stringdata7[26];
    char stringdata8[19];
    char stringdata9[10];
    char stringdata10[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GameWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_GameWindow_t qt_meta_stringdata_GameWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "GameWindow"
        QT_MOC_LITERAL(11, 20),  // "onStartGameRequested"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 18),  // "onRestartRequested"
        QT_MOC_LITERAL(52, 19),  // "onMainMenuRequested"
        QT_MOC_LITERAL(72, 15),  // "onExitRequested"
        QT_MOC_LITERAL(88, 21),  // "onScoreboardRequested"
        QT_MOC_LITERAL(110, 25),  // "onScoreboardBackRequested"
        QT_MOC_LITERAL(136, 18),  // "onGameStateChanged"
        QT_MOC_LITERAL(155, 9),  // "GameState"
        QT_MOC_LITERAL(165, 8)   // "newState"
    },
    "GameWindow",
    "onStartGameRequested",
    "",
    "onRestartRequested",
    "onMainMenuRequested",
    "onExitRequested",
    "onScoreboardRequested",
    "onScoreboardBackRequested",
    "onGameStateChanged",
    "GameState",
    "newState"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_GameWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    6 /* Private */,
       8,    1,   62,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_GameWindow.offsetsAndSizes,
    qt_meta_data_GameWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_GameWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameWindow, std::true_type>,
        // method 'onStartGameRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRestartRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMainMenuRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onExitRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onScoreboardRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onScoreboardBackRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGameStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<GameState, std::false_type>
    >,
    nullptr
} };

void GameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onStartGameRequested(); break;
        case 1: _t->onRestartRequested(); break;
        case 2: _t->onMainMenuRequested(); break;
        case 3: _t->onExitRequested(); break;
        case 4: _t->onScoreboardRequested(); break;
        case 5: _t->onScoreboardBackRequested(); break;
        case 6: _t->onGameStateChanged((*reinterpret_cast< std::add_pointer_t<GameState>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *GameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
