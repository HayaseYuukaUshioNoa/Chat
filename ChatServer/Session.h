//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_SESSION_H
#define CHATSERVER_SESSION_H

#include "Common.h"
#include <memory>
#include <vector>
#include "LogicSystem.h"

class CServer;

class Session : public std::enable_shared_from_this<Session> {
    friend class CServer;

    friend class LogicSystem;

private:
    // 核心修改：单一接收缓冲区（累积所有接收到的数据）
    std::vector<char> recv_buffer_;
    // 核心修改：已处理数据的索引指针（指向 recv_buffer_ 中未处理数据的起始位置）
    size_t recv_index_ = 0;

    tcp::socket socket_;
    std::weak_ptr<CServer> server_;
    std::vector<char> header_;
    std::vector<char> body_;
    std::vector<char> write_buffer_;
    uint16_t uid_ = 0;
    uint16_t type_ = 0;
    uint16_t len_ = 0;
    bool is_running_ = false;

    void read_header();

    void process_header();

    void read_body();

    void process_body();

    void handle_msg();

    void reset();

    void close_session_safe();

    std::string bytes_to_hex(const uint8_t* data, size_t len, bool uppercase = false);

    void process_recv_buffer();

    bool parse_header_safe();

    void reset_recv_state();

public:
    Session(tcp::socket socket, std::shared_ptr<CServer> server);

    void start();

    void do_read();

    void do_write();

    uint16_t uid() const;

    uint16_t type() const;

    std::weak_ptr<CServer> server() const;

    const std::vector<char>& body() const;

    void set_uid(uint16_t uid);

    void send_response(uint16_t msg_type, const std::string& content);

};


#endif //CHATSERVER_SESSION_H
