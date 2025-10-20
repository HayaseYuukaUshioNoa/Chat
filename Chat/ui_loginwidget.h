/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_tips;
    QLabel *label_4;
    QFrame *frame_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_email;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_pwd;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_login;
    QPushButton *pushButton_register;
    QPushButton *pushButton_forget;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName("LoginWidget");
        LoginWidget->resize(300, 500);
        LoginWidget->setMinimumSize(QSize(300, 500));
        LoginWidget->setMaximumSize(QSize(300, 500));
        LoginWidget->setStyleSheet(QString::fromUtf8("#pushButton_forget{\n"
"	border:none;\n"
"	padding: 5px 10px;\n"
"	color: #333333;\n"
"	font-size: 14px;\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"#pushButton_forget:hover{\n"
"	background-color: #f0f0f0;\n"
"	color:green;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"#pushButton_forget:pressed{\n"
"	background-color: #e0e0e0;\n"
"}\n"
"\n"
"#label_tips[error=\"true\"] {\n"
"	color:red;\n"
"}\n"
"\n"
"#label_tips[error=\"false\"] {\n"
"	color:green;\n"
"}"));
        layoutWidget = new QWidget(LoginWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 281, 481));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(layoutWidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(frame);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 281, 241));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_tips = new QLabel(verticalLayoutWidget);
        label_tips->setObjectName("label_tips");
        label_tips->setMinimumSize(QSize(0, 30));
        label_tips->setMaximumSize(QSize(16777215, 30));
        label_tips->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_tips);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/res/login.jpg")));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName("frame_2");
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        layoutWidget_2 = new QWidget(frame_2);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 13, 261, 211));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget_2);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_email = new QLineEdit(layoutWidget_2);
        lineEdit_email->setObjectName("lineEdit_email");

        horizontalLayout->addWidget(lineEdit_email);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(13);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_pwd = new QLineEdit(layoutWidget_2);
        lineEdit_pwd->setObjectName("lineEdit_pwd");

        horizontalLayout_2->addWidget(lineEdit_pwd);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_login = new QPushButton(layoutWidget_2);
        pushButton_login->setObjectName("pushButton_login");

        horizontalLayout_3->addWidget(pushButton_login);

        pushButton_register = new QPushButton(layoutWidget_2);
        pushButton_register->setObjectName("pushButton_register");

        horizontalLayout_3->addWidget(pushButton_register);

        pushButton_forget = new QPushButton(layoutWidget_2);
        pushButton_forget->setObjectName("pushButton_forget");

        horizontalLayout_3->addWidget(pushButton_forget);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(frame_2);


        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "Form", nullptr));
        label_tips->setText(QCoreApplication::translate("LoginWidget", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        label_4->setText(QString());
        label->setText(QCoreApplication::translate("LoginWidget", "\351\202\256\347\256\261\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWidget", "\345\257\206\347\240\201\357\274\232", nullptr));
        pushButton_login->setText(QCoreApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
        pushButton_register->setText(QCoreApplication::translate("LoginWidget", "\346\263\250\345\206\214", nullptr));
        pushButton_forget->setText(QCoreApplication::translate("LoginWidget", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
