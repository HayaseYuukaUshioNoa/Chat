#include <iostream>
#include "VerifyServerImpl.h"
#include "ConfigMgr.h"
#include <boost/python.hpp>
#include <csignal>
#include <atomic>
#include <chrono>
#include <thread>
#include "Logger.h"

std::unique_ptr<grpc::Server> g_server;
std::atomic<bool> g_shutdown_requested{ false };

PyThreadState* initialize_python()
{
    Py_Initialize();  // GIL已自动初始化
    return PyEval_SaveThread();  // 释放主线程GIL，允许其他线程获取
}

void finalize_python(PyThreadState* state)
{
    PyEval_RestoreThread(state); // 主线程获取GIL
    Py_FinalizeEx(); // 安全退出
}

void sig_handler(int signum)
{
    g_shutdown_requested = true;
}

int main()
{
    PyThreadState* state = initialize_python();
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    try {
        std::thread shutdown_thread([] {
            while (!g_shutdown_requested.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            LOG_INFO("VerifyServer shutdown");
            auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(5);
            g_server->Shutdown(deadline);
        });
        std::string host = ConfigMgr::instance()->get_value("VerifyServer", "host");
        std::string port = ConfigMgr::instance()->get_value("VerifyServer", "port");
        std::string server_address = host + ":" + port;
        VerifyServerImpl verify_service;
        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&verify_service);
        g_server = builder.BuildAndStart();
        LOG_INFO("Server listening on {}", server_address);
        g_server->Wait();
        shutdown_thread.join();
    } catch (const std::exception& e) {
        LOG_WARN("{}", e.what());
        finalize_python(state);
        return 1;
    }
    finalize_python(state);
    return 0;
}