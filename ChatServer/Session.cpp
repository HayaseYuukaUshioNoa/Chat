//
// Created by tom on 25-10-13.
//

#include "Session.h"
#include <cstring>
#include "LogicSystem.h"
#include "Logger.h"
#include "nlohmann/json.hpp"
#include "ErrorCode.h"
#include "CServer.h"

using json = nlohmann::json;

Session::Session(tcp::socket socket, std::shared_ptr<CServer> server) : socket_(std::move(socket)), server_(server),
is_running_(true)
{
    // 强制初始化头部缓冲区为6字节（必须）
    header_.resize(6);
}

/*
 * uid: 2
 * msg_type: 2
 * msg_len: 2
 * content: ?
 */
void Session::start()
{
    do_read();
}

void Session::do_read()
{
    read_header();
}

void Session::do_write()
{
    auto self = shared_from_this();
    if (!is_running_ || write_buffer_.empty()) {
        LOG_DEBUG("uid:{} session stopped or write_buffer empty, skip do_write", uid_);
        return;
    }
    asio::async_write(socket_, asio::buffer(write_buffer_, write_buffer_.size()),
        [self](error_code err, size_t transferred) {
        if (!err) {
            LOG_INFO("uid:{} async_write success", self->uid_);
            self->do_read();
        } else {
            LOG_WARN("uid:{} async_write error", self->uid_);
            auto service = self->server_.lock();
            if (service) {
                service->close_session(self->uid_);
            }
        }
    });
}

void Session::read_header()
{
    auto self = shared_from_this();
    if (!is_running_) {
        LOG_DEBUG("uid:{} session stopped, skip read_header", uid_);
        return;
    }
    asio::async_read(socket_, asio::buffer(header_, header_.size()), [self](error_code err, size_t transferred) {
        if (!err) {
            LOG_INFO("uid:{} read header success", self->uid_);
            self->process_header();
            self->read_body();
        } else {
            LOG_WARN("uid:{} read header failed", self->uid_);
            auto service = self->server_.lock();
            if (service) {
                service->close_session(self->uid_);
            }
        }
    });
}

void Session::process_header()
{
    if (header_.size() != sizeof(uid_) + sizeof(type_) + sizeof(len_)) {
        LOG_ERROR("Invalid header size: {} (expected 6)", header_.size());
        close_session_safe();
        return;
    }

    LOG_INFO("Data in HEX: [{}]", bytes_to_hex(reinterpret_cast<uint8_t*>(header_.data()), header_.size()));
    uint16_t uid = 0;
    memcpy(&uid, header_.data(), sizeof(uid));
    uint16_t type = 0;
    memcpy(&type, header_.data() + sizeof(uid), sizeof(type));
    uint16_t len = 0;
    memcpy(&len, header_.data() + sizeof(uid) + sizeof(type), sizeof(len));

    if (len > 0xFFFF) {
        LOG_ERROR("Invalid len (raw): {} (exceeds max 65535)", len);
        close_session_safe();
        return;
    }

    uid_ = socket_ops::network_to_host_short(uid);
    type_ = socket_ops::network_to_host_short(type);
    len_ = socket_ops::network_to_host_short(len);

    const size_t MAX_BODY_LEN = 1024 * 1024;
    if (len_ <= 0 || len_ > MAX_BODY_LEN) {
        LOG_ERROR("Invalid len_: {} (must be 1~{})", len_, MAX_BODY_LEN);
        close_session_safe();
        return;
    }

    LOG_INFO("(uid, type, len)->({}, {}, {})", uid_, type_, len_);
    body_.resize(len_);
}

void Session::read_body()
{
    auto self = shared_from_this();
    if (!is_running_) {
        LOG_DEBUG("uid:{} session stopped, skip read_body", uid_);
        return;
    }
    asio::async_read(socket_, asio::buffer(body_, body_.size()), [self](error_code err, size_t transferred) {
        if (!err) {
            LOG_INFO("uid:{} read body success", self->uid_);
            self->process_body();
            self->handle_msg();
        } else {
            LOG_WARN("uid:{} read body failed", self->uid_);
            auto service = self->server_.lock();
            if (service) {
                service->close_session(self->uid_);
            }
        }
    });
}

void Session::process_body()
{
    LOG_INFO("body: {}", std::string(body_.data(), body_.size()));
}

void Session::handle_msg()
{
    auto self = shared_from_this();
    bool res = LogicSystem::instance()->handle_message(type_, self);
    if (!res) {
        json root;
        root["error"] = ErrorCode::ERROR;
        std::string s = root.dump();
        send_response(type_, s);
    }
}

void Session::reset()
{
    body_.clear();
    write_buffer_.clear();
    uid_ = 0;
    type_ = 0;
    len_ = 0;
    header_.resize(sizeof(uid_) + sizeof(type_) + sizeof(len_));
}

std::string Session::bytes_to_hex(const uint8_t* data, size_t len, bool uppercase)
{
    std::string hex_str;
    hex_str.reserve(len * 3);
    for (size_t i = 0; i < len; ++i) {
        if (uppercase) {
            hex_str += fmt::format("{:02X} ", data[i]);
        } else {
            hex_str += fmt::format("{:02x} ", data[i]);
        }
    }
    if (!hex_str.empty()) {
        hex_str.pop_back();
    }
    return hex_str;
}

void Session::close_session_safe()
{
    boost::system::error_code ec;
    if (socket_.is_open()) {
        socket_.close(ec);
        if (ec) LOG_WARN("uid:{} close socket error: {}", uid_, ec.message());
    }

    reset();

    auto service = server_.lock();
    if (service && uid_ != 0) {
        service->close_session(uid_);
    }
}

uint16_t Session::uid() const
{
    return uid_;
}

uint16_t Session::type() const
{
    return type_;
}

const std::vector<char>& Session::body() const
{
    return body_;
}

void Session::set_uid(uint16_t uid)
{
    uid_ = uid;
}

void Session::send_response(uint16_t msg_type, const std::string& content)
{
    if (!is_running_ || !socket_.is_open()) {
        LOG_WARN("uid:{} cannot send response (session stopped or socket closed)", uid_);
        return;
    }
    write_buffer_ = LogicSystem::instance()->prepare_msg(uid_, msg_type, content.length(), content);
    do_write();
}

std::weak_ptr<CServer> Session::server() const
{
    return server_;
}
