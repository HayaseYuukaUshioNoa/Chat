#ifndef FRIENDVERIFYDIALOG_H
#define FRIENDVERIFYDIALOG_H

#include <QDialog>
#include <global.h>

namespace Ui {
class FriendVerifyDialog;
}

class FriendVerifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendVerifyDialog(QWidget *parent = nullptr);
    ~FriendVerifyDialog();

    ServerInfo info;
signals:
    void sig_show_verify_dialog(const QString& username, const QString& email);
private slots:
    void slot_show_verify_dialog(const QString& username, const QString& email);
    void on_pushButton_clicked();

private:
    Ui::FriendVerifyDialog *ui;
};

#endif // FRIENDVERIFYDIALOG_H
