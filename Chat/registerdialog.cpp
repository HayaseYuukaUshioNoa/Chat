#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QRegularExpression>
#include <QStyle>
#include "httpmgr.h"
#include <QJsonDocument>
#include <QUrl>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_confirm->setEchoMode(QLineEdit::Password);
    connect(HttpMgr::instance().get(), &HttpMgr::sig_regmod_finished, this, &RegisterDialog::slot_regmod_finished);
    init_http_handlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_pushButton_getVerifyCode_clicked()
{
    // 获取验证码
    // 验证邮箱格式
    QString email = ui->lineEdit_email->text();
    QString emailPattern = "^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$";
    QRegularExpression reg(emailPattern);
    bool match = reg.match(email).hasMatch();
    if(match){
        // 获取验证码
        QJsonObject json;
        json["email"] = email;
        HttpMgr::instance()->post_http_request(QUrl("http://localhost:8080/get_verify_code"), json,
                                               ReqId::ID_GET_VERIFY_CODE, Module::MOD_REGISTER);
    }else{
        show_tips("邮箱格式不正确", true);
    }
}

void RegisterDialog::init_http_handlers()
{
    handlers_.insert(ReqId::ID_GET_VERIFY_CODE, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        if(error != ErrorCode::CODE_SUCCESS){
            show_tips("参数错误", true);
            return;
        }

        auto email = json["email"].toString();
        show_tips("验证码已发送到邮箱", false);
        qDebug() << "email is " << email << "\n";
    });
}

void RegisterDialog::show_tips(const QString &tips, bool value)
{
    ui->label_tips->setText(tips);
    ui->label_tips->setProperty("error", value);
    // 刷新样式
    ui->label_tips->style()->unpolish(ui->label_tips);
    ui->label_tips->style()->polish(ui->label_tips);
}

void RegisterDialog::slot_regmod_finished(ReqId req_id, QString res, ErrorCode err_code)
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
        show_tips("json解析失败", true);
        return;
    }

    handlers_[req_id](json.object());
    return;
}


void RegisterDialog::on_pushButton_cancel_clicked()
{
    emit switch_login();
}


void RegisterDialog::on_pushButton_confirm_clicked()
{
    emit switch_login();
}

