#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog_ = new ChatDialog();
    dialog_->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint |
                            Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    dialog_->resize(1000, 800);
    login_ = new LoginWidget();
    connect(login_, &LoginWidget::switch_register, this, &MainWindow::to_register);
    connect(login_, &LoginWidget::switch_reset, this, &MainWindow::to_reset);
    connect(login_, &LoginWidget::switch_chat_dialog, this, &MainWindow::to_chat_dialog);
    // 设置CentralWidget会释放旧的Widget
    setCentralWidget(login_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::to_register()
{
    register_ = new RegisterWidget();
    connect(register_, &RegisterWidget::switch_login, this, &MainWindow::to_login);
    setCentralWidget(register_);
}

void MainWindow::to_login()
{
    login_ = new LoginWidget();
    connect(login_, &LoginWidget::switch_register, this, &MainWindow::to_register);
    connect(login_, &LoginWidget::switch_reset, this, &MainWindow::to_reset);
    connect(login_, &LoginWidget::switch_chat_dialog, this, &MainWindow::to_chat_dialog);
    setCentralWidget(login_);
}

void MainWindow::to_reset()
{
    reset_ = new ResetWidget();
    connect(reset_, &ResetWidget::switch_login, this, &MainWindow::to_login);
    setCentralWidget(reset_);
}

void MainWindow::to_chat_dialog(ServerInfo info)
{
    dialog_->info = info;
    emit dialog_->sig_show_dialog();
}
