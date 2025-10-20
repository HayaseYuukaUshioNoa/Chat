#include "loadingdialog.h"
#include "ui_loadingdialog.h"
#include <QMovie>

LoadingDialog::LoadingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    // 配置模态对话框
    setModal(true);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); // 无边框
    setAttribute(Qt::WA_TranslucentBackground);           // 背景透明
    setFixedSize(parent->size());

    QMovie* movie = new QMovie(":/res/loading.gif");
    ui->loading_label->setMovie(movie);
    movie->start();
}

LoadingDialog::~LoadingDialog()
{
    qDebug() << "free LoadingDialog";
    delete ui;
}
