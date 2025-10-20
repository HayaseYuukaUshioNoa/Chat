#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QMap>
#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_pushButton_getVerifyCode_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_confirm_clicked();

private:
    void init_http_handlers();
    void show_tips(const QString& tips, bool value);
    void slot_regmod_finished(ReqId req_id, QString res, ErrorCode err_code);

private:
    Ui::RegisterDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;

signals:
    void switch_login();
};

#endif // REGISTERDIALOG_H
