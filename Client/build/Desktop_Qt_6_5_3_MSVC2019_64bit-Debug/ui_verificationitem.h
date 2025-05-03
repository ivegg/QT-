/********************************************************************************
** Form generated from reading UI file 'verificationitem.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERIFICATIONITEM_H
#define UI_VERIFICATIONITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <friendiconlabel.h>

QT_BEGIN_NAMESPACE

class Ui_VerificationItem
{
public:
    FriendIconLabel *label_icon;
    QLabel *label_name;
    QLabel *label_name_msg;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *label_name_2;

    void setupUi(QWidget *VerificationItem)
    {
        if (VerificationItem->objectName().isEmpty())
            VerificationItem->setObjectName("VerificationItem");
        VerificationItem->resize(700, 100);
        label_icon = new FriendIconLabel(VerificationItem);
        label_icon->setObjectName("label_icon");
        label_icon->setGeometry(QRect(10, 10, 80, 80));
        label_name = new QLabel(VerificationItem);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(290, 10, 161, 31));
        label_name_msg = new QLabel(VerificationItem);
        label_name_msg->setObjectName("label_name_msg");
        label_name_msg->setGeometry(QRect(110, 50, 341, 41));
        comboBox = new QComboBox(VerificationItem);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(524, 40, 101, 25));
        comboBox->setFrame(false);
        pushButton = new QPushButton(VerificationItem);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(520, 40, 84, 25));
        label_name_2 = new QLabel(VerificationItem);
        label_name_2->setObjectName("label_name_2");
        label_name_2->setGeometry(QRect(110, 10, 161, 31));

        retranslateUi(VerificationItem);

        QMetaObject::connectSlotsByName(VerificationItem);
    } // setupUi

    void retranslateUi(QWidget *VerificationItem)
    {
        VerificationItem->setWindowTitle(QCoreApplication::translate("VerificationItem", "Form", nullptr));
        label_icon->setText(QString());
        label_name->setText(QString());
        label_name_msg->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("VerificationItem", "\345\220\214\346\204\217", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("VerificationItem", "\346\213\222\347\273\235", nullptr));

        pushButton->setText(QCoreApplication::translate("VerificationItem", "\345\220\214\346\204\217", nullptr));
        label_name_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VerificationItem: public Ui_VerificationItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFICATIONITEM_H
