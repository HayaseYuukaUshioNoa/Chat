#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "registerwidget.h"
#include "resetwidget.h"
#include "chatdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginWidget* login_ = nullptr;
    RegisterWidget* register_ = nullptr;
    ResetWidget* reset_ = nullptr;
    ChatDialog* dialog_ = nullptr;

private slots:
    void to_register();
    void to_login();
    void to_reset();
    void to_chat_dialog(ServerInfo info);
};
#endif // MAINWINDOW_H
