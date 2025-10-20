//
// Created by tom on 25-10-15.
//

#ifndef VERIFYSERVER_LOGGER_H
#define VERIFYSERVER_LOGGER_H

#include "Singleton.h"
#include <spdlog/spdlog.h>

class Logger : public Singleton<Logger> {
    friend class Singleton<Logger>;

private:
    std::shared_ptr<spdlog::logger> logger_ = nullptr;

    Logger();

public:
    ~Logger() = default;

    std::shared_ptr<spdlog::logger> logger() const;
};

#define LOG_TRACE(...)  Logger::instance()->logger()-> \
    log(spdlog::source_loc(__FILE__, __LINE__, __FUNCTION__), spdlog::level::level_enum::trace, __VA_ARGS__)
#define LOG_DEBUG(...)  Logger::instance()->logger()-> \
    log(spdlog::source_loc(__FILE__, __LINE__, __FUNCTION__), spdlog::level::level_enum::debug, __VA_ARGS__)
#define LOG_INFO(...)   Logger::instance()->logger()-> \
    log(spdlog::source_loc(__FILE__, __LINE__, __FUNCTION__), spdlog::level::level_enum::info, __VA_ARGS__)
#define LOG_WARN(...)   Logger::instance()->logger()-> \
    log(spdlog::source_loc(__FILE__, __LINE__, __FUNCTION__), spdlog::level::level_enum::warn, __VA_ARGS__)
#define LOG_ERROR(...)  Logger::instance()->logger()-> \
    log(spdlog::source_loc(__FILE__, __LINE__, __FUNCTION__), spdlog::level::level_enum::err, __VA_ARGS__)
#define LOG_CRITICAL(...) Logger::instance()->logger()-> \
    log(spdlog::source_loc(__FILE__, __LINE__, __FUNCTION__), spdlog::level::level_enum::critical, __VA_ARGS__)


#endif //VERIFYSERVER_LOGGER_H
