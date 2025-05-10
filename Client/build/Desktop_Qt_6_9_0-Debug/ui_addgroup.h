/********************************************************************************
** Form generated from reading UI file 'addgroup.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDGROUP_H
#define UI_ADDGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addgroup
{
public:
    QListWidget *listWidget;
    QTextEdit *textEdit;
    QPushButton *pushButton_create;
    QLineEdit *lineEdit;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *addgroup)
    {
        if (addgroup->objectName().isEmpty())
            addgroup->setObjectName("addgroup");
        addgroup->resize(553, 512);
        listWidget = new QListWidget(addgroup);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(50, 100, 361, 171));
        textEdit = new QTextEdit(addgroup);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(50, 280, 361, 85));
        textEdit->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 1px solid gray;\n"
"    border-radius: 5px;\n"
"    padding: 2px 10px;\n"
"    font-size: 16px;\n"
"    color: black;"));
        pushButton_create = new QPushButton(addgroup);
        pushButton_create->setObjectName("pushButton_create");
        pushButton_create->setGeometry(QRect(60, 390, 80, 40));
        lineEdit = new QLineEdit(addgroup);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(50, 10, 250, 40));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 1px solid gray;\n"
"    border-radius: 5px;\n"
"    padding: 2px 10px;\n"
"    font-size: 16px;\n"
"    color: black;"));
        pushButton_cancel = new QPushButton(addgroup);
        pushButton_cancel->setObjectName("pushButton_cancel");
        pushButton_cancel->setGeometry(QRect(330, 380, 80, 40));

        retranslateUi(addgroup);

        QMetaObject::connectSlotsByName(addgroup);
    } // setupUi

    void retranslateUi(QWidget *addgroup)
    {
        addgroup->setWindowTitle(QCoreApplication::translate("addgroup", "\345\210\233\345\273\272\347\276\244\350\201\212", nullptr));
#if QT_CONFIG(accessibility)
        textEdit->setAccessibleDescription(QCoreApplication::translate("addgroup", "\351\252\214\350\257\201\344\277\241\346\201\257", nullptr));
#endif // QT_CONFIG(accessibility)
        pushButton_create->setText(QCoreApplication::translate("addgroup", "\345\210\233\345\273\272", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("addgroup", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addgroup: public Ui_addgroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDGROUP_H
