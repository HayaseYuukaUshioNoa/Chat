//
// Created by tom on 25-10-2.
//

#include "HttpConnection.h"
#include "LogicSystem.h"
#include "UriCode.h"
#include "Logger.h"

HttpConnection::HttpConnection(tcp::socket socket) : socket_(std::move(socket))
{

}

void HttpConnection::start()
{
    auto self = shared_from_this();
    http::async_read(socket_, buffer_, request_, [self](beast::error_code err, std::size_t transferred) {
        if (!err) {
            // 解析请求
            self->handle_request();
            // 开启定时器
            self->check_deadline();
        } else {
            LOG_WARN("http async_read error");
        }
    });
}

void HttpConnection::handle_request()
{
    response_.version(request_.version());
    response_.keep_alive(false);
    if (request_.method() == http::verb::get) {
        // Get请求可能带有参数
        path_ = extract_path(request_.target());
        // 逻辑类处理Get请求
        bool success = LogicSystem::instance()->handle_get(path_, shared_from_this());
        if (!success) {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "url not found\r\n";
            response_.prepare_payload();
            write_response();
            return;
        }
        response_.result(http::status::ok);
        response_.set(http::field::server, "GateServer");
        response_.set(http::field::content_type, "text/plain");
        beast::ostream(response_.body()) << "url found\r\n";
        response_.prepare_payload();
        write_response();
        return;
    }

    if (request_.method() == http::verb::post) {
        path_ = extract_path(request_.target());
        bool success = LogicSystem::instance()->handle_post(path_, shared_from_this());
        if (!success) {
            response_.result(http::status::not_found);
            response_.prepare_payload();
            write_response();
            return;
        }
        response_.result(http::status::ok);
        response_.set(http::field::server, "GateServer");
        response_.prepare_payload();
        write_response();
        return;
    }
}

void HttpConnection::write_response()
{
    auto self = shared_from_this();
    http::async_write(socket_, response_, [self](beast::error_code err, std::size_t transferred) {
        // 关闭发送缓冲区，发送剩余数据以及FIN序列
        std::string ip = self->socket_.remote_endpoint().address().to_string();
        uint16_t port = self->socket_.remote_endpoint().port();
        LOG_INFO("Close connection ip: {}, port: {}", ip, port);
        self->socket_.close();
        self->deadline_.cancel();
    });
}

void HttpConnection::check_deadline()
{
    auto self = shared_from_this();
    // 定时器到期关闭连接
    deadline_.async_wait([self](beast::error_code err) {
        if (!err) {
            self->socket_.close();
        }
    });
}
