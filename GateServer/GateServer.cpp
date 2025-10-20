#include <stdexcept>
#include "CServer.h"
#include <vector>
#include "RedisPool.h"
#include "ConfigMgr.h"
#include "Logger.h"

int main()
{
    try {
        asio::io_context io;
        std::string port = ConfigMgr::instance()->get_value("GateServer", "port");
        int port_num = std::stoi(port);
        asio::signal_set signals(io, SIGINT, SIGTERM);
        signals.async_wait([&io](boost::system::error_code err, int sig) {
            if (!err) {
                io.stop();
                LOG_INFO("GateServer close");
            } else {
                LOG_WARN("signals async_wait failed");
            }
        });
        std::make_shared<CServer>(io, port_num)->do_accept();
        io.run();
    } catch (const std::exception &e) {
        LOG_WARN("{}", e.what());
        return 1;
    }
    return 0;
}
