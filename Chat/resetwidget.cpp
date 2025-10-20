#include "resetwidget.h"
#include "ui_resetwidget.h"
#include <QStyle>
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
#include "httpmgr.h"
#include <QTimer>

ResetWidget::ResetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResetWidget)
{
    ui->setupUi(this);
    ui->lineEdit_newPassword->setEchoMode(QLineEdit::Password);
    show_tips(tr("重置密码"), false);
    init_http_handlers();
}

ResetWidget::~ResetWidget()
{
    delete ui;
}

void ResetWidget::show_tips(const QString &tips, bool value)
{
    ui->label_tips->setText(tips);
    ui->label_tips->setProperty("error", value);
    // 刷新样式
    ui->label_tips->style()->unpolish(ui->label_tips);
    ui->label_tips->style()->polish(ui->label_tips);
}

void ResetWidget::init_http_handlers()
{
    // 处理重置密码消息
    connect(HttpMgr::instance().get(), &HttpMgr::sig_resetmod_finished, this, &ResetWidget::slot_resetmod_finished);
    handlers_.insert(ReqId::ID_GET_VERIFY_CODE, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        if(error != ErrorCode::CODE_SUCCESS){
            show_tips("验证码错误", true);
            return;
        }

        auto email = json["email"].toString();
        show_tips("验证码已发送到邮箱", false);
        qDebug() << "email is " << email;
    });
    handlers_.insert(ReqId::ID_RESET_PASSWORD, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        if(error != ErrorCode::CODE_SUCCESS){
            show_tips(tr("重置密码错误"), true);
            return;
        }
        auto email = json["email"].toString();
        auto username = json["username"].toString();
        show_tips(tr("重置密码成功"), false);
        qDebug()<< "email is " << email;
        qDebug() << "username is " << username;
        // 2s后切换登录界面
        QTimer::singleShot(2000, [this](){
            emit this->switch_login();
        });
    });
}

void ResetWidget::on_pushButton_verifyCode_clicked()
{
    // 验证邮箱格式
    QString email = ui->lineEdit_email->text();
    QString emailPattern = "^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$";
    QRegularExpression reg(emailPattern);
    bool match = reg.match(email).hasMatch();
    if(match){
        QJsonObject json;
        json["email"] = email;
        // 发送请求给获取验证码服务
        HttpMgr::instance()->post_http_request(QUrl("http://localhost:8080/get_verify_code"), json,
                                               ReqId::ID_GET_VERIFY_CODE, Module::MOD_RESET);
    }else{
        show_tips("邮箱格式不正确", true);
    }
}

void ResetWidget::slot_resetmod_finished(ReqId req_id, QString res, ErrorCode err_code)
{
    if(err_code != ErrorCode::CODE_SUCCESS){
        show_tips("网络错误", true);
        return;
    }

    QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
    if(json.isNull()){
        show_tips("json解析失败", true);
        return;
    }

    if(!json.isObject()){
        show_tips("json非对象", true);
        return;
    }

    handlers_[req_id](json.object());
    return;
}


void ResetWidget::on_pushButton_cancel_clicked()
{
    emit this->switch_login();
}


void ResetWidget::on_pushButton_confirm_clicked()
{
    if(ui->lineEdit_username->text() == ""){
        show_tips(tr("用户名不能为空"), false);
        return;
    }
    if(ui->lineEdit_email->text() == ""){
        show_tips(tr("邮箱不能为空"), false);
        return;
    }
    if(ui->lineEdit_newPassword->text() == ""){
        show_tips(tr("新密码不能为空"), false);
        return;
    }
    if(ui->lineEdit_verifyCode->text() == ""){
        show_tips(tr("验证码不能为空"), false);
        return;
    }

    QJsonObject json_obj;
    json_obj["username"] = ui->lineEdit_username->text();
    json_obj["email"] = ui->lineEdit_email->text();
    json_obj["password"] = ui->lineEdit_newPassword->text();
    json_obj["verifycode"] = ui->lineEdit_verifyCode->text();
    // 发送请求给用户注册服务
    HttpMgr::instance()->post_http_request(QUrl("http://localhost:8080/reset_pwd"),
                                           json_obj, ReqId::ID_RESET_PASSWORD, Module::MOD_RESET);
}

