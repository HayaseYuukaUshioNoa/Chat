#include "friendverifydialog.h"
#include "ui_friendverifydialog.h"
#include <global.h>
#include <QJsonObject>
#include <tcpmgr.h>

FriendVerifyDialog::FriendVerifyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FriendVerifyDialog)
{
    ui->setupUi(this);
    connect(this, &FriendVerifyDialog::sig_show_verify_dialog, this, &FriendVerifyDialog::slot_show_verify_dialog);
}

FriendVerifyDialog::~FriendVerifyDialog()
{
    delete ui;
}

void FriendVerifyDialog::slot_show_verify_dialog(const QString &username, const QString &email)
{
    ui->username->setText(username);
    ui->email->setText(email);
    this->show();
}

void FriendVerifyDialog::on_pushButton_clicked()
{
    // 好友认证
    this->hide();
    QString from_username = ui->username->text();
    QString from_email = ui->email->text();
    QJsonObject json;
    json["username"] = from_username;
    json["email"] = from_email;
    TcpMgr::instance()->sig_send_msg(info.uid, MsgType::MSG_FRIEND_RES, json);
}

