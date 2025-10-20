//
// Created by tom on 25-10-15.
//

#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <iostream>

Logger::Logger()
{
    try {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%P] [%t] [%s:%#] %v");

        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/status_server.log",
                                                                                1024 * 1024 * 5, 3);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%P] [%t] [%s:%#] %v");

        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
        logger_ = std::make_shared<spdlog::logger>("StatusLogger", sinks.begin(), sinks.end());

        spdlog::register_logger(logger_);
        logger_->set_level(spdlog::level::level_enum::debug);
        logger_->flush_on(spdlog::level::level_enum::info);

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

std::shared_ptr<spdlog::logger> Logger::logger() const
{
    return logger_;
}