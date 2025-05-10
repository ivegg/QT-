/********************************************************************************
** Form generated from reading UI file 'systemmessage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMMESSAGE_H
#define UI_SYSTEMMESSAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemMessage
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_friend;
    QListWidget *listWidget;
    QWidget *tab_group;
    QListWidget *listWidget_2;

    void setupUi(QWidget *SystemMessage)
    {
        if (SystemMessage->objectName().isEmpty())
            SystemMessage->setObjectName("SystemMessage");
        SystemMessage->resize(749, 757);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/src/weichat.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        SystemMessage->setWindowIcon(icon);
        tabWidget = new QTabWidget(SystemMessage);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 30, 750, 730));
        tab_friend = new QWidget();
        tab_friend->setObjectName("tab_friend");
        listWidget = new QListWidget(tab_friend);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 746, 698));
        tabWidget->addTab(tab_friend, QString());
        tab_group = new QWidget();
        tab_group->setObjectName("tab_group");
        listWidget_2 = new QListWidget(tab_group);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(0, 0, 746, 698));
        tabWidget->addTab(tab_group, QString());

        retranslateUi(SystemMessage);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SystemMessage);
    } // setupUi

    void retranslateUi(QWidget *SystemMessage)
    {
        SystemMessage->setWindowTitle(QCoreApplication::translate("SystemMessage", "\347\263\273\347\273\237\346\266\210\346\201\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_friend), QCoreApplication::translate("SystemMessage", "\345\245\275\345\217\213\351\252\214\350\257\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_group), QCoreApplication::translate("SystemMessage", "\347\276\244\347\263\273\347\273\237\346\266\210\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemMessage: public Ui_SystemMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMMESSAGE_H
