#include "tcpmgr.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QDataStream>
#include <QAbstractSocket>
#include <QtEndian>
#include <QTimer>

TcpMgr::TcpMgr()
{
    init_handlers();
}

void TcpMgr::init_handlers()
{
    // 建立连接
    connect(&socket_, &QTcpSocket::connected, this, [this](){
        qDebug() << "connect chat server success";
        connection_ = true;
        emit this->sig_connect_success(true);
    });
    // 错误
    connect(&socket_, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError err){
        qDebug() << "errorOccurred: " << socket_.errorString();
        // 关闭连接
        connection_ = false;
        socket_.close();
        emit this->sig_connect_success(false);
    });
    // 连接断开
    connect(&socket_, &QTcpSocket::disconnected, this, [this](){
        qDebug() << "disconnected from chat server";
        socket_.close();
        connection_ = false;
        emit this->sig_connect_success(false);
    });
    // 数据处理
    connect(&socket_, &QTcpSocket::readyRead, this, [this](){
        buffer_.append(socket_.readAll());
        ParseStatus status = parse(buffer_);
        if(status == ParseError){
            qDebug() << "parse data error";
            connection_ = false;
            socket_.close();
            emit this->sig_connect_success(false);
        }else if(status == ParseComplete){
            qDebug() << "parse data complete";
            buffer_ = buffer_.mid(read_bytes_);
            // 处理完整消息
            handle_msg();
            reset_status();
        }else{
            qDebug() << "parse data no complete";
        }
    });
    connect(this, &TcpMgr::sig_send_msg, this, &TcpMgr::slot_send_msg);
    connect(this, &TcpMgr::sig_tcp_connect, this, &TcpMgr::slot_tcp_connect);
    // 处理消息
    handlers_.insert(MsgType::MSG_LOGIN, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_login_failed();
            reset_status();
            return;
        }
        emit sig_login_success(json);
        reset_status();
    });
    handlers_.insert(MsgType::MSG_FIND, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_find_failed();
            reset_status();
            return;
        }
        emit sig_find_success(json);
        reset_status();
    });
    handlers_.insert(MsgType::MSG_FRIEND_REQ, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_friend_req_failed();
            reset_status();
            return;
        }
        emit sig_friend_req_success(json);
        reset_status();
    });
    handlers_.insert(MsgType::MSG_SHOW_FRIEND_REQ, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_show_friend_req(json, false);
            reset_status();
            return;
        }
        emit sig_show_friend_req(json, true);
        reset_status();
    });
    handlers_.insert(MsgType::MSG_FRIEND_RES, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_friend_response(json, false);
            reset_status();
            return;
        }
        emit sig_friend_response(json, true);
        reset_status();
    });
    handlers_.insert(MsgType::MSG_SHOW_CONTACT, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_show_contact(json, false);
            reset_status();
            return;
        }
        emit sig_show_contact(json, true);
        reset_status();
    });
    handlers_.insert(MsgType::MSG_SHOW_MESSAGES, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_show_messages(json, false);
            reset_status();
            return;
        }
        emit sig_show_messages(json, true);
        reset_status();
    });
    handlers_.insert(MsgType::MSG_SEND_MESSAGE, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            reset_status();
            return;
        }
        reset_status();
    });
    handlers_.insert(MsgType::MSG_RECV_MESSAGE, [this](const QJsonObject& json){
        int error = json["error"].toInt();
        qDebug() << "error: " << error;
        if(error != ErrorCode::CODE_SUCCESS){
            emit sig_recv_message(json, false);
            reset_status();
            return;
        }
        emit sig_recv_message(json, false);
        reset_status();
    });
}

ParseStatus TcpMgr::parse(const QByteArray &data)
{
    for(quint32 i = read_bytes_; i < data.length(); ++i){
        char c = data[i];
        process_byte(c);
    }
    return cur_status_;
}

void TcpMgr::process_byte(char c)
{
    switch(cur_status_){
    case ParseId:
        content_ += c;
        read_bytes_ += 1;
        if(read_bytes_ == sizeof(quint16)){
            QDataStream input(&content_, QIODevice::ReadOnly);
            input >> msg_id_;
            qDebug() << "id: " << msg_id_;
            cur_status_ = ParseType;
            content_.clear();
        }
        break;
    case ParseType:
        content_ += c;
        read_bytes_ += 1;
        if(read_bytes_ == sizeof(quint16) * 2){
            QDataStream input(&content_, QIODevice::ReadOnly);
            input >> msg_type_;
            qDebug() << "type: " << msg_type_;
            cur_status_ = ParseLen;
            content_.clear();
        }
        break;
    case ParseLen:
        content_ += c;
        read_bytes_ += 1;
        if(read_bytes_ == sizeof(quint16) * 3){
            QDataStream input(&content_, QIODevice::ReadOnly);
            input >> msg_len_;
            qDebug() << "len: " << msg_len_;
            cur_status_ = ParseContent;
            content_.clear();
        }
        break;
    case ParseContent:
        content_ += c;
        read_bytes_ += 1;
        if(read_bytes_ == sizeof(quint16) * 3 + msg_len_){
            qDebug() << "content: " << content_;
            cur_status_ = ParseComplete;
        }
        break;
    case ParseComplete:
    case ParseError:
        break;
    }
}

void TcpMgr::handle_msg()
{
    auto doc = QJsonDocument::fromJson(content_);
    if(doc.isNull()){
        qDebug() << "json is null";
        reset_status();
        return;
    }
    if(!doc.isObject()){
        qDebug() << "json is not object";
        reset_status();
        return;
    }
    handlers_[msg_type_](doc.object());
}

void TcpMgr::reset_status()
{
    buffer_.clear();
    read_bytes_ = 0;
    msg_id_ = 0;
    msg_type_ = 0;
    msg_len_ = 0;
    content_.clear();
    cur_status_ = ParseId;
}

void TcpMgr::slot_tcp_connect(ServerInfo info)
{
    qDebug() << "connecting to chat server...";
    host_ = info.host;
    port_ = info.port;
    socket_.connectToHost(host_, port_);
}

void TcpMgr::slot_send_msg(quint16 uid, quint16 msg_type, QJsonObject json)
{
    QByteArray data = QJsonDocument(json).toJson();
    QByteArray message;
    QDataStream out(&message, QIODevice::WriteOnly);

    // 1. 关键修改：设置字节序为大端（网络字节序）
    out.setByteOrder(QDataStream::BigEndian);
    // 2. 固定数据流版本（原有逻辑，保留）
    out.setVersion(QDataStream::Qt_5_15);
    // 3. 写入头部字段（uid/msg_type/len），此时按大端写入
    out << uid << msg_type << (quint16)data.length();
    // 4. 追加消息体（原有逻辑，保留）
    message.append(data);

    // 发送数据
    socket_.write(message);
}
