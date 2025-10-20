//
// Created by tom on 25-10-10.
//

#include "StatusServerImpl.h"
#include "ConfigMgr.h"
#include <memory>
#include <iostream>
#include "Logger.h"
#include <csignal>
#include <atomic>

std::unique_ptr<grpc::Server> g_server;
std::atomic<bool> g_shutdown_requested{false};

void sig_handler(int signum)
{
    g_shutdown_requested = true;
}

int main()
{
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    try {
        std::thread shutdown_thread([] {
            while (!g_shutdown_requested.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            LOG_INFO("StatusServer shutdown");
            auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(5);
            g_server->Shutdown(deadline);
        });
        std::string host = ConfigMgr::instance()->get_value("StatusServer", "host");
        std::string port = ConfigMgr::instance()->get_value("StatusServer", "port");
        std::string server_address = host + ":" + port;
        StatusServerImpl status_service;
        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&status_service);
        g_server = builder.BuildAndStart();
        LOG_INFO("StatusServer listening on {}", server_address);
        g_server->Wait();
        shutdown_thread.join();
    } catch (const std::exception &e) {
        LOG_WARN("{}", e.what());
        return 1;
    }
    return 0;
}