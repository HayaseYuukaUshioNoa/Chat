/********************************************************************************
** Form generated from reading UI file 'friendrequestdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDREQUESTDIALOG_H
#define UI_FRIENDREQUESTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FriendRequestDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *FriendRequestDialog)
    {
        if (FriendRequestDialog->objectName().isEmpty())
            FriendRequestDialog->setObjectName("FriendRequestDialog");
        FriendRequestDialog->resize(400, 300);
        label = new QLabel(FriendRequestDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 110, 111, 31));
        label->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(FriendRequestDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(140, 170, 80, 18));

        retranslateUi(FriendRequestDialog);

        QMetaObject::connectSlotsByName(FriendRequestDialog);
    } // setupUi

    void retranslateUi(QDialog *FriendRequestDialog)
    {
        FriendRequestDialog->setWindowTitle(QCoreApplication::translate("FriendRequestDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FriendRequestDialog", "\345\217\221\351\200\201\345\245\275\345\217\213\350\257\267\346\261\202\345\244\261\350\264\245", nullptr));
        pushButton->setText(QCoreApplication::translate("FriendRequestDialog", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendRequestDialog: public Ui_FriendRequestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDREQUESTDIALOG_H
