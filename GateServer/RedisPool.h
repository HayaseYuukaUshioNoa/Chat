//
// Created by tom on 25-10-8.
//

#ifndef GATESERVER_REDISPOOL_H
#define GATESERVER_REDISPOOL_H

#include "RedisMgr.h"
#include "Singleton.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

class RedisPool : public Singleton<RedisPool> {
    friend class Singleton<RedisPool>;
private:
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<std::shared_ptr<RedisMgr>> redis_mgrs_;
    bool stop_ = false;

    RedisPool();

public:
    ~RedisPool();

    std::shared_ptr<RedisMgr> redis_mgr();

    void recycle_redis_mgr(std::shared_ptr<RedisMgr> redis_mgr);

    void close();
};


#endif //GATESERVER_REDISPOOL_H
