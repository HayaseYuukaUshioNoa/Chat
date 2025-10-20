//
// Created by tom on 25-10-13.
//

#include "MySqlPool.h"
#include "ConfigMgr.h"

void MySqlPool::close()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    cv_.notify_all();
    while (!sql_connections_.empty()) {
        sql_connections_.pop_back();
    }
}

MySqlPool::~MySqlPool()
{
    close();
}

MySqlPool::MySqlPool()
{
    std::string pool_size = ConfigMgr::instance()->get_value("MySql", "pool_size");
    std::string host = ConfigMgr::instance()->get_value("MySql", "host");
    std::string port = ConfigMgr::instance()->get_value("MySql", "port");
    std::string username = ConfigMgr::instance()->get_value("MySql", "username");
    std::string passwd = ConfigMgr::instance()->get_value("MySql", "password");
    std::string dbname = ConfigMgr::instance()->get_value("MySql", "dbname");

    int pool_size_num = std::stoi(pool_size);
    int port_num = std::stoi(port);
    for (int i = 0; i < pool_size_num; ++i) {
        auto con = std::make_shared<MySqlConnection>();
        if (con->connect(host, username, passwd, dbname, port_num)) {
            sql_connections_.push_back(con);
        }
    }
}

std::shared_ptr<MySqlConnection> MySqlPool::sql_connection()
{
    std::shared_ptr<MySqlConnection> res;
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() {
        return stop_ || !sql_connections_.empty();
    });
    if (stop_) {
        return res;
    }
    res = sql_connections_.front();
    sql_connections_.pop_front();
    return res;
}

void MySqlPool::recycle_sql_connection(std::shared_ptr<MySqlConnection> con)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (stop_) {
        return;
    }
    sql_connections_.push_back(con);
    cv_.notify_one();
}