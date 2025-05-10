/********************************************************************************
** Form generated from reading UI file 'imagepreview.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPREVIEW_H
#define UI_IMAGEPREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImagePreview
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *ImagePreview)
    {
        if (ImagePreview->objectName().isEmpty())
            ImagePreview->setObjectName("ImagePreview");
        ImagePreview->resize(400, 480);
        ImagePreview->setMinimumSize(QSize(400, 400));
        gridLayout = new QGridLayout(ImagePreview);
        gridLayout->setObjectName("gridLayout");
        plainTextEdit = new QPlainTextEdit(ImagePreview);
        plainTextEdit->setObjectName("plainTextEdit");

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);


        retranslateUi(ImagePreview);

        QMetaObject::connectSlotsByName(ImagePreview);
    } // setupUi

    void retranslateUi(QWidget *ImagePreview)
    {
        ImagePreview->setWindowTitle(QCoreApplication::translate("ImagePreview", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImagePreview: public Ui_ImagePreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPREVIEW_H
