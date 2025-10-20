#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QStyle>
#include <QRegularExpression>
#include "httpmgr.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "tcpmgr.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    show_tips(tr("用户登录"), false);
    init_http_handlers();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::show_register()
{
    emit switch_register();
}

void LoginWidget::show_reset()
{
    emit switch_reset();
}

void LoginWidget::show_tips(const QString &tips, bool value)
{
    ui->label_tips->setText(tips);
    ui->label_tips->setProperty("error", value);
    // 刷新样式
    ui->label_tips->style()->unpolish(ui->label_tips);
    ui->label_tips->style()->polish(ui->label_tips);
}

bool LoginWidget::check_email()
{
    // 检查邮箱格式
    QString email = ui->lineEdit_email->text();
    QString emailPattern = "^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$";
    QRegularExpression reg(emailPattern);
    bool match = reg.match(email).hasMatch();
    if(match){
        return true;
    }else{
        return false;
    }
}

void LoginWidget::login_btn_enable(bool enable)
{
    ui->pushButton_login->setEnabled(enable);
}

void LoginWidget::init_http_handlers()
{
    // 切换注册界面
    connect(ui->pushButton_register, &QPushButton::clicked, this, &LoginWidget::show_register);
    // 切换重置密码界面
    connect(ui->pushButton_forget, &QPushButton::clicked, this, &LoginWidget::show_reset);
    // 处理登录消息
    connect(HttpMgr::instance().get(), &HttpMgr::sig_loginmod_finished, this, &LoginWidget::slot_loginmod_finished);
    // 登录成功
    connect(TcpMgr::instance().get(), &TcpMgr::sig_login_success, this, &LoginWidget::slot_login_success);
    // 登录失败
    connect(TcpMgr::instance().get(), &TcpMgr::sig_login_failed, this, &LoginWidget::slot_login_failed);
    // Tcp建立连接成功
    connect(TcpMgr::instance().get(), &TcpMgr::sig_connect_success, this, &LoginWidget::slot_connect_success);

    handlers_.insert(ReqId::ID_USER_LOGIN, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        if(error != ErrorCode::CODE_SUCCESS){
            show_tips("登录错误", true);
            login_btn_enable(true);
            return;
        }
        auto uid = json["uid"].toInt();
        auto host = json["host"].toString();
        auto port = json["port"].toInt();
        auto token = json["token"].toString();
        show_tips("正在建立tcp连接...", false);
        qDebug() << "uid is " << uid;
        qDebug() << "host is " << host;
        qDebug() << "port is " << port;
        qDebug() << "token is " << token;
        svr_info_.uid = uid;
        svr_info_.host = host;
        svr_info_.port = port;
        svr_info_.token = token;

        // 连接ChatServer服务器
        emit TcpMgr::instance()->sig_tcp_connect(svr_info_);
    });
}

void LoginWidget::on_pushButton_login_clicked()
{
    login_btn_enable(false);
    if(!check_email()){
        show_tips(tr("邮箱格式不正确"), true);
        login_btn_enable(true);
        return;
    }
    QJsonObject json;
    json["email"] = ui->lineEdit_email->text();
    json["password"] = ui->lineEdit_pwd->text();
    // 发送请求给用户登录服务
    HttpMgr::instance()->post_http_request(QUrl("http://localhost:8080/user_login"),
                                           json, ReqId::ID_USER_LOGIN, Module::MOD_LOGIN);

}

void LoginWidget::slot_loginmod_finished(ReqId req_id, QString res, ErrorCode err_code)
{
    if(err_code != ErrorCode::CODE_SUCCESS){
        show_tips("网络错误", true);
        login_btn_enable(true);
        return;
    }

    QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
    if(json.isNull()){
        show_tips("json解析失败", true);
        login_btn_enable(true);
        return;
    }

    if(!json.isObject()){
        show_tips("json非对象", true);
        login_btn_enable(true);
        return;
    }

    handlers_[req_id](json.object());
    return;
}

void LoginWidget::slot_connect_success(bool success)
{
    if(success){
        show_tips("tcp连接成功，正在登录...", false);
        // 发送登录消息给聊天服务器
        QJsonObject json;
        json["uid"] = svr_info_.uid;
        json["token"] = svr_info_.token;
        emit TcpMgr::instance()->sig_send_msg(svr_info_.uid, MsgType::MSG_LOGIN, json);
        login_btn_enable(true);
    }else{
        show_tips("tcp连接失败", true);
        login_btn_enable(true);
    }
}

void LoginWidget::slot_login_success(const QJsonObject& json)
{
    show_tips("登录成功，正在加载聊天界面...", false);
    login_btn_enable(true);
    qDebug() << "username = " << svr_info_.username;
    svr_info_.username = json["username"].toString();
    g_server_info.username = json["username"].toString();
    g_server_info.uid = json["uid"].toInt();
    g_server_info.email = json["email"].toString();
    emit switch_chat_dialog(svr_info_);
}

void LoginWidget::slot_login_failed()
{
    show_tips("登录失败", true);
    login_btn_enable(true);
}

