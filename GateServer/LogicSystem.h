//
// Created by tom on 25-10-2.
//

#ifndef GATESERVER_LOGICSYSTEM_H
#define GATESERVER_LOGICSYSTEM_H

#include "Singleton.h"
#include <map>
#include <functional>

class HttpConnection;

class LogicSystem : public Singleton<LogicSystem> {
    friend class Singleton<LogicSystem>;

    using HttpHandler = std::function<void(std::shared_ptr<HttpConnection>)>;
private:
    std::map<std::string, HttpHandler> get_handlers_;
    std::map<std::string, HttpHandler> post_handlers_;

    LogicSystem();

public:
    ~LogicSystem() = default;

    void register_get(const std::string &url, HttpHandler handler);

    void register_post(const std::string &url, HttpHandler handler);

    bool handle_get(const std::string &url, std::shared_ptr<HttpConnection> connection);

    bool handle_post(const std::string &url, std::shared_ptr<HttpConnection> connection);
};


#endif //GATESERVER_LOGICSYSTEM_H
