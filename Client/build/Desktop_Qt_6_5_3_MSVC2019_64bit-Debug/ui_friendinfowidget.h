/********************************************************************************
** Form generated from reading UI file 'friendinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDINFOWIDGET_H
#define UI_FRIENDINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendInfoWidget
{
public:
    QLabel *label_name;
    QTextEdit *textEdit_sig;
    QLabel *label_account;
    QLabel *label_bg;

    void setupUi(QWidget *FriendInfoWidget)
    {
        if (FriendInfoWidget->objectName().isEmpty())
            FriendInfoWidget->setObjectName("FriendInfoWidget");
        FriendInfoWidget->resize(422, 229);
        QFont font;
        font.setPointSize(9);
        FriendInfoWidget->setFont(font);
        label_name = new QLabel(FriendInfoWidget);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(25, 80, 111, 41));
        QFont font1;
        font1.setPointSize(20);
        label_name->setFont(font1);
        label_name->setCursor(QCursor(Qt::IBeamCursor));
        label_name->setStyleSheet(QString::fromUtf8("color:#ffffff;"));
        label_name->setTextFormat(Qt::MarkdownText);
        label_name->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        textEdit_sig = new QTextEdit(FriendInfoWidget);
        textEdit_sig->setObjectName("textEdit_sig");
        textEdit_sig->setGeometry(QRect(30, 160, 101, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit_sig->sizePolicy().hasHeightForWidth());
        textEdit_sig->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(11);
        textEdit_sig->setFont(font2);
        textEdit_sig->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textEdit_sig->setStyleSheet(QString::fromUtf8("background:transparent;border-width:0;border-style:outset;color:#ffffff;"));
        textEdit_sig->setReadOnly(true);
        label_account = new QLabel(FriendInfoWidget);
        label_account->setObjectName("label_account");
        label_account->setGeometry(QRect(25, 40, 121, 41));
        label_account->setFont(font1);
        label_account->setCursor(QCursor(Qt::IBeamCursor));
        label_account->setStyleSheet(QString::fromUtf8("color:#ffffff;"));
        label_account->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        label_bg = new QLabel(FriendInfoWidget);
        label_bg->setObjectName("label_bg");
        label_bg->setGeometry(QRect(0, 0, 422, 229));
        label_bg->setFont(font);
        label_bg->setStyleSheet(QString::fromUtf8(""));
        label_bg->setPixmap(QPixmap(QString::fromUtf8(":/src/friendItemBg.png")));
        label_bg->setScaledContents(true);
        label_bg->setTextInteractionFlags(Qt::NoTextInteraction);
        label_bg->raise();
        label_name->raise();
        textEdit_sig->raise();
        label_account->raise();

        retranslateUi(FriendInfoWidget);

        QMetaObject::connectSlotsByName(FriendInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *FriendInfoWidget)
    {
        FriendInfoWidget->setWindowTitle(QCoreApplication::translate("FriendInfoWidget", "Form", nullptr));
        label_name->setText(QCoreApplication::translate("FriendInfoWidget", "name", nullptr));
        label_account->setText(QCoreApplication::translate("FriendInfoWidget", "account", nullptr));
        label_bg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendInfoWidget: public Ui_FriendInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDINFOWIDGET_H
