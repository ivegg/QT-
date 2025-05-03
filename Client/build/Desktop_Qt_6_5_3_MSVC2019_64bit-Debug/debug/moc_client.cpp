/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../client.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSClientENDCLASS = QtMocHelpers::stringData(
    "Client",
    "iconChanged",
    "",
    "url",
    "on_pushBtn_close_clicked",
    "on_pushBtn_hide_clicked",
    "on_pushBtn_max_clicked",
    "on_pushButton_emoj_3_clicked",
    "on_pushButton_msg_list_clicked",
    "on_pushButton_friend_list_clicked",
    "on_pushButton_group_list_clicked",
    "on_pushButton_system_msg_clicked",
    "on_pushButton_icon_clicked",
    "on_pushButton_emoj_clicked",
    "on_pushButton_image_clicked",
    "on_pushButton_addFriend_clicked",
    "on_pushBtn_refresh_clicked",
    "on_listWidget_info_itemClicked",
    "QListWidgetItem*",
    "item",
    "on_groupsListWidget_itemClicked",
    "on_pushBtn_send_clicked",
    "insertEmoji",
    "emoji",
    "ClientMsgHandler",
    "json",
    "msg"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSClientENDCLASS_t {
    uint offsetsAndSizes[54];
    char stringdata0[7];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[25];
    char stringdata5[24];
    char stringdata6[23];
    char stringdata7[29];
    char stringdata8[31];
    char stringdata9[34];
    char stringdata10[33];
    char stringdata11[33];
    char stringdata12[27];
    char stringdata13[27];
    char stringdata14[28];
    char stringdata15[32];
    char stringdata16[27];
    char stringdata17[31];
    char stringdata18[17];
    char stringdata19[5];
    char stringdata20[32];
    char stringdata21[24];
    char stringdata22[12];
    char stringdata23[6];
    char stringdata24[17];
    char stringdata25[5];
    char stringdata26[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSClientENDCLASS_t qt_meta_stringdata_CLASSClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Client"
        QT_MOC_LITERAL(7, 11),  // "iconChanged"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 3),  // "url"
        QT_MOC_LITERAL(24, 24),  // "on_pushBtn_close_clicked"
        QT_MOC_LITERAL(49, 23),  // "on_pushBtn_hide_clicked"
        QT_MOC_LITERAL(73, 22),  // "on_pushBtn_max_clicked"
        QT_MOC_LITERAL(96, 28),  // "on_pushButton_emoj_3_clicked"
        QT_MOC_LITERAL(125, 30),  // "on_pushButton_msg_list_clicked"
        QT_MOC_LITERAL(156, 33),  // "on_pushButton_friend_list_cli..."
        QT_MOC_LITERAL(190, 32),  // "on_pushButton_group_list_clicked"
        QT_MOC_LITERAL(223, 32),  // "on_pushButton_system_msg_clicked"
        QT_MOC_LITERAL(256, 26),  // "on_pushButton_icon_clicked"
        QT_MOC_LITERAL(283, 26),  // "on_pushButton_emoj_clicked"
        QT_MOC_LITERAL(310, 27),  // "on_pushButton_image_clicked"
        QT_MOC_LITERAL(338, 31),  // "on_pushButton_addFriend_clicked"
        QT_MOC_LITERAL(370, 26),  // "on_pushBtn_refresh_clicked"
        QT_MOC_LITERAL(397, 30),  // "on_listWidget_info_itemClicked"
        QT_MOC_LITERAL(428, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(445, 4),  // "item"
        QT_MOC_LITERAL(450, 31),  // "on_groupsListWidget_itemClicked"
        QT_MOC_LITERAL(482, 23),  // "on_pushBtn_send_clicked"
        QT_MOC_LITERAL(506, 11),  // "insertEmoji"
        QT_MOC_LITERAL(518, 5),  // "emoji"
        QT_MOC_LITERAL(524, 16),  // "ClientMsgHandler"
        QT_MOC_LITERAL(541, 4),  // "json"
        QT_MOC_LITERAL(546, 3)   // "msg"
    },
    "Client",
    "iconChanged",
    "",
    "url",
    "on_pushBtn_close_clicked",
    "on_pushBtn_hide_clicked",
    "on_pushBtn_max_clicked",
    "on_pushButton_emoj_3_clicked",
    "on_pushButton_msg_list_clicked",
    "on_pushButton_friend_list_clicked",
    "on_pushButton_group_list_clicked",
    "on_pushButton_system_msg_clicked",
    "on_pushButton_icon_clicked",
    "on_pushButton_emoj_clicked",
    "on_pushButton_image_clicked",
    "on_pushButton_addFriend_clicked",
    "on_pushBtn_refresh_clicked",
    "on_listWidget_info_itemClicked",
    "QListWidgetItem*",
    "item",
    "on_groupsListWidget_itemClicked",
    "on_pushBtn_send_clicked",
    "insertEmoji",
    "emoji",
    "ClientMsgHandler",
    "json",
    "msg"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSClientENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  128,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  131,    2, 0x08,    3 /* Private */,
       5,    0,  132,    2, 0x08,    4 /* Private */,
       6,    0,  133,    2, 0x08,    5 /* Private */,
       7,    0,  134,    2, 0x08,    6 /* Private */,
       8,    0,  135,    2, 0x08,    7 /* Private */,
       9,    0,  136,    2, 0x08,    8 /* Private */,
      10,    0,  137,    2, 0x08,    9 /* Private */,
      11,    0,  138,    2, 0x08,   10 /* Private */,
      12,    0,  139,    2, 0x08,   11 /* Private */,
      13,    0,  140,    2, 0x08,   12 /* Private */,
      14,    0,  141,    2, 0x08,   13 /* Private */,
      15,    0,  142,    2, 0x0a,   14 /* Public */,
      16,    0,  143,    2, 0x0a,   15 /* Public */,
      17,    1,  144,    2, 0x0a,   16 /* Public */,
      20,    1,  147,    2, 0x0a,   18 /* Public */,
      21,    0,  150,    2, 0x0a,   20 /* Public */,
      22,    1,  151,    2, 0x0a,   21 /* Public */,
      24,    1,  154,    2, 0x0a,   23 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

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
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, 0x80000000 | 25,   26,

       0        // eod
};

Q_CONSTINIT const QMetaObject Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Client, std::true_type>,
        // method 'iconChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_pushBtn_close_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushBtn_hide_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushBtn_max_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_emoj_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_msg_list_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_friend_list_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_group_list_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_system_msg_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_icon_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_emoj_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_image_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_addFriend_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushBtn_refresh_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_listWidget_info_itemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_groupsListWidget_itemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_pushBtn_send_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'insertEmoji'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'ClientMsgHandler'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<json, std::false_type>
    >,
    nullptr
} };

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->iconChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->on_pushBtn_close_clicked(); break;
        case 2: _t->on_pushBtn_hide_clicked(); break;
        case 3: _t->on_pushBtn_max_clicked(); break;
        case 4: _t->on_pushButton_emoj_3_clicked(); break;
        case 5: _t->on_pushButton_msg_list_clicked(); break;
        case 6: _t->on_pushButton_friend_list_clicked(); break;
        case 7: _t->on_pushButton_group_list_clicked(); break;
        case 8: _t->on_pushButton_system_msg_clicked(); break;
        case 9: _t->on_pushButton_icon_clicked(); break;
        case 10: _t->on_pushButton_emoj_clicked(); break;
        case 11: _t->on_pushButton_image_clicked(); break;
        case 12: _t->on_pushButton_addFriend_clicked(); break;
        case 13: _t->on_pushBtn_refresh_clicked(); break;
        case 14: _t->on_listWidget_info_itemClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 15: _t->on_groupsListWidget_itemClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 16: _t->on_pushBtn_send_clicked(); break;
        case 17: _t->insertEmoji((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->ClientMsgHandler((*reinterpret_cast< std::add_pointer_t<json>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Client::*)(QString );
            if (_t _q_method = &Client::iconChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Client::iconChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
