/********************************************************************************
** Form generated from reading UI file 'userinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFOWIDGET_H
#define UI_USERINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInfoWidget
{
public:

    void setupUi(QWidget *UserInfoWidget)
    {
        if (UserInfoWidget->objectName().isEmpty())
            UserInfoWidget->setObjectName("UserInfoWidget");
        UserInfoWidget->resize(400, 300);

        retranslateUi(UserInfoWidget);

        QMetaObject::connectSlotsByName(UserInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *UserInfoWidget)
    {
        UserInfoWidget->setWindowTitle(QCoreApplication::translate("UserInfoWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInfoWidget: public Ui_UserInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFOWIDGET_H
