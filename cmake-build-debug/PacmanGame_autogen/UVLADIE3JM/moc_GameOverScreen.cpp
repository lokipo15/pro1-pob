/****************************************************************************
** Meta object code from reading C++ file 'GameOverScreen.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/GameOverScreen.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameOverScreen.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_GameOverScreen_t {
    uint offsetsAndSizes[22];
    char stringdata0[15];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[14];
    char stringdata5[20];
    char stringdata6[17];
    char stringdata7[18];
    char stringdata8[14];
    char stringdata9[20];
    char stringdata10[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GameOverScreen_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_GameOverScreen_t qt_meta_stringdata_GameOverScreen = {
    {
        QT_MOC_LITERAL(0, 14),  // "GameOverScreen"
        QT_MOC_LITERAL(15, 16),  // "restartRequested"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 17),  // "mainMenuRequested"
        QT_MOC_LITERAL(51, 13),  // "exitRequested"
        QT_MOC_LITERAL(65, 19),  // "scoreboardRequested"
        QT_MOC_LITERAL(85, 16),  // "onRestartClicked"
        QT_MOC_LITERAL(102, 17),  // "onMainMenuClicked"
        QT_MOC_LITERAL(120, 13),  // "onExitClicked"
        QT_MOC_LITERAL(134, 19),  // "onScoreboardClicked"
        QT_MOC_LITERAL(154, 18)   // "onSaveScoreClicked"
    },
    "GameOverScreen",
    "restartRequested",
    "",
    "mainMenuRequested",
    "exitRequested",
    "scoreboardRequested",
    "onRestartClicked",
    "onMainMenuClicked",
    "onExitClicked",
    "onScoreboardClicked",
    "onSaveScoreClicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_GameOverScreen[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,
       3,    0,   69,    2, 0x06,    2 /* Public */,
       4,    0,   70,    2, 0x06,    3 /* Public */,
       5,    0,   71,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    0,   74,    2, 0x08,    7 /* Private */,
       9,    0,   75,    2, 0x08,    8 /* Private */,
      10,    0,   76,    2, 0x08,    9 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameOverScreen::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GameOverScreen.offsetsAndSizes,
    qt_meta_data_GameOverScreen,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_GameOverScreen_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameOverScreen, std::true_type>,
        // method 'restartRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mainMenuRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scoreboardRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRestartClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMainMenuClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onExitClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onScoreboardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveScoreClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GameOverScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameOverScreen *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->restartRequested(); break;
        case 1: _t->mainMenuRequested(); break;
        case 2: _t->exitRequested(); break;
        case 3: _t->scoreboardRequested(); break;
        case 4: _t->onRestartClicked(); break;
        case 5: _t->onMainMenuClicked(); break;
        case 6: _t->onExitClicked(); break;
        case 7: _t->onScoreboardClicked(); break;
        case 8: _t->onSaveScoreClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameOverScreen::*)();
            if (_t _q_method = &GameOverScreen::restartRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameOverScreen::*)();
            if (_t _q_method = &GameOverScreen::mainMenuRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameOverScreen::*)();
            if (_t _q_method = &GameOverScreen::exitRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameOverScreen::*)();
            if (_t _q_method = &GameOverScreen::scoreboardRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *GameOverScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameOverScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameOverScreen.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameOverScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void GameOverScreen::restartRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GameOverScreen::mainMenuRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GameOverScreen::exitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GameOverScreen::scoreboardRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
