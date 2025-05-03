/********************************************************************************
** Form generated from reading UI file 'addfriend.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIEND_H
#define UI_ADDFRIEND_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriend
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton_search;
    QPushButton *pushButton_add;
    QPushButton *pushButton_cancel;
    QTextEdit *textEdit;
    QListWidget *listWidget;
    QRadioButton *radioButton_friend;
    QRadioButton *radioButton_group;

    void setupUi(QWidget *AddFriend)
    {
        if (AddFriend->objectName().isEmpty())
            AddFriend->setObjectName("AddFriend");
        AddFriend->resize(683, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pic/src/wechat2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddFriend->setWindowIcon(icon);
        AddFriend->setLayoutDirection(Qt::LeftToRight);
        AddFriend->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit = new QLineEdit(AddFriend);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(160, 40, 250, 40));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 1px solid gray;\n"
"    border-radius: 5px;\n"
"    padding: 2px 10px;\n"
"    font-size: 16px;\n"
"    color: black;"));
        pushButton_search = new QPushButton(AddFriend);
        pushButton_search->setObjectName("pushButton_search");
        pushButton_search->setGeometry(QRect(440, 40, 80, 40));
        pushButton_add = new QPushButton(AddFriend);
        pushButton_add->setObjectName("pushButton_add");
        pushButton_add->setGeometry(QRect(160, 410, 80, 40));
        pushButton_cancel = new QPushButton(AddFriend);
        pushButton_cancel->setObjectName("pushButton_cancel");
        pushButton_cancel->setGeometry(QRect(440, 410, 80, 40));
        textEdit = new QTextEdit(AddFriend);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(160, 310, 361, 85));
        textEdit->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 1px solid gray;\n"
"    border-radius: 5px;\n"
"    padding: 2px 10px;\n"
"    font-size: 16px;\n"
"    color: black;"));
        listWidget = new QListWidget(AddFriend);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(160, 130, 361, 171));
        radioButton_friend = new QRadioButton(AddFriend);
        radioButton_friend->setObjectName("radioButton_friend");
        radioButton_friend->setGeometry(QRect(160, 100, 71, 21));
        radioButton_friend->setChecked(true);
        radioButton_group = new QRadioButton(AddFriend);
        radioButton_group->setObjectName("radioButton_group");
        radioButton_group->setGeometry(QRect(260, 100, 71, 21));

        retranslateUi(AddFriend);

        QMetaObject::connectSlotsByName(AddFriend);
    } // setupUi

    void retranslateUi(QWidget *AddFriend)
    {
        AddFriend->setWindowTitle(QCoreApplication::translate("AddFriend", "\346\237\245\346\211\276", nullptr));
        pushButton_search->setText(QCoreApplication::translate("AddFriend", "\346\237\245\346\211\276", nullptr));
        pushButton_add->setText(QCoreApplication::translate("AddFriend", "\346\267\273\345\212\240", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("AddFriend", "\345\217\226\346\266\210", nullptr));
#if QT_CONFIG(accessibility)
        textEdit->setAccessibleDescription(QCoreApplication::translate("AddFriend", "\351\252\214\350\257\201\344\277\241\346\201\257", nullptr));
#endif // QT_CONFIG(accessibility)
        radioButton_friend->setText(QCoreApplication::translate("AddFriend", "\345\245\275\345\217\213", nullptr));
        radioButton_group->setText(QCoreApplication::translate("AddFriend", "\347\276\244\350\201\212", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriend: public Ui_AddFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIEND_H
