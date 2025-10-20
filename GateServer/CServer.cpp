//
// Created by tom on 25-10-2.
//

#include "CServer.h"
#include "HttpConnection.h"
#include "Logger.h"

CServer::CServer(asio::io_context &io, unsigned int port) : acceptor_(io, tcp::endpoint(tcp::v4(), port))
{
}

void CServer::do_accept()
{
    auto self = shared_from_this();
    acceptor_.async_accept([self](boost::system::error_code err, tcp::socket socket) {
        if (!err) {
            std::string ip = socket.remote_endpoint().address().to_string();
            uint16_t port = socket.remote_endpoint().port();
            LOG_INFO("New connection ip: {}, port: {}", ip, port);
            std::make_shared<HttpConnection>(std::move(socket))->start();
        } else {
            LOG_WARN("async_accept error");
        }
        self->do_accept();
    });
}