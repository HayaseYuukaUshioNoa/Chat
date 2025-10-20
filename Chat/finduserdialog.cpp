#include "finduserdialog.h"
#include "ui_finduserdialog.h"
#include "tcpmgr.h"
#include <QJsonObject>

FindUserDialog::FindUserDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindUserDialog)
{
    ui->setupUi(this);
    this->setModal(true);

    connect(this, &FindUserDialog::sig_show_adduser_dialog, this, &FindUserDialog::slot_show_adduser_dialog);
}

FindUserDialog::~FindUserDialog()
{
    delete ui;
}

void FindUserDialog::on_pushButton_clicked()
{
    this->hide();
    QJsonObject json;
    json["from_uid"] = info.uid;
    json["to_username"] = ui->username->text();
    json["to_email"] = ui->email->text();

    emit TcpMgr::instance()->sig_send_msg(info.uid, MsgType::MSG_FRIEND_REQ, json);
}

void FindUserDialog::slot_show_adduser_dialog(const QString &username, const QString &email)
{
    ui->username->setText(username);
    ui->email->setText(email);
    this->show();
}

