#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "global.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
private:
    void show_tips(const QString& tips, bool value);
    bool check_email();
    void login_btn_enable(bool enable);
    void init_http_handlers();
private:
    Ui::LoginWidget *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
    ServerInfo svr_info_;
signals:
    void switch_register();
    void switch_reset();
    void switch_chat_dialog(ServerInfo info);
    void sig_tcp_connect(ServerInfo info);
private slots:
    void show_register();
    void show_reset();
    void on_pushButton_login_clicked();
    void slot_loginmod_finished(ReqId req_id, QString res, ErrorCode err_code);
    void slot_connect_success(bool success);
    void slot_login_success(const QJsonObject& json);
    void slot_login_failed();
};

#endif // LOGINWIDGET_H
