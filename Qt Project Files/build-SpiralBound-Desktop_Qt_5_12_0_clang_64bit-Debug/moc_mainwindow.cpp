/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SpiralBound/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[37];
    char stringdata0[920];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "sendEditData"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 24), // "on_action_open_triggered"
QT_MOC_LITERAL(4, 50, 24), // "on_action_test_triggered"
QT_MOC_LITERAL(5, 75, 24), // "on_action_save_triggered"
QT_MOC_LITERAL(6, 100, 25), // "on_action_about_triggered"
QT_MOC_LITERAL(7, 126, 27), // "on_action_aboutQt_triggered"
QT_MOC_LITERAL(8, 154, 31), // "on_action_crashCourse_triggered"
QT_MOC_LITERAL(9, 186, 25), // "on_action_print_triggered"
QT_MOC_LITERAL(10, 212, 23), // "on_action_new_triggered"
QT_MOC_LITERAL(11, 236, 30), // "on_action_openRecent_triggered"
QT_MOC_LITERAL(12, 267, 26), // "on_action_saveAs_triggered"
QT_MOC_LITERAL(13, 294, 24), // "on_action_bold_triggered"
QT_MOC_LITERAL(14, 319, 26), // "on_action_italic_triggered"
QT_MOC_LITERAL(15, 346, 29), // "on_action_underline_triggered"
QT_MOC_LITERAL(16, 376, 27), // "on_action_comment_triggered"
QT_MOC_LITERAL(17, 404, 33), // "on_action_strikethrough_trigg..."
QT_MOC_LITERAL(18, 438, 26), // "on_action_indent_triggered"
QT_MOC_LITERAL(19, 465, 28), // "on_action_unindent_triggered"
QT_MOC_LITERAL(20, 494, 32), // "on_action_bulletedList_triggered"
QT_MOC_LITERAL(21, 527, 32), // "on_action_numberedList_triggered"
QT_MOC_LITERAL(22, 560, 28), // "on_action_taskList_triggered"
QT_MOC_LITERAL(23, 589, 31), // "on_action_preferences_triggered"
QT_MOC_LITERAL(24, 621, 32), // "on_action_printPreview_triggered"
QT_MOC_LITERAL(25, 654, 26), // "on_action_export_triggered"
QT_MOC_LITERAL(26, 681, 24), // "on_action_quit_triggered"
QT_MOC_LITERAL(27, 706, 30), // "on_pushButton_addEvent_clicked"
QT_MOC_LITERAL(28, 737, 33), // "on_pushButton_deleteEvent_cli..."
QT_MOC_LITERAL(29, 771, 31), // "on_pushButton_editEvent_clicked"
QT_MOC_LITERAL(30, 803, 14), // "receiveAddData"
QT_MOC_LITERAL(31, 818, 15), // "receiveEditData"
QT_MOC_LITERAL(32, 834, 17), // "receiveDeleteData"
QT_MOC_LITERAL(33, 852, 19), // "stretchTableHeaders"
QT_MOC_LITERAL(34, 872, 36), // "on_tableWidget_eventList_cell..."
QT_MOC_LITERAL(35, 909, 3), // "row"
QT_MOC_LITERAL(36, 913, 6) // "column"

    },
    "MainWindow\0sendEditData\0\0"
    "on_action_open_triggered\0"
    "on_action_test_triggered\0"
    "on_action_save_triggered\0"
    "on_action_about_triggered\0"
    "on_action_aboutQt_triggered\0"
    "on_action_crashCourse_triggered\0"
    "on_action_print_triggered\0"
    "on_action_new_triggered\0"
    "on_action_openRecent_triggered\0"
    "on_action_saveAs_triggered\0"
    "on_action_bold_triggered\0"
    "on_action_italic_triggered\0"
    "on_action_underline_triggered\0"
    "on_action_comment_triggered\0"
    "on_action_strikethrough_triggered\0"
    "on_action_indent_triggered\0"
    "on_action_unindent_triggered\0"
    "on_action_bulletedList_triggered\0"
    "on_action_numberedList_triggered\0"
    "on_action_taskList_triggered\0"
    "on_action_preferences_triggered\0"
    "on_action_printPreview_triggered\0"
    "on_action_export_triggered\0"
    "on_action_quit_triggered\0"
    "on_pushButton_addEvent_clicked\0"
    "on_pushButton_deleteEvent_clicked\0"
    "on_pushButton_editEvent_clicked\0"
    "receiveAddData\0receiveEditData\0"
    "receiveDeleteData\0stretchTableHeaders\0"
    "on_tableWidget_eventList_cellChanged\0"
    "row\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  179,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  186,    2, 0x08 /* Private */,
       4,    0,  187,    2, 0x08 /* Private */,
       5,    0,  188,    2, 0x08 /* Private */,
       6,    0,  189,    2, 0x08 /* Private */,
       7,    0,  190,    2, 0x08 /* Private */,
       8,    0,  191,    2, 0x08 /* Private */,
       9,    0,  192,    2, 0x08 /* Private */,
      10,    0,  193,    2, 0x08 /* Private */,
      11,    0,  194,    2, 0x08 /* Private */,
      12,    0,  195,    2, 0x08 /* Private */,
      13,    0,  196,    2, 0x08 /* Private */,
      14,    0,  197,    2, 0x08 /* Private */,
      15,    0,  198,    2, 0x08 /* Private */,
      16,    0,  199,    2, 0x08 /* Private */,
      17,    0,  200,    2, 0x08 /* Private */,
      18,    0,  201,    2, 0x08 /* Private */,
      19,    0,  202,    2, 0x08 /* Private */,
      20,    0,  203,    2, 0x08 /* Private */,
      21,    0,  204,    2, 0x08 /* Private */,
      22,    0,  205,    2, 0x08 /* Private */,
      23,    0,  206,    2, 0x08 /* Private */,
      24,    0,  207,    2, 0x08 /* Private */,
      25,    0,  208,    2, 0x08 /* Private */,
      26,    0,  209,    2, 0x08 /* Private */,
      27,    0,  210,    2, 0x08 /* Private */,
      28,    0,  211,    2, 0x08 /* Private */,
      29,    0,  212,    2, 0x08 /* Private */,
      30,    2,  213,    2, 0x08 /* Private */,
      31,    2,  218,    2, 0x08 /* Private */,
      32,    1,  223,    2, 0x08 /* Private */,
      33,    0,  226,    2, 0x08 /* Private */,
      34,    2,  227,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,

 // slots: parameters
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
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   35,   36,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendEditData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->on_action_open_triggered(); break;
        case 2: _t->on_action_test_triggered(); break;
        case 3: _t->on_action_save_triggered(); break;
        case 4: _t->on_action_about_triggered(); break;
        case 5: _t->on_action_aboutQt_triggered(); break;
        case 6: _t->on_action_crashCourse_triggered(); break;
        case 7: _t->on_action_print_triggered(); break;
        case 8: _t->on_action_new_triggered(); break;
        case 9: _t->on_action_openRecent_triggered(); break;
        case 10: _t->on_action_saveAs_triggered(); break;
        case 11: _t->on_action_bold_triggered(); break;
        case 12: _t->on_action_italic_triggered(); break;
        case 13: _t->on_action_underline_triggered(); break;
        case 14: _t->on_action_comment_triggered(); break;
        case 15: _t->on_action_strikethrough_triggered(); break;
        case 16: _t->on_action_indent_triggered(); break;
        case 17: _t->on_action_unindent_triggered(); break;
        case 18: _t->on_action_bulletedList_triggered(); break;
        case 19: _t->on_action_numberedList_triggered(); break;
        case 20: _t->on_action_taskList_triggered(); break;
        case 21: _t->on_action_preferences_triggered(); break;
        case 22: _t->on_action_printPreview_triggered(); break;
        case 23: _t->on_action_export_triggered(); break;
        case 24: _t->on_action_quit_triggered(); break;
        case 25: _t->on_pushButton_addEvent_clicked(); break;
        case 26: _t->on_pushButton_deleteEvent_clicked(); break;
        case 27: _t->on_pushButton_editEvent_clicked(); break;
        case 28: _t->receiveAddData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: _t->receiveEditData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 30: _t->receiveDeleteData((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->stretchTableHeaders(); break;
        case 32: _t->on_tableWidget_eventList_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendEditData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
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
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sendEditData(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
