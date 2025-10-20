#include "findfaileddialog.h"
#include "ui_findfaileddialog.h"

FindFailedDialog::FindFailedDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindFailedDialog)
{
    ui->setupUi(this);
    this->setModal(true);
}

FindFailedDialog::~FindFailedDialog()
{
    delete ui;
}

void FindFailedDialog::on_pushButton_clicked()
{
    this->hide();
}

