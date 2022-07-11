/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../5/mainwindow.h"
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
    QByteArrayData data[22];
    char stringdata0[307];
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
QT_MOC_LITERAL(5, 77, 14), // "ip_camera_open"
QT_MOC_LITERAL(6, 92, 11), // "std::string"
QT_MOC_LITERAL(7, 104, 7), // "address"
QT_MOC_LITERAL(8, 112, 4), // "port"
QT_MOC_LITERAL(9, 117, 14), // "camera_capture"
QT_MOC_LITERAL(10, 132, 7), // "cv::Mat"
QT_MOC_LITERAL(11, 140, 5), // "frame"
QT_MOC_LITERAL(12, 146, 16), // "server_open_port"
QT_MOC_LITERAL(13, 163, 24), // "server_accept_connection"
QT_MOC_LITERAL(14, 188, 11), // "server_send"
QT_MOC_LITERAL(15, 200, 4), // "data"
QT_MOC_LITERAL(16, 205, 4), // "temp"
QT_MOC_LITERAL(17, 210, 12), // "detect_color"
QT_MOC_LITERAL(18, 223, 11), // "imgOriginal"
QT_MOC_LITERAL(19, 235, 25), // "on_Server_startup_clicked"
QT_MOC_LITERAL(20, 261, 18), // "on_capture_clicked"
QT_MOC_LITERAL(21, 280, 26) // "on_clear_templates_clicked"

    },
    "MainWindow\0on_quit_button_clicked\0\0"
    "on_clear_button_clicked\0local_camera_open\0"
    "ip_camera_open\0std::string\0address\0"
    "port\0camera_capture\0cv::Mat\0frame\0"
    "server_open_port\0server_accept_connection\0"
    "server_send\0data\0temp\0detect_color\0"
    "imgOriginal\0on_Server_startup_clicked\0"
    "on_capture_clicked\0on_clear_templates_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    2,   82,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      12,    1,   90,    2, 0x08 /* Private */,
      13,    0,   93,    2, 0x08 /* Private */,
      14,    1,   94,    2, 0x08 /* Private */,
      16,    1,   97,    2, 0x08 /* Private */,
      17,    1,  100,    2, 0x08 /* Private */,
      19,    0,  103,    2, 0x08 /* Private */,
      20,    0,  104,    2, 0x08 /* Private */,
      21,    0,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    0x80000000 | 10, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    0x80000000 | 6, 0x80000000 | 10,   11,
    0x80000000 | 6, 0x80000000 | 10,   18,
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
        case 3: _t->ip_camera_open((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 4: { cv::Mat _r = _t->camera_capture((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< cv::Mat*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->server_open_port((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->server_accept_connection(); break;
        case 7: _t->server_send((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: { std::string _r = _t->temp((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 9: { std::string _r = _t->detect_color((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->on_Server_startup_clicked(); break;
        case 11: _t->on_capture_clicked(); break;
        case 12: _t->on_clear_templates_clicked(); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
