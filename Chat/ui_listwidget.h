/********************************************************************************
** Form generated from reading UI file 'listwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTWIDGET_H
#define UI_LISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListWidget
{
public:

    void setupUi(QWidget *ListWidget)
    {
        if (ListWidget->objectName().isEmpty())
            ListWidget->setObjectName("ListWidget");
        ListWidget->resize(200, 51);
        ListWidget->setMinimumSize(QSize(0, 50));

        retranslateUi(ListWidget);

        QMetaObject::connectSlotsByName(ListWidget);
    } // setupUi

    void retranslateUi(QWidget *ListWidget)
    {
        ListWidget->setWindowTitle(QCoreApplication::translate("ListWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListWidget: public Ui_ListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTWIDGET_H
