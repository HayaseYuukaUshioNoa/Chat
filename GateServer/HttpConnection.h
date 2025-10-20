//
// Created by tom on 25-10-2.
//

#ifndef GATESERVER_HTTPCONNECTION_H
#define GATESERVER_HTTPCONNECTION_H

#include "Common.h"
#include <memory>

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
    friend class LogicSystem;

private:
    tcp::socket socket_;
    beast::flat_buffer buffer_{8192};
    http::request<http::dynamic_body> request_;
    http::response<http::dynamic_body> response_;
    asio::steady_timer deadline_{socket_.get_executor(), std::chrono::seconds(60)};
    // URI path
    std::string path_;
    // URI query params
    std::unordered_map<std::string, std::string> params_;

    void check_deadline();

    void write_response();

    void handle_request();

public:
    HttpConnection(tcp::socket socket);

    void start();
};


#endif //GATESERVER_HTTPCONNECTION_H
