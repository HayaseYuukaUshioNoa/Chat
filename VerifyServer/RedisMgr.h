#pragma once

#include <hiredis/hiredis.h>
#include <string>

class RedisMgr {
private:
    redisContext *context_ = nullptr;
    redisReply *reply_ = nullptr;

public:
    RedisMgr() = default;

    ~RedisMgr();

    bool connect(const std::string &host, int port);

    bool get(const std::string &key, std::string &value);

    bool set(const std::string &key, const std::string &value);

    bool expire(const std::string &key, int seconds);

    bool auth(const std::string &password);

    bool left_push(const std::string &key, const std::string &value);

    bool left_pop(const std::string &key, std::string &value);

    bool right_push(const std::string &key, const std::string &value);

    bool right_pop(const std::string &key, std::string &value);

    bool hash_set(const std::string &hash_key, const std::string &field, const std::string &value);

    bool hash_set(const char *hash_key, const char *field, const char *value, size_t value_len);

    std::string hash_get(const std::string &hash_key, const std::string &field);

    bool del(const std::string &key);

    bool exists(const std::string &key);

    void close();
};