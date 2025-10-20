//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_LOGICSYSTEM_H
#define CHATSERVER_LOGICSYSTEM_H

#include "Singleton.h"
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>
#include "ErrorCode.h"

class Session;

class LogicSystem : public Singleton<LogicSystem> {
    friend class Singleton<LogicSystem>;

private:
    std::unordered_map<MsgType , std::function<void(std::shared_ptr<Session>)>> handlers_;

    LogicSystem();

    void init_handler();

    bool is_valid_msg_type(MsgType type);

public:
    ~LogicSystem() = default;

    bool handle_message(uint16_t msg_type, std::shared_ptr<Session> session);
    std::vector<char> prepare_msg(uint16_t uid, uint16_t type, uint16_t len, const std::string &data);
};


#endif //CHATSERVER_LOGICSYSTEM_H
