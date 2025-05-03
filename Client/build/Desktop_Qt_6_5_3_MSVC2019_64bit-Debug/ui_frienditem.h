/********************************************************************************
** Form generated from reading UI file 'frienditem.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDITEM_H
#define UI_FRIENDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include <friendiconlabel.h>

QT_BEGIN_NAMESPACE

class Ui_FriendItem
{
public:
    FriendIconLabel *label_icon;
    QLabel *label_name;
    QLabel *label_sig;
    QLineEdit *lineEdit_newMsg;

    void setupUi(QWidget *FriendItem)
    {
        if (FriendItem->objectName().isEmpty())
            FriendItem->setObjectName("FriendItem");
        FriendItem->resize(250, 71);
        FriendItem->setStyleSheet(QString::fromUtf8(""));
        label_icon = new FriendIconLabel(FriendItem);
        label_icon->setObjectName("label_icon");
        label_icon->setGeometry(QRect(5, 6, 61, 61));
        label_icon->setMouseTracking(true);
        label_icon->setStyleSheet(QString::fromUtf8(""));
        label_icon->setTextFormat(Qt::RichText);
        label_icon->setPixmap(QPixmap(QString::fromUtf8(":/pic/src/QQIcon/icon2.png")));
        label_icon->setScaledContents(true);
        label_name = new QLabel(FriendItem);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(79, 10, 161, 21));
        label_name->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_sig = new QLabel(FriendItem);
        label_sig->setObjectName("label_sig");
        label_sig->setGeometry(QRect(79, 40, 161, 21));
        label_sig->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        lineEdit_newMsg = new QLineEdit(FriendItem);
        lineEdit_newMsg->setObjectName("lineEdit_newMsg");
        lineEdit_newMsg->setGeometry(QRect(50, 2, 20, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Bahnschrift SemiLight")});
        lineEdit_newMsg->setFont(font);
        lineEdit_newMsg->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_newMsg->setMouseTracking(false);
        lineEdit_newMsg->setStyleSheet(QString::fromUtf8("min-width: 20px; min-height: 20px;max-width:20px; max-height: 20px;border-radius: 10px; ;background: #E13D4E;\n"
"color: #ffffff"));
        lineEdit_newMsg->setMaxLength(10);
        lineEdit_newMsg->setAlignment(Qt::AlignCenter);
        lineEdit_newMsg->setReadOnly(true);

        retranslateUi(FriendItem);

        QMetaObject::connectSlotsByName(FriendItem);
    } // setupUi

    void retranslateUi(QWidget *FriendItem)
    {
        FriendItem->setWindowTitle(QCoreApplication::translate("FriendItem", "Form", nullptr));
        label_icon->setText(QString());
        label_name->setText(QCoreApplication::translate("FriendItem", "\345\220\215\345\255\227", nullptr));
        label_sig->setText(QCoreApplication::translate("FriendItem", "\344\270\252\346\200\247\347\255\276\345\220\215", nullptr));
        lineEdit_newMsg->setText(QCoreApplication::translate("FriendItem", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendItem: public Ui_FriendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDITEM_H
