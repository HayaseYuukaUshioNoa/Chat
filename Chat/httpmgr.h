#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <QObject>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include "sigleton.h"
#include "global.h"

class HttpMgr: public QObject, public Singleton<HttpMgr>,
                public std::enable_shared_from_this<HttpMgr>
{
    friend class Singleton<HttpMgr>;
    Q_OBJECT
private:
    QNetworkAccessManager manager_;
private:
    HttpMgr();
public:
    void post_http_request(QUrl url, QJsonObject json, ReqId req_id, Module module);
    ~HttpMgr() = default;
private slots:
    void slot_http_finished(ReqId req_id, QString res, ErrorCode err_code, Module module);
signals:
    void sig_http_finished(ReqId req_id, QString res, ErrorCode err_code, Module module);
    void sig_regmod_finished(ReqId req_id, QString res, ErrorCode err_code);
    void sig_resetmod_finished(ReqId req_id, QString res, ErrorCode err_code);
    void sig_loginmod_finished(ReqId req_id, QString res, ErrorCode err_code);
};

#endif // HTTPMGR_H
