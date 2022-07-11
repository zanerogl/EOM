/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../V1_0/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_quit_button_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 23), // "on_clear_button_clicked"
QT_MOC_LITERAL(4, 59, 17), // "local_camera_open"
QT_MOC_LITERAL(5, 77, 14), // "camera_capture"
QT_MOC_LITERAL(6, 92, 7), // "cv::Mat"
QT_MOC_LITERAL(7, 100, 5), // "frame"
QT_MOC_LITERAL(8, 106, 16), // "server_open_port"
QT_MOC_LITERAL(9, 123, 4), // "port"
QT_MOC_LITERAL(10, 128, 11), // "server_send"
QT_MOC_LITERAL(11, 140, 4), // "data"
QT_MOC_LITERAL(12, 145, 14), // "templates_show"
QT_MOC_LITERAL(13, 160, 13), // "temp_function"
QT_MOC_LITERAL(14, 174, 18), // "on_capture_clicked"
QT_MOC_LITERAL(15, 193, 26), // "on_clear_templates_clicked"
QT_MOC_LITERAL(16, 220, 15), // "on_test_clicked"
QT_MOC_LITERAL(17, 236, 25) // "on_server_startup_clicked"

    },
    "MainWindow\0on_quit_button_clicked\0\0"
    "on_clear_button_clicked\0local_camera_open\0"
    "camera_capture\0cv::Mat\0frame\0"
    "server_open_port\0port\0server_send\0"
    "data\0templates_show\0temp_function\0"
    "on_capture_clicked\0on_clear_templates_clicked\0"
    "on_test_clicked\0on_server_startup_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    1,   77,    2, 0x08 /* Private */,
       8,    1,   80,    2, 0x08 /* Private */,
      10,    1,   83,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,
      16,    0,   90,    2, 0x08 /* Private */,
      17,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 6, 0x80000000 | 6,    7,
    QMetaType::Bool, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_quit_button_clicked(); break;
        case 1: _t->on_clear_button_clicked(); break;
        case 2: _t->local_camera_open(); break;
        case 3: { cv::Mat _r = _t->camera_capture((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< cv::Mat*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->server_open_port((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->server_send((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->templates_show(); break;
        case 7: _t->temp_function(); break;
        case 8: _t->on_capture_clicked(); break;
        case 9: _t->on_clear_templates_clicked(); break;
        case 10: _t->on_test_clicked(); break;
        case 11: _t->on_server_startup_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
