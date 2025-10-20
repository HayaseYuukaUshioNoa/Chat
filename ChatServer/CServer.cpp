//
// Created by tom on 25-10-13.
//

#include "CServer.h"
#include "Session.h"
#include "Logger.h"

CServer::CServer(asio::io_context &io, unsigned int port) : acceptor_(io, tcp::endpoint(tcp::v4(), port))
{
}

void CServer::do_accept()
{
    auto self = shared_from_this();
    acceptor_.async_accept([self](boost::system::error_code err, tcp::socket socket) {
        try {
            if (!err) {
                std::string ip = socket.remote_endpoint().address().to_string();
                uint16_t port = socket.remote_endpoint().port();
                LOG_INFO("New connection ip: {}, port: {}", ip, port);
                std::make_shared<Session>(std::move(socket), self)->start();
            } else {
                LOG_WARN("async_accept error");
            }
        } catch (const std::exception &e) {
            LOG_WARN("{}", e.what());
        }
        self->do_accept();
    });
}

void CServer::close_session(uint16_t uid)
{
    std::lock_guard<std::mutex> lockGuard(mutex_);
    auto iter = uid_session_.find(uid);
    if (iter == uid_session_.end()) {
        LOG_WARN("uid: {} is no session", uid);
        return;
    }
    uid_session_.erase(iter);
    LOG_INFO("uid: {} close session success", uid);
}

void CServer::insert_session(uint16_t uid, std::shared_ptr<Session> session)
{
    std::lock_guard<std::mutex> lockGuard(mutex_);
    uid_session_[uid] = session;
    LOG_INFO("uid: {} insert/update session success", uid);
}

std::shared_ptr<Session> CServer::find_session(uint16_t uid)
{
    std::lock_guard<std::mutex> lockGuard(mutex_);
    auto iter = uid_session_.find(uid);
    if (iter == uid_session_.end()) {
        LOG_INFO("uid: {} is no session", uid);
        return nullptr;
    } else {
        LOG_INFO("uid: {} find session success", uid);
        return iter->second;
    }
}
