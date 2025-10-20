/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chatuserlist.h>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *side_bar;
    QVBoxLayout *verticalLayout;
    QLabel *username;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer;
    QWidget *chat_user_widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *search_widget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *search_edit;
    QPushButton *search_btn;
    ChatUserList *chat_user_list;
    QListWidget *search_list;
    QListWidget *contact_person_list;
    QListWidget *new_friend_list;
    QWidget *chat_data_widget;
    QVBoxLayout *verticalLayout_3;
    QWidget *title_widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *title_label;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QListWidget *chat_data_list;
    QTextEdit *textEdit;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *recv_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *send_btn;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName("ChatDialog");
        ChatDialog->resize(678, 603);
        horizontalLayout = new QHBoxLayout(ChatDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        side_bar = new QWidget(ChatDialog);
        side_bar->setObjectName("side_bar");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(side_bar->sizePolicy().hasHeightForWidth());
        side_bar->setSizePolicy(sizePolicy);
        side_bar->setMinimumSize(QSize(60, 0));
        side_bar->setMaximumSize(QSize(60, 16777215));
        verticalLayout = new QVBoxLayout(side_bar);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 0, 0);
        username = new QLabel(side_bar);
        username->setObjectName("username");

        verticalLayout->addWidget(username);

        pushButton = new QPushButton(side_bar);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(side_bar);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(side_bar);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(side_bar);

        chat_user_widget = new QWidget(ChatDialog);
        chat_user_widget->setObjectName("chat_user_widget");
        chat_user_widget->setMaximumSize(QSize(250, 16777215));
        verticalLayout_2 = new QVBoxLayout(chat_user_widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        search_widget = new QWidget(chat_user_widget);
        search_widget->setObjectName("search_widget");
        search_widget->setMinimumSize(QSize(0, 60));
        search_widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_2 = new QHBoxLayout(search_widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        search_edit = new QLineEdit(search_widget);
        search_edit->setObjectName("search_edit");
        search_edit->setMinimumSize(QSize(0, 30));
        search_edit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(search_edit);

        search_btn = new QPushButton(search_widget);
        search_btn->setObjectName("search_btn");
        search_btn->setMinimumSize(QSize(40, 30));
        search_btn->setMaximumSize(QSize(40, 30));

        horizontalLayout_2->addWidget(search_btn);


        verticalLayout_2->addWidget(search_widget);

        chat_user_list = new ChatUserList(chat_user_widget);
        chat_user_list->setObjectName("chat_user_list");

        verticalLayout_2->addWidget(chat_user_list);

        search_list = new QListWidget(chat_user_widget);
        search_list->setObjectName("search_list");

        verticalLayout_2->addWidget(search_list);

        contact_person_list = new QListWidget(chat_user_widget);
        contact_person_list->setObjectName("contact_person_list");

        verticalLayout_2->addWidget(contact_person_list);

        new_friend_list = new QListWidget(chat_user_widget);
        new_friend_list->setObjectName("new_friend_list");

        verticalLayout_2->addWidget(new_friend_list);


        horizontalLayout->addWidget(chat_user_widget);

        chat_data_widget = new QWidget(ChatDialog);
        chat_data_widget->setObjectName("chat_data_widget");
        verticalLayout_3 = new QVBoxLayout(chat_data_widget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        title_widget = new QWidget(chat_data_widget);
        title_widget->setObjectName("title_widget");
        title_widget->setMinimumSize(QSize(0, 30));
        title_widget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(title_widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        title_label = new QLabel(title_widget);
        title_label->setObjectName("title_label");

        horizontalLayout_3->addWidget(title_label);


        verticalLayout_3->addWidget(title_widget);

        widget = new QWidget(chat_data_widget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        chat_data_list = new QListWidget(widget);
        chat_data_list->setObjectName("chat_data_list");

        verticalLayout_4->addWidget(chat_data_list);


        verticalLayout_3->addWidget(widget);

        textEdit = new QTextEdit(chat_data_widget);
        textEdit->setObjectName("textEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);
        textEdit->setMaximumSize(QSize(16777215, 200));

        verticalLayout_3->addWidget(textEdit);

        widget_3 = new QWidget(chat_data_widget);
        widget_3->setObjectName("widget_3");
        widget_3->setMinimumSize(QSize(0, 50));
        widget_3->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        recv_btn = new QPushButton(widget_3);
        recv_btn->setObjectName("recv_btn");

        horizontalLayout_4->addWidget(recv_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        send_btn = new QPushButton(widget_3);
        send_btn->setObjectName("send_btn");

        horizontalLayout_4->addWidget(send_btn);


        verticalLayout_3->addWidget(widget_3);


        horizontalLayout->addWidget(chat_data_widget);


        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "Dialog", nullptr));
        username->setText(QCoreApplication::translate("ChatDialog", "Tom", nullptr));
        pushButton->setText(QCoreApplication::translate("ChatDialog", "\350\201\212\345\244\251", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ChatDialog", "\350\201\224\347\263\273\344\272\272", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ChatDialog", "\346\226\260\346\234\213\345\217\213", nullptr));
        search_edit->setPlaceholderText(QCoreApplication::translate("ChatDialog", "\346\220\234\347\264\242", nullptr));
        search_btn->setText(QCoreApplication::translate("ChatDialog", "\346\267\273\345\212\240", nullptr));
        title_label->setText(QCoreApplication::translate("ChatDialog", "\350\201\212\345\244\251", nullptr));
        recv_btn->setText(QCoreApplication::translate("ChatDialog", "\346\216\245\346\224\266", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatDialog", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
