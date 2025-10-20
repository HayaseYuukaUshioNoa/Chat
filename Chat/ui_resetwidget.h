/********************************************************************************
** Form generated from reading UI file 'resetwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETWIDGET_H
#define UI_RESETWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <timerbutton.h>

QT_BEGIN_NAMESPACE

class Ui_ResetWidget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_tips;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_username;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_email;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_newPassword;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_verifyCode;
    TimerButton *pushButton_verifyCode;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_confirm;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *ResetWidget)
    {
        if (ResetWidget->objectName().isEmpty())
            ResetWidget->setObjectName("ResetWidget");
        ResetWidget->resize(300, 500);
        ResetWidget->setMinimumSize(QSize(300, 500));
        ResetWidget->setMaximumSize(QSize(300, 500));
        ResetWidget->setStyleSheet(QString::fromUtf8("#label_tips[error=\"true\"] {\n"
"	color:red;\n"
"}\n"
"\n"
"#label_tips[error=\"false\"] {\n"
"	color:green;\n"
"}"));
        widget = new QWidget(ResetWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 20, 261, 461));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_tips = new QLabel(widget);
        label_tips->setObjectName("label_tips");
        label_tips->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(12);
        label_tips->setFont(font);
        label_tips->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_tips);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_username = new QLineEdit(widget);
        lineEdit_username->setObjectName("lineEdit_username");

        horizontalLayout->addWidget(lineEdit_username);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_email = new QLineEdit(widget);
        lineEdit_email->setObjectName("lineEdit_email");

        horizontalLayout_2->addWidget(lineEdit_email);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        lineEdit_newPassword = new QLineEdit(widget);
        lineEdit_newPassword->setObjectName("lineEdit_newPassword");

        horizontalLayout_4->addWidget(lineEdit_newPassword);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        lineEdit_verifyCode = new QLineEdit(widget);
        lineEdit_verifyCode->setObjectName("lineEdit_verifyCode");

        horizontalLayout_3->addWidget(lineEdit_verifyCode);

        pushButton_verifyCode = new TimerButton(widget);
        pushButton_verifyCode->setObjectName("pushButton_verifyCode");

        horizontalLayout_3->addWidget(pushButton_verifyCode);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pushButton_confirm = new QPushButton(widget);
        pushButton_confirm->setObjectName("pushButton_confirm");

        horizontalLayout_5->addWidget(pushButton_confirm);

        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName("pushButton_cancel");

        horizontalLayout_5->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(ResetWidget);

        QMetaObject::connectSlotsByName(ResetWidget);
    } // setupUi

    void retranslateUi(QWidget *ResetWidget)
    {
        ResetWidget->setWindowTitle(QCoreApplication::translate("ResetWidget", "Form", nullptr));
        label_tips->setText(QCoreApplication::translate("ResetWidget", "\351\207\215\347\275\256\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("ResetWidget", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("ResetWidget", "\351\202\256\347\256\261\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("ResetWidget", "\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("ResetWidget", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        pushButton_verifyCode->setText(QCoreApplication::translate("ResetWidget", "\350\216\267\345\217\226", nullptr));
        pushButton_confirm->setText(QCoreApplication::translate("ResetWidget", "\347\241\256\350\256\244", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("ResetWidget", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResetWidget: public Ui_ResetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETWIDGET_H
