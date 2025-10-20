/********************************************************************************
** Form generated from reading UI file 'findfaileddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDFAILEDDIALOG_H
#define UI_FINDFAILEDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindFailedDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *FindFailedDialog)
    {
        if (FindFailedDialog->objectName().isEmpty())
            FindFailedDialog->setObjectName("FindFailedDialog");
        FindFailedDialog->resize(300, 300);
        FindFailedDialog->setMinimumSize(QSize(300, 300));
        FindFailedDialog->setMaximumSize(QSize(300, 300));
        widget = new QWidget(FindFailedDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(80, 110, 121, 51));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);


        retranslateUi(FindFailedDialog);

        QMetaObject::connectSlotsByName(FindFailedDialog);
    } // setupUi

    void retranslateUi(QDialog *FindFailedDialog)
    {
        FindFailedDialog->setWindowTitle(QCoreApplication::translate("FindFailedDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FindFailedDialog", "\347\224\250\346\210\267\344\270\215\345\255\230\345\234\250", nullptr));
        pushButton->setText(QCoreApplication::translate("FindFailedDialog", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindFailedDialog: public Ui_FindFailedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDFAILEDDIALOG_H
