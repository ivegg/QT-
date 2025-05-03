/********************************************************************************
** Form generated from reading UI file 'selfinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELFINFOWIDGET_H
#define UI_SELFINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelfInfoWidget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *widget_3;
    QWidget *widget;
    QPushButton *pushBtn_hide;
    QPushButton *pushBtn_close;

    void setupUi(QWidget *SelfInfoWidget)
    {
        if (SelfInfoWidget->objectName().isEmpty())
            SelfInfoWidget->setObjectName("SelfInfoWidget");
        SelfInfoWidget->resize(953, 675);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/src/\344\270\252\344\272\272\344\270\255\345\277\203\347\273\277.png"), QSize(), QIcon::Normal, QIcon::Off);
        SelfInfoWidget->setWindowIcon(icon);
        horizontalLayoutWidget = new QWidget(SelfInfoWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 951, 671));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        widget_2 = new QWidget(horizontalLayoutWidget);
        widget_2->setObjectName("widget_2");
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setGeometry(QRect(0, -40, 501, 491));
        label->setPixmap(QPixmap(QString::fromUtf8(":/src/bg1.png")));
        label->setScaledContents(true);
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(380, 363, 80, 80));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("border:0"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/src/dz2.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/src/dz1.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(80, 80));
        pushButton->setCheckable(true);
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(0, 450, 473, 217));
        widget_3->setStyleSheet(QString::fromUtf8("background-color:#6F8E92"));

        gridLayout->addWidget(widget_2, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        widget = new QWidget(horizontalLayoutWidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushBtn_hide = new QPushButton(widget);
        pushBtn_hide->setObjectName("pushBtn_hide");
        pushBtn_hide->setGeometry(QRect(390, 0, 34, 40));
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
        icon2.addFile(QString::fromUtf8(":/pic/src/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushBtn_hide->setIcon(icon2);
        pushBtn_hide->setIconSize(QSize(40, 40));
        pushBtn_close = new QPushButton(widget);
        pushBtn_close->setObjectName("pushBtn_close");
        pushBtn_close->setGeometry(QRect(430, 0, 34, 40));
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pic/src/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushBtn_close->setIcon(icon3);
        pushBtn_close->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(widget);


        retranslateUi(SelfInfoWidget);

        QMetaObject::connectSlotsByName(SelfInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *SelfInfoWidget)
    {
        SelfInfoWidget->setWindowTitle(QCoreApplication::translate("SelfInfoWidget", "\346\210\221\347\232\204\350\265\204\346\226\231", nullptr));
        label->setText(QString());
        pushButton->setText(QString());
        pushBtn_hide->setText(QString());
        pushBtn_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SelfInfoWidget: public Ui_SelfInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFINFOWIDGET_H
