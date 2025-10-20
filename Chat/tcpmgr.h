#ifndef TCPMGR_H
#define TCPMGR_H

#include <QObject>
#include "global.h"
#include "sigleton.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonObject>
#include <QMap>

enum ParseStatus{
    ParseId,
    ParseType,
    ParseLen,
    ParseContent,
    ParseComplete,
    ParseError
};

class TcpMgr: public QObject, public Singleton<TcpMgr>,
               public std::enable_shared_from_this<TcpMgr>
{
    friend class Singleton<TcpMgr>;
    Q_OBJECT
    TcpMgr();
public:
    ~TcpMgr() = default;
    void init_handlers();
    ParseStatus parse(const QByteArray& data);
    bool connection_ = false;
private:
    void process_byte(char c);
    void handle_msg();
    void reset_status();
private:
    QTcpSocket socket_;
    QString host_;
    int port_ = 0;
    QMap<quint16, std::function<void(const QJsonObject&)>> handlers_;

    QByteArray buffer_;
    int read_bytes_ = 0;
    quint16 msg_id_ = 0;
    quint16 msg_type_ = 0;
    quint16 msg_len_ = 0;
    QByteArray content_;
    ParseStatus cur_status_ = ParseId;
signals:
    void sig_connect_success(bool success);
    void sig_send_msg(quint16 uid, quint16 msg_type, QJsonObject json);
    void sig_login_failed();
    void sig_login_success(const QJsonObject& json);
    void sig_tcp_connect(ServerInfo info);
    void sig_find_failed();
    void sig_find_success(const QJsonObject& json);
    void sig_friend_req_failed();
    void sig_friend_req_success(const QJsonObject& json);
    void sig_show_friend_req(const QJsonObject& json, bool success);
    void sig_friend_response(const QJsonObject& json, bool success);
    void sig_show_contact(const QJsonObject& json, bool success);
    void sig_show_messages(const QJsonObject& json, bool success);
    void sig_send_message(const QJsonObject& json, bool success);
    void sig_recv_message(const QJsonObject& json, bool success);
private slots:
    void slot_tcp_connect(ServerInfo info);
    void slot_send_msg(quint16 uid, quint16 msg_type, QJsonObject json);
};

#endif // TCPMGR_H
