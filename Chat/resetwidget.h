#ifndef RESETWIDGET_H
#define RESETWIDGET_H

#include <QWidget>
#include "global.h"

namespace Ui {
class ResetWidget;
}

class ResetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResetWidget(QWidget *parent = nullptr);
    ~ResetWidget();
private:
    void show_tips(const QString& tips, bool value);
    void init_http_handlers();
private:
    Ui::ResetWidget *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
signals:
    void switch_login();
private slots:
    void on_pushButton_verifyCode_clicked();
    void slot_resetmod_finished(ReqId req_id, QString res, ErrorCode err_code);
    void on_pushButton_cancel_clicked();
    void on_pushButton_confirm_clicked();
};

#endif // RESETWIDGET_H
