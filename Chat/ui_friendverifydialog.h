/********************************************************************************
** Form generated from reading UI file 'friendverifydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDVERIFYDIALOG_H
#define UI_FRIENDVERIFYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FriendVerifyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *username;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *email;
    QFrame *frame_2;
    QPushButton *pushButton;

    void setupUi(QDialog *FriendVerifyDialog)
    {
        if (FriendVerifyDialog->objectName().isEmpty())
            FriendVerifyDialog->setObjectName("FriendVerifyDialog");
        FriendVerifyDialog->resize(400, 400);
        FriendVerifyDialog->setMinimumSize(QSize(400, 400));
        FriendVerifyDialog->setMaximumSize(QSize(400, 400));
        verticalLayout = new QVBoxLayout(FriendVerifyDialog);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(FriendVerifyDialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(frame);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        username = new QLabel(frame);
        username->setObjectName("username");

        horizontalLayout->addWidget(username);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        email = new QLabel(frame);
        email->setObjectName("email");

        horizontalLayout_2->addWidget(email);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(FriendVerifyDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(150, 60, 80, 31));

        verticalLayout->addWidget(frame_2);


        retranslateUi(FriendVerifyDialog);

        QMetaObject::connectSlotsByName(FriendVerifyDialog);
    } // setupUi

    void retranslateUi(QDialog *FriendVerifyDialog)
    {
        FriendVerifyDialog->setWindowTitle(QCoreApplication::translate("FriendVerifyDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FriendVerifyDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        username->setText(QCoreApplication::translate("FriendVerifyDialog", "Tom", nullptr));
        label_3->setText(QCoreApplication::translate("FriendVerifyDialog", "\351\202\256\347\256\261", nullptr));
        email->setText(QCoreApplication::translate("FriendVerifyDialog", "XXXX", nullptr));
        pushButton->setText(QCoreApplication::translate("FriendVerifyDialog", "\345\220\214\346\204\217\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendVerifyDialog: public Ui_FriendVerifyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDVERIFYDIALOG_H
