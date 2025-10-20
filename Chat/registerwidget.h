#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QMap>
#include "global.h"
#include <QTimer>

namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();

private slots:
    void on_pushButton_getVerifyCode_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_confirm_clicked();

    void on_pushButton_login_clicked();

private:
    void init_http_handlers();
    void show_tips(const QString& tips, bool value);
    void slot_regmod_finished(ReqId req_id, QString res, ErrorCode err_code);
    void switch_tips_page();

private:
    Ui::RegisterWidget *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
    QTimer* timer_ = nullptr;
    int counter_ = 5;
signals:
    void switch_login();
};

#endif // REGISTERWIDGET_H
