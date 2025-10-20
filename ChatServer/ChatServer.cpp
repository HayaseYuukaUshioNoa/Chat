//
// Created by tom on 25-10-13.
//

#include "CServer.h"
#include "ConfigMgr.h"
#include <stdexcept>
#include "Logger.h"

int main()
{
    try {
        asio::io_context io;
        std::string port = ConfigMgr::instance()->get_value("ChatServer", "port");
        int port_num = std::stoi(port);
        asio::signal_set signals(io, SIGINT, SIGTERM);
        signals.async_wait([&io](boost::system::error_code err, int sig) {
            if (!err) {
                io.stop();
                LOG_INFO("ChatServer close");
            } else {
                LOG_WARN("signal async_wait error");
            }
        });
        std::make_shared<CServer>(io, port_num)->do_accept();
        // 多个线程执行同一个 io_context（共享模型）
        // 每个线程运行独立 io_context（独立模型）
        io.run();
    } catch (const std::exception &e) {
        LOG_WARN("{}", e.what());
        return 1;
    }
    return 0;
}