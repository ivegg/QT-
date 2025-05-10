/********************************************************************************
** Form generated from reading UI file 'logging.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGGING_H
#define UI_LOGGING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logging
{
public:
    QWidget *centerWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushBtn_close;
    QLineEdit *lineEdit_account;
    QLineEdit *lineEdit_password;
    QPushButton *pushBtn_hide;
    QLabel *label_4;
    QPushButton *pushButton_seePassword;
    QLabel *label_6;
    QPushButton *pushButton_login;
    QPushButton *pushbtn_regist;
    QWidget *page_2;
    QLabel *label_7;
    QLineEdit *lineEdit_account_2;
    QLineEdit *lineEdit_password_2;
    QLineEdit *lineEdit_password_3;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_name;
    QPushButton *pushButton_regist;
    QPushButton *pushButton_return;
    QLabel *label_5;
    QPushButton *pushBtn_close_2;
    QPushButton *pushBtn_hide_2;
    QLabel *label_11;

    void setupUi(QWidget *Logging)
    {
        if (Logging->objectName().isEmpty())
            Logging->setObjectName("Logging");
        Logging->resize(564, 430);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pic/src/wechat2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Logging->setWindowIcon(icon);
        centerWidget = new QWidget(Logging);
        centerWidget->setObjectName("centerWidget");
        centerWidget->setGeometry(QRect(0, 0, 561, 430));
        centerWidget->setMinimumSize(QSize(430, 330));
        centerWidget->setMaximumSize(QSize(1000, 1000));
        stackedWidget = new QStackedWidget(centerWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 10, 511, 401));
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(54, 131, 61, 61));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(54, 196, 61, 61));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        pushBtn_close = new QPushButton(page);
        pushBtn_close->setObjectName("pushBtn_close");
        pushBtn_close->setGeometry(QRect(450, 0, 34, 40));
        pushBtn_close->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: none; /* no border for a flat push button */\n"
"	image: url(:/src/close.png); /* \346\234\200\345\260\217\345\214\226 */\n"
"	min-width: 34px;\n"
"	max-width: 34px;\n"
"	min-height: 40px;\n"
"	max-height: 40px;\n"
"}\n"
"QPushButton::hover {\n"
"	background-color: #f57575; \n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pic/src/close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushBtn_close->setIcon(icon1);
        pushBtn_close->setIconSize(QSize(40, 40));
        lineEdit_account = new QLineEdit(page);
        lineEdit_account->setObjectName("lineEdit_account");
        lineEdit_account->setGeometry(QRect(133, 135, 301, 51));
        lineEdit_account->setMinimumSize(QSize(240, 22));
        lineEdit_account->setMaximumSize(QSize(2400, 2400));
        lineEdit_account->setFont(font);
        lineEdit_account->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: rgb(0, 0, 0);\n"
"	border-style: none;\n"
"	border-radius: 5px;	\n"
"	border-right:1px solid #3498db;\n"
"	border-top:1px solid #3498db;\n"
"	border-left:1px solid #3498db;\n"
"	border-bottom:1px solid #3498db;\n"
"	min-height: 20px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"}"));
        lineEdit_account->setMaxLength(16);
        lineEdit_password = new QLineEdit(page);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(133, 202, 301, 51));
        lineEdit_password->setMinimumSize(QSize(240, 22));
        lineEdit_password->setMaximumSize(QSize(2400, 3000));
        lineEdit_password->setFont(font);
        lineEdit_password->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: rgb(0, 0, 0);\n"
"	border-style: none;\n"
"	border-radius: 5px;	\n"
"	border-right:1px solid #3498db;\n"
"	border-top:1px solid #3498db;\n"
"	border-left:1px solid #3498db;\n"
"	border-bottom:1px solid #3498db;\n"
"	min-height: 20px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"}"));
        lineEdit_password->setMaxLength(32);
        lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);
        pushBtn_hide = new QPushButton(page);
        pushBtn_hide->setObjectName("pushBtn_hide");
        pushBtn_hide->setGeometry(QRect(410, 0, 34, 40));
        pushBtn_hide->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: none; /* no border for a flat push button */\n"
"	image: url(:/src/min.png); /* \346\234\200\345\260\217\345\214\226 */\n"
"	min-width: 34px;\n"
"	max-width: 34px;\n"
"	min-height: 40px;\n"
"	max-height: 40px;\n"
"}\n"
"QPushButton::hover {\n"
"	background-color: rgba(166,166,166, 50); \n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pic/src/min.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushBtn_hide->setIcon(icon2);
        pushBtn_hide->setIconSize(QSize(40, 40));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 10, 121, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setPointSize(15);
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(166,166,166);"));
        pushButton_seePassword = new QPushButton(page);
        pushButton_seePassword->setObjectName("pushButton_seePassword");
        pushButton_seePassword->setGeometry(QRect(390, 210, 36, 36));
        pushButton_seePassword->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pic/src/eyes_open.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/pic/src/eyes_close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_seePassword->setIcon(icon3);
        pushButton_seePassword->setIconSize(QSize(36, 36));
        pushButton_seePassword->setCheckable(true);
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 10, 40, 40));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/pic/src/wechat2.png")));
        pushButton_login = new QPushButton(page);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setGeometry(QRect(140, 330, 235, 51));
        pushButton_login->setMinimumSize(QSize(235, 35));
        pushButton_login->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"	border-style: solid;\n"
"	border-radius: 5px;	\n"
"	background-color: rgb(7,193,96);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: rgb(56,205,127);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgb(7,193,96);\n"
"}"));
        pushbtn_regist = new QPushButton(page);
        pushbtn_regist->setObjectName("pushbtn_regist");
        pushbtn_regist->setGeometry(QRect(10, 360, 75, 23));
        pushbtn_regist->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        pushbtn_regist->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: rgb(166,166,166);\n"
"	border-style: none;\n"
"}\n"
"QPushButton::hover {\n"
"	color: rgb(67,129,202);\n"
"}"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_7 = new QLabel(page_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(83, 120, 81, 31));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineEdit_account_2 = new QLineEdit(page_2);
        lineEdit_account_2->setObjectName("lineEdit_account_2");
        lineEdit_account_2->setGeometry(QRect(200, 80, 240, 30));
        lineEdit_account_2->setMinimumSize(QSize(240, 22));
        lineEdit_account_2->setMaximumSize(QSize(240, 30));
        lineEdit_account_2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: rgb(0, 0, 0);\n"
"	border-style: none;\n"
"	border-radius: 5px;	\n"
"	border-right:1px solid #3498db;\n"
"	border-top:1px solid #3498db;\n"
"	border-left:1px solid #3498db;\n"
"	border-bottom:1px solid #3498db;\n"
"	min-height: 20px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"}"));
        lineEdit_account_2->setMaxLength(16);
        lineEdit_password_2 = new QLineEdit(page_2);
        lineEdit_password_2->setObjectName("lineEdit_password_2");
        lineEdit_password_2->setGeometry(QRect(200, 120, 240, 30));
        lineEdit_password_2->setMinimumSize(QSize(240, 22));
        lineEdit_password_2->setMaximumSize(QSize(240, 30));
        lineEdit_password_2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: rgb(0, 0, 0);\n"
"	border-style: none;\n"
"	border-radius: 5px;	\n"
"	border-right:1px solid #3498db;\n"
"	border-top:1px solid #3498db;\n"
"	border-left:1px solid #3498db;\n"
"	border-bottom:1px solid #3498db;\n"
"	min-height: 20px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"}"));
        lineEdit_password_2->setMaxLength(32);
        lineEdit_password_3 = new QLineEdit(page_2);
        lineEdit_password_3->setObjectName("lineEdit_password_3");
        lineEdit_password_3->setGeometry(QRect(200, 160, 240, 30));
        lineEdit_password_3->setMinimumSize(QSize(240, 22));
        lineEdit_password_3->setMaximumSize(QSize(240, 30));
        lineEdit_password_3->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: rgb(0, 0, 0);\n"
"	border-style: none;\n"
"	border-radius: 5px;	\n"
"	border-right:1px solid #3498db;\n"
"	border-top:1px solid #3498db;\n"
"	border-left:1px solid #3498db;\n"
"	border-bottom:1px solid #3498db;\n"
"	min-height: 20px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"}"));
        lineEdit_password_3->setMaxLength(32);
        label_8 = new QLabel(page_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(73, 160, 91, 31));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        label_9 = new QLabel(page_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(83, 80, 81, 31));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        label_10 = new QLabel(page_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(70, 200, 91, 31));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineEdit_name = new QLineEdit(page_2);
        lineEdit_name->setObjectName("lineEdit_name");
        lineEdit_name->setGeometry(QRect(200, 200, 240, 30));
        lineEdit_name->setMinimumSize(QSize(240, 22));
        lineEdit_name->setMaximumSize(QSize(240, 30));
        lineEdit_name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: rgb(0, 0, 0);\n"
"	border-style: none;\n"
"	border-radius: 5px;	\n"
"	border-right:1px solid #3498db;\n"
"	border-top:1px solid #3498db;\n"
"	border-left:1px solid #3498db;\n"
"	border-bottom:1px solid #3498db;\n"
"	min-height: 20px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"}"));
        lineEdit_name->setMaxLength(32);
        pushButton_regist = new QPushButton(page_2);
        pushButton_regist->setObjectName("pushButton_regist");
        pushButton_regist->setGeometry(QRect(100, 290, 84, 24));
        pushButton_return = new QPushButton(page_2);
        pushButton_return->setObjectName("pushButton_return");
        pushButton_return->setGeometry(QRect(350, 290, 84, 24));
        label_5 = new QLabel(page_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 10, 121, 41));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(166,166,166);"));
        pushBtn_close_2 = new QPushButton(page_2);
        pushBtn_close_2->setObjectName("pushBtn_close_2");
        pushBtn_close_2->setGeometry(QRect(450, 0, 34, 40));
        pushBtn_close_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: none; /* no border for a flat push button */\n"
"	image: url(:/src/close.png); /* \346\234\200\345\260\217\345\214\226 */\n"
"	min-width: 34px;\n"
"	max-width: 34px;\n"
"	min-height: 40px;\n"
"	max-height: 40px;\n"
"}\n"
"QPushButton::hover {\n"
"	background-color: #f57575; \n"
"}"));
        pushBtn_close_2->setIcon(icon1);
        pushBtn_close_2->setIconSize(QSize(40, 40));
        pushBtn_hide_2 = new QPushButton(page_2);
        pushBtn_hide_2->setObjectName("pushBtn_hide_2");
        pushBtn_hide_2->setGeometry(QRect(410, 0, 34, 40));
        pushBtn_hide_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: none; /* no border for a flat push button */\n"
"	image: url(:/src/min.png); /* \346\234\200\345\260\217\345\214\226 */\n"
"	min-width: 34px;\n"
"	max-width: 34px;\n"
"	min-height: 40px;\n"
"	max-height: 40px;\n"
"}\n"
"QPushButton::hover {\n"
"	background-color: rgba(166,166,166, 50); \n"
"}"));
        pushBtn_hide_2->setIcon(icon2);
        pushBtn_hide_2->setIconSize(QSize(40, 40));
        label_11 = new QLabel(page_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 10, 40, 40));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/pic/src/wechat2.png")));
        stackedWidget->addWidget(page_2);

        retranslateUi(Logging);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Logging);
    } // setupUi

    void retranslateUi(QWidget *Logging)
    {
        Logging->setWindowTitle(QCoreApplication::translate("Logging", "Form", nullptr));
        label->setText(QCoreApplication::translate("Logging", "\350\264\246\345\217\267:", nullptr));
        label_2->setText(QCoreApplication::translate("Logging", "\345\257\206\347\240\201:", nullptr));
        pushBtn_close->setText(QString());
        lineEdit_account->setText(QCoreApplication::translate("Logging", "123", nullptr));
        lineEdit_password->setText(QCoreApplication::translate("Logging", "123", nullptr));
        pushBtn_hide->setText(QString());
        label_4->setText(QCoreApplication::translate("Logging", "WeChat", nullptr));
        pushButton_seePassword->setText(QString());
        label_6->setText(QString());
        pushButton_login->setText(QCoreApplication::translate("Logging", "\347\231\273\345\275\225", nullptr));
#if QT_CONFIG(statustip)
        pushbtn_regist->setStatusTip(QCoreApplication::translate("Logging", "\346\263\250\345\206\214", nullptr));
#endif // QT_CONFIG(statustip)
        pushbtn_regist->setText(QCoreApplication::translate("Logging", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        label_7->setText(QCoreApplication::translate("Logging", "\345\257\206\347\240\201:", nullptr));
        lineEdit_account_2->setText(QString());
        lineEdit_password_2->setText(QString());
        lineEdit_password_3->setText(QString());
        label_8->setText(QCoreApplication::translate("Logging", "\347\241\256\350\256\244\345\257\206\347\240\201:", nullptr));
        label_9->setText(QCoreApplication::translate("Logging", "\350\264\246\345\217\267:", nullptr));
        label_10->setText(QCoreApplication::translate("Logging", "\346\230\265\347\247\260:", nullptr));
        lineEdit_name->setText(QString());
        pushButton_regist->setText(QCoreApplication::translate("Logging", "\346\263\250\345\206\214", nullptr));
        pushButton_return->setText(QCoreApplication::translate("Logging", "\350\277\224\345\233\236", nullptr));
        label_5->setText(QCoreApplication::translate("Logging", "OurChat", nullptr));
        pushBtn_close_2->setText(QString());
        pushBtn_hide_2->setText(QString());
        label_11->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Logging: public Ui_Logging {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGING_H
