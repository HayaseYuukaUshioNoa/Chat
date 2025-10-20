#include "RedisMgr.h"
#include <cstring>
#include "Logger.h"

bool RedisMgr::connect(const std::string& host, int port)
{
    context_ = redisConnect(host.c_str(), port);
    if (context_ == nullptr || context_->err) {
        if (context_) {
            LOG_WARN("connection error: {}", context_->errstr);
        } else {
            LOG_WARN("memory allocate error");
        }
        return false;
    }
    return true;
}

bool RedisMgr::get(const std::string& key, std::string& value)
{
    reply_ = (redisReply*)redisCommand(context_, "GET %s", key.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type != REDIS_REPLY_STRING) {
        freeReplyObject(reply_);
        return false;
    }
    value = reply_->str;
    freeReplyObject(reply_);
    LOG_INFO("GET {} success", key);
    return true;
}

bool RedisMgr::set(const std::string& key, const std::string& value)
{
    reply_ = (redisReply*)redisCommand(context_, "SET %s %s", key.c_str(), value.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type == REDIS_REPLY_STATUS && strcasecmp(reply_->str, "OK") == 0) {
        LOG_INFO("SET {} {} success", key, value);
        freeReplyObject(reply_);
        return true;
    } else {
        freeReplyObject(reply_);
        return false;
    }
}

bool RedisMgr::expire(const std::string& key, int seconds)
{
    reply_ = (redisReply*)redisCommand(context_, "EXPIRE %s %d", key.c_str(), seconds);
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type == REDIS_REPLY_INTEGER && reply_->integer == 1) {
        LOG_INFO("EXPIRE {} {} success", key, seconds);
        freeReplyObject(reply_);
        return true;
    } else {
        freeReplyObject(reply_);
        return false;
    }
}

bool RedisMgr::auth(const std::string& password)
{
    reply_ = (redisReply*)redisCommand(context_, "AUTH %s", password.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type == REDIS_REPLY_STATUS && strcasecmp(reply_->str, "OK") == 0) {
        LOG_INFO("AUTH {} success", password);
        freeReplyObject(reply_);
        return true;
    } else {
        freeReplyObject(reply_);
        return false;
    }
}

bool RedisMgr::left_push(const std::string& key, const std::string& value)
{
    reply_ = (redisReply*)redisCommand(context_, "LPUSH %s %s", key.c_str(), value.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type == REDIS_REPLY_INTEGER && reply_->integer > 0) {
        LOG_INFO("LPUSH {} {} success", key, value);
        freeReplyObject(reply_);
        return true;
    } else {
        freeReplyObject(reply_);
        return false;
    }
}

bool RedisMgr::left_pop(const std::string& key, std::string& value)
{
    reply_ = (redisReply*)redisCommand(context_, "LPOP %s", key.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    // 键不存在
    if (reply_->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply_);
        return false;
    }
    value = reply_->str;
    freeReplyObject(reply_);
    LOG_INFO("LPOP {} success", key);
    return true;
}

bool RedisMgr::right_push(const std::string& key, const std::string& value)
{
    reply_ = (redisReply*)redisCommand(context_, "RPUSH %s %s", key.c_str(), value.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type == REDIS_REPLY_INTEGER && reply_->integer > 0) {
        LOG_INFO("RPUSH {} {} success", key, value);
        freeReplyObject(reply_);
        return true;
    } else {
        freeReplyObject(reply_);
        return false;
    }
}

bool RedisMgr::right_pop(const std::string& key, std::string& value)
{
    reply_ = (redisReply*)redisCommand(context_, "RPOP %s", key.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    // 键不存在
    if (reply_->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply_);
        return false;
    }
    value = reply_->str;
    freeReplyObject(reply_);
    LOG_INFO("RPOP {} success", key);
    return true;
}

bool RedisMgr::hash_set(const std::string& hash_key, const std::string& field, const std::string& value)
{
    reply_ = (redisReply*)redisCommand(context_, "HSET %s %s %s", hash_key.c_str(), field.c_str(), value.c_str());
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type == REDIS_REPLY_INTEGER && reply_->integer > 0) {
        LOG_INFO("HSET {} {} {} success", hash_key, field, value);
        freeReplyObject(reply_);
        return true;
    } else {
        freeReplyObject(reply_);
        return false;
    }
}

bool RedisMgr::hash_set(const char* hash_key, const char* field, const char* value, size_t value_len)
{
    const char* argv[4];
    size_t argv_len[4];
    argv[0] = "HSET";
    argv_len[0] = 4;
    argv[1] = hash_key;
    argv_len[1] = strlen(hash_key);
    argv[2] = field;
    argv_len[2] = strlen(field);
    argv[3] = value;
    argv_len[3] = value_len;
    reply_ = (redisReply*)redisCommandArgv(context_, 4, argv, argv_len);
    if (reply_ == nullptr) {
        return false;
    }
    if (reply_->type == REDIS_REPLY_INTEGER && reply_->integer > 0) {
        LOG_INFO("HSET {} {} {} success", hash_key, field, value);
        freeReplyObject(reply_);
        return true;
    } else {
        freeReplyObject(reply_);
        return false;
    }
}

std::string RedisMgr::hash_get(const std::string& hash_key, const std::string& field)
{
    const char* argv[3];
    size_t argv_len[3];
    argv[0] = "HGET";
    argv_len[0] = 4;
    argv[1] = hash_key.c_str();
    argv_len[1] = strlen(hash_key.c_str());
    argv[2] = field.c_str();
    argv_len[2] = strlen(field.c_str());
    reply_ = (redisReply*)redisCommandArgv(context_, 3, argv, argv_len);
    if (reply_ == nullptr || reply_->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply_);
        return "";
    }
    std::string value = reply_->str;
    freeReplyObject(reply_);
    LOG_INFO("HGET {} {} success", hash_key, field);
    return value;
}

bool RedisMgr::del(const std::string& key)
{
    reply_ = (redisReply*)redisCommand(context_, "DEL %s", key.c_str());
    if (reply_ == nullptr || reply_->type != REDIS_REPLY_INTEGER) {
        freeReplyObject(reply_);
        return false;
    }
    LOG_INFO("DEL {} success", key);
    freeReplyObject(reply_);
    return true;
}

bool RedisMgr::exists(const std::string& key)
{
    reply_ = (redisReply*)redisCommand(context_, "EXISTS %s", key.c_str());
    if (reply_ == nullptr || reply_->type != REDIS_REPLY_INTEGER || reply_->integer == 0) {
        freeReplyObject(reply_);
        return false;
    }
    LOG_INFO("EXISTS {} success", key);
    freeReplyObject(reply_);
    return true;
}

void RedisMgr::close()
{
    if (context_) {
        redisFree(context_);
    }
}

RedisMgr::~RedisMgr()
{
    close();
}
