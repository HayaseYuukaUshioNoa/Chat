#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    connect(ui->pushButton_register, &QPushButton::clicked, this, &LoginDialog::switch_register);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
