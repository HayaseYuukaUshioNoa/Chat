#include "friendrequestdialog.h"
#include "ui_friendrequestdialog.h"

FriendRequestDialog::FriendRequestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FriendRequestDialog)
{
    ui->setupUi(this);
    this->setModal(true);
}

FriendRequestDialog::~FriendRequestDialog()
{
    delete ui;
}

void FriendRequestDialog::on_pushButton_clicked()
{
    this->hide();
}

