//
// Created by tom on 25-10-8.
//

#include "RedisPool.h"
#include "ConfigMgr.h"

RedisPool::RedisPool()
{
    std::string pool_size = ConfigMgr::instance()->get_value("Redis", "pool_size");
    std::string host = ConfigMgr::instance()->get_value("Redis", "host");
    std::string port = ConfigMgr::instance()->get_value("Redis", "port");

    int pool_size_num = std::stoi(pool_size);
    int port_num = std::stoi(port);
    for (int i = 0; i < pool_size_num; ++i) {
        auto redis_mgr = std::make_shared<RedisMgr>();
        if (redis_mgr->connect(host, port_num)) {
            redis_mgrs_.push(redis_mgr);
        }
    }
}

void RedisPool::close()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    cv_.notify_all();
    while (!redis_mgrs_.empty()) {
        redis_mgrs_.pop();
    }
}

RedisPool::~RedisPool()
{
    close();
}

std::shared_ptr<RedisMgr> RedisPool::redis_mgr()
{
    std::shared_ptr<RedisMgr> res;
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() {
        return stop_ || !redis_mgrs_.empty();
    });
    // 连接池已关闭返回空指针
    if (stop_) {
        return res;
    }
    res = redis_mgrs_.front();
    redis_mgrs_.pop();
    return res;
}

void RedisPool::recycle_redis_mgr(std::shared_ptr<RedisMgr> redis_mgr)
{
    std::lock_guard<std::mutex> lock(mutex_);
    // 连接池已关闭，不再回收连接
    if (stop_) {
        return;
    }
    redis_mgrs_.push(redis_mgr);
    cv_.notify_one();
}
