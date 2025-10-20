/********************************************************************************
** Form generated from reading UI file 'finduserdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDUSERDIALOG_H
#define UI_FINDUSERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindUserDialog
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

    void setupUi(QDialog *FindUserDialog)
    {
        if (FindUserDialog->objectName().isEmpty())
            FindUserDialog->setObjectName("FindUserDialog");
        FindUserDialog->resize(442, 393);
        verticalLayout = new QVBoxLayout(FindUserDialog);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(FindUserDialog);
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

        frame_2 = new QFrame(FindUserDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 90, 80, 31));

        verticalLayout->addWidget(frame_2);


        retranslateUi(FindUserDialog);

        QMetaObject::connectSlotsByName(FindUserDialog);
    } // setupUi

    void retranslateUi(QDialog *FindUserDialog)
    {
        FindUserDialog->setWindowTitle(QCoreApplication::translate("FindUserDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FindUserDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        username->setText(QCoreApplication::translate("FindUserDialog", "Tom", nullptr));
        label_3->setText(QCoreApplication::translate("FindUserDialog", "\351\202\256\347\256\261", nullptr));
        email->setText(QCoreApplication::translate("FindUserDialog", "XXXX", nullptr));
        pushButton->setText(QCoreApplication::translate("FindUserDialog", "\346\267\273\345\212\240\345\210\260\351\200\232\350\256\257\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindUserDialog: public Ui_FindUserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDUSERDIALOG_H
