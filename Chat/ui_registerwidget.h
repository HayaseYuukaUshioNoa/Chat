/********************************************************************************
** Form generated from reading UI file 'registerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIDGET_H
#define UI_REGISTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <timerbutton.h>

QT_BEGIN_NAMESPACE

class Ui_RegisterWidget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_tips;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_username;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_email;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_pwd;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_confirm;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_verifyCode;
    TimerButton *pushButton_getVerifyCode;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_confirm;
    QPushButton *pushButton_cancel;
    QWidget *page_2;
    QLabel *label_tips_2;
    QPushButton *pushButton_login;

    void setupUi(QWidget *RegisterWidget)
    {
        if (RegisterWidget->objectName().isEmpty())
            RegisterWidget->setObjectName("RegisterWidget");
        RegisterWidget->resize(300, 500);
        RegisterWidget->setMinimumSize(QSize(300, 500));
        RegisterWidget->setMaximumSize(QSize(300, 500));
        RegisterWidget->setStyleSheet(QString::fromUtf8("#label_tips[error=\"true\"] {\n"
"	color:red;\n"
"}\n"
"\n"
"#label_tips[error=\"false\"] {\n"
"	color:green;\n"
"}"));
        stackedWidget = new QStackedWidget(RegisterWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 281, 481));
        page = new QWidget();
        page->setObjectName("page");
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 20, 281, 451));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(layoutWidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 30));
        frame->setMaximumSize(QSize(16777215, 30));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_tips = new QLabel(frame);
        label_tips->setObjectName("label_tips");
        sizePolicy.setHeightForWidth(label_tips->sizePolicy().hasHeightForWidth());
        label_tips->setSizePolicy(sizePolicy);
        label_tips->setMinimumSize(QSize(0, 20));
        label_tips->setMaximumSize(QSize(16777215, 20));
        label_tips->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_tips);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_username = new QLineEdit(layoutWidget);
        lineEdit_username->setObjectName("lineEdit_username");

        horizontalLayout->addWidget(lineEdit_username);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        lineEdit_email = new QLineEdit(layoutWidget);
        lineEdit_email->setObjectName("lineEdit_email");

        horizontalLayout_3->addWidget(lineEdit_email);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_pwd = new QLineEdit(layoutWidget);
        lineEdit_pwd->setObjectName("lineEdit_pwd");

        horizontalLayout_2->addWidget(lineEdit_pwd);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        lineEdit_confirm = new QLineEdit(layoutWidget);
        lineEdit_confirm->setObjectName("lineEdit_confirm");

        horizontalLayout_4->addWidget(lineEdit_confirm);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        lineEdit_verifyCode = new QLineEdit(layoutWidget);
        lineEdit_verifyCode->setObjectName("lineEdit_verifyCode");

        horizontalLayout_5->addWidget(lineEdit_verifyCode);

        pushButton_getVerifyCode = new TimerButton(layoutWidget);
        pushButton_getVerifyCode->setObjectName("pushButton_getVerifyCode");

        horizontalLayout_5->addWidget(pushButton_getVerifyCode);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        pushButton_confirm = new QPushButton(layoutWidget);
        pushButton_confirm->setObjectName("pushButton_confirm");

        horizontalLayout_6->addWidget(pushButton_confirm);

        pushButton_cancel = new QPushButton(layoutWidget);
        pushButton_cancel->setObjectName("pushButton_cancel");

        horizontalLayout_6->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout_6);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_tips_2 = new QLabel(page_2);
        label_tips_2->setObjectName("label_tips_2");
        label_tips_2->setGeometry(QRect(20, 180, 251, 51));
        QFont font;
        font.setPointSize(12);
        label_tips_2->setFont(font);
        label_tips_2->setAlignment(Qt::AlignCenter);
        pushButton_login = new QPushButton(page_2);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setGeometry(QRect(90, 260, 100, 21));
        pushButton_login->setMaximumSize(QSize(100, 16777215));
        stackedWidget->addWidget(page_2);

        retranslateUi(RegisterWidget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RegisterWidget);
    } // setupUi

    void retranslateUi(QWidget *RegisterWidget)
    {
        RegisterWidget->setWindowTitle(QCoreApplication::translate("RegisterWidget", "Form", nullptr));
        label_tips->setText(QCoreApplication::translate("RegisterWidget", "\345\257\206\347\240\201\351\224\231\350\257\257", nullptr));
        label->setText(QCoreApplication::translate("RegisterWidget", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterWidget", "\351\202\256\347\256\261\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterWidget", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterWidget", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("RegisterWidget", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        pushButton_getVerifyCode->setText(QCoreApplication::translate("RegisterWidget", "\350\216\267\345\217\226", nullptr));
        pushButton_confirm->setText(QCoreApplication::translate("RegisterWidget", "\347\241\256\350\256\244", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("RegisterWidget", "\345\217\226\346\266\210", nullptr));
        label_tips_2->setText(QCoreApplication::translate("RegisterWidget", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\2145s\345\220\216\350\277\224\345\233\236\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        pushButton_login->setText(QCoreApplication::translate("RegisterWidget", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWidget: public Ui_RegisterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIDGET_H
