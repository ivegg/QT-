/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include <sendtextedit.h>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QGridLayout *gridLayout;
    SendTextEdit *textEdit;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->setEnabled(true);
        ChatWindow->resize(620, 450);
        gridLayout = new QGridLayout(ChatWindow);
        gridLayout->setObjectName("gridLayout");
        textEdit = new SendTextEdit(ChatWindow);
        textEdit->setObjectName("textEdit");
        textEdit->setEnabled(true);
        textEdit->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {\n"
"    border: none;\n"
"    background: white;\n"
"    width: 15px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #999999;\n"
"    min-height: 20px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover,\n"
"QScrollBar::handle:vertical:focus {\n"
"    background-color: #666666;\n"
"    border-radius: 10px;\n"
"}\n"
""));
        textEdit->setFrameShape(QFrame::NoFrame);
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);


        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
