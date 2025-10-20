#include "registerwidget.h"
#include "ui_registerwidget.h"
#include <QRegularExpression>
#include <QStyle>
#include "httpmgr.h"
#include <QJsonDocument>
#include <QUrl>

RegisterWidget::RegisterWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    show_tips(tr("用户注册"), false);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_confirm->setEchoMode(QLineEdit::Password);

    init_http_handlers();

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [this](){
        if(counter_ <= 0){
            timer_->stop();
            emit this->switch_login();
            return;
        }
        --counter_;
        ui->label_tips_2->setText(QString("注册成功，%1s后返回登录界面").arg(counter_));
    });
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::on_pushButton_getVerifyCode_clicked()
{
    // 验证邮箱格式
    QString email = ui->lineEdit_email->text();
    QString emailPattern = "^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$";
    QRegularExpression reg(emailPattern);
    bool match = reg.match(email).hasMatch();
    if(match){
        // 获取验证码
        QJsonObject json;
        json["email"] = email;
        // 发送请求给获取验证码服务
        HttpMgr::instance()->post_http_request(QUrl("http://localhost:8080/get_verify_code"), json,
                                               ReqId::ID_GET_VERIFY_CODE, Module::MOD_REGISTER);
    }else{
        show_tips("邮箱格式不正确", true);
    }
}

void RegisterWidget::init_http_handlers()
{
    // 处理注册消息
    connect(HttpMgr::instance().get(), &HttpMgr::sig_regmod_finished, this, &RegisterWidget::slot_regmod_finished);
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
    handlers_.insert(ReqId::ID_USER_REGISTER, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        if(error != ErrorCode::CODE_SUCCESS){
            show_tips(tr("用户注册错误"), true);
            return;
        }
        auto email = json["email"].toString();
        auto username = json["username"].toString();
        show_tips(tr("用户注册成功"), false);
        qDebug()<< "email is " << email;
        qDebug() << "username is " << username;

        // 切换提示页面
        switch_tips_page();
    });
}

void RegisterWidget::show_tips(const QString &tips, bool value)
{
    ui->label_tips->setText(tips);
    ui->label_tips->setProperty("error", value);
    // 刷新样式
    ui->label_tips->style()->unpolish(ui->label_tips);
    ui->label_tips->style()->polish(ui->label_tips);
}

void RegisterWidget::slot_regmod_finished(ReqId req_id, QString res, ErrorCode err_code)
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

void RegisterWidget::switch_tips_page()
{
    timer_->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    timer_->start(1000);
}


void RegisterWidget::on_pushButton_cancel_clicked()
{
    timer_->stop();
    emit switch_login();
}


void RegisterWidget::on_pushButton_confirm_clicked()
{
    if(ui->lineEdit_username->text() == ""){
        show_tips(tr("用户名不能为空"), false);
        return;
    }
    if(ui->lineEdit_email->text() == ""){
        show_tips(tr("邮箱不能为空"), false);
        return;
    }
    if(ui->lineEdit_pwd->text() == ""){
        show_tips(tr("密码不能为空"), false);
        return;
    }
    if(ui->lineEdit_confirm->text() == ""){
        show_tips(tr("确认密码不能为空"), false);
        return;
    }
    if(ui->lineEdit_pwd->text() != ui->lineEdit_confirm->text()){
        show_tips(tr("密码和确认密码不匹配"), false);
        return;
    }
    if(ui->lineEdit_verifyCode->text() == ""){
        show_tips(tr("验证码不能为空"), false);
        return;
    }

    QJsonObject json_obj;
    json_obj["username"] = ui->lineEdit_username->text();
    json_obj["email"] = ui->lineEdit_email->text();
    json_obj["password"] = ui->lineEdit_pwd->text();
    json_obj["confirm"] = ui->lineEdit_confirm->text();
    json_obj["verifycode"] = ui->lineEdit_verifyCode->text();
    // 发送请求给用户注册服务
    HttpMgr::instance()->post_http_request(QUrl("http://localhost:8080/user_register"),
                                           json_obj, ReqId::ID_USER_REGISTER, Module::MOD_REGISTER);
}

void RegisterWidget::on_pushButton_login_clicked()
{
    timer_->stop();
    emit this->switch_login();
}

