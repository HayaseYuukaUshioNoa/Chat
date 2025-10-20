#include "httpmgr.h"
#include <QJsonDocument>
#include <QNetworkReply>

HttpMgr::HttpMgr()
{
    connect(this, &HttpMgr::sig_http_finished, this, &HttpMgr::slot_http_finished);
}

void HttpMgr::post_http_request(QUrl url, QJsonObject json, ReqId req_id, Module module)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request = QNetworkRequest(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    auto self = shared_from_this();
    QNetworkReply* reply = manager_.post(request, data);
    connect(reply, &QNetworkReply::finished, this, [self, reply, req_id, module](){
        // 发生错误
        if(reply->error() != QNetworkReply::NoError){
            emit self->sig_http_finished(req_id, "", ErrorCode::CODE_NETWORK_ERROR, module);
            reply->deleteLater();
            return;
        }
        QString res = reply->readAll();
        emit self->sig_http_finished(req_id, res, ErrorCode::CODE_SUCCESS, module);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finished(ReqId req_id, QString res, ErrorCode err_code, Module module)
{
    // 注册模块
    if(module == Module::MOD_REGISTER){
        emit this->sig_regmod_finished(req_id, res, err_code);
    }
    // 重置密码模块
    if(module == Module::MOD_RESET){
        emit this->sig_resetmod_finished(req_id, res, err_code);
    }
    // 登录模块
    if(module == Module::MOD_LOGIN){
        emit this->sig_loginmod_finished(req_id, res, err_code);
    }
}
