/********************************************************************************
** Form generated from reading UI file 'loadingdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGDIALOG_H
#define UI_LOADINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_LoadingDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *loading_label;

    void setupUi(QDialog *LoadingDialog)
    {
        if (LoadingDialog->objectName().isEmpty())
            LoadingDialog->setObjectName("LoadingDialog");
        LoadingDialog->resize(400, 300);
        horizontalLayout = new QHBoxLayout(LoadingDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        loading_label = new QLabel(LoadingDialog);
        loading_label->setObjectName("loading_label");
        loading_label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(loading_label);


        retranslateUi(LoadingDialog);

        QMetaObject::connectSlotsByName(LoadingDialog);
    } // setupUi

    void retranslateUi(QDialog *LoadingDialog)
    {
        LoadingDialog->setWindowTitle(QCoreApplication::translate("LoadingDialog", "Dialog", nullptr));
        loading_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoadingDialog: public Ui_LoadingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGDIALOG_H
