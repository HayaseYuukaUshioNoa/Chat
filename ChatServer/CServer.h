//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_CSERVER_H
#define CHATSERVER_CSERVER_H


#include "Common.h"
#include <memory>
#include <unordered_map>
#include "Session.h"
#include <mutex>

class CServer : public std::enable_shared_from_this<CServer> {
private:
    ip::tcp::acceptor acceptor_;
    std::unordered_map<uint16_t, std::shared_ptr<Session>> uid_session_;
    std::mutex mutex_;
public:
    ~CServer() = default;

    CServer(asio::io_context &io, unsigned port);

    void do_accept();

    void close_session(uint16_t uid);

    void insert_session(uint16_t uid, std::shared_ptr<Session> session);

    std::shared_ptr<Session> find_session(uint16_t uid);
};


#endif //CHATSERVER_CSERVER_H
