/********************************************************************************
** Form generated from reading UI file 'iconselect.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICONSELECT_H
#define UI_ICONSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IconSelect
{
public:
    QListWidget *listWidget;
    QLabel *label;
    QPushButton *pushButton;
    QLineEdit *lineEdit;

    void setupUi(QWidget *IconSelect)
    {
        if (IconSelect->objectName().isEmpty())
            IconSelect->setObjectName("IconSelect");
        IconSelect->resize(640, 562);
        listWidget = new QListWidget(IconSelect);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 20, 601, 411));
        listWidget->setIconSize(QSize(64, 64));
        listWidget->setResizeMode(QListView::Adjust);
        listWidget->setSpacing(20);
        listWidget->setViewMode(QListView::IconMode);
        listWidget->setUniformItemSizes(true);
        label = new QLabel(IconSelect);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 450, 171, 21));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        pushButton = new QPushButton(IconSelect);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(530, 490, 84, 40));
        lineEdit = new QLineEdit(IconSelect);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 490, 501, 40));
        QFont font1;
        font1.setPointSize(12);
        lineEdit->setFont(font1);

        retranslateUi(IconSelect);

        QMetaObject::connectSlotsByName(IconSelect);
    } // setupUi

    void retranslateUi(QWidget *IconSelect)
    {
        IconSelect->setWindowTitle(QCoreApplication::translate("IconSelect", "Form", nullptr));
        label->setText(QCoreApplication::translate("IconSelect", "\350\216\267\345\217\226\347\275\221\347\273\234\345\244\264\345\203\217", nullptr));
        pushButton->setText(QCoreApplication::translate("IconSelect", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IconSelect: public Ui_IconSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICONSELECT_H
