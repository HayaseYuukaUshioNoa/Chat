#ifndef FRIENDREQUESTDIALOG_H
#define FRIENDREQUESTDIALOG_H

#include <QDialog>

namespace Ui {
class FriendRequestDialog;
}

class FriendRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendRequestDialog(QWidget *parent = nullptr);
    ~FriendRequestDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FriendRequestDialog *ui;
};

#endif // FRIENDREQUESTDIALOG_H
