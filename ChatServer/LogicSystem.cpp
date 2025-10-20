//
// Created by tom on 25-10-13.
//

#include "LogicSystem.h"
#include "Session.h"
#include "JsonParser.h"
#include "MySqlMgr.h"
#include "StatusServiceClient.h"
#include "Logger.h"
#include "nlohmann/json.hpp"
#include "CServer.h"

using json = nlohmann::json;

void LogicSystem::init_handler()
{
    handlers_[MsgType::MSG_LOGIN] = [this](std::shared_ptr<Session> session) {
        try {
            JsonParser parser;
            std::string str = std::string(session->body().data(), session->body().size());
            parser.parse(str);
            uint16_t uid = parser.uid();
            LOG_INFO("Login message uid: {}", uid);
            // 验证uid
            std::string username;
            std::string email;
            if (!MySqlMgr::find_uid(uid, username, email)) {
                LOG_WARN("find uid error");
                json root;
                root["error"] = ErrorCode::USER_LOGIN_ERROR;
                std::string s = root.dump();
                session->send_response(MsgType::MSG_LOGIN, s);
                return;
            }
            // 验证token
            std::string token = parser.token();
            LOG_INFO("Login message token: {}", token);
            auto response = StatusServiceClient::instance()->LoginVerify(uid, token);
            json root;
            root["error"] = 0;
            root["uid"] = uid;
            // root["token"] = token;
            root["username"] = username;
            root["email"] = email;
            std::string s = root.dump();
            // token验证成功
            if (response.error() == ErrorCode::SUCCESS) {
                session->set_uid(uid);
                auto service = session->server().lock();
                if (service) {
                    service->insert_session(uid, session);
                }
            }
            session->send_response(MsgType::MSG_LOGIN, s);
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_LOGIN, s);
        }
    };
    handlers_[MsgType::MSG_FIND] = [this](std::shared_ptr<Session> session) {
        try {
            std::string str = std::string(session->body().data(), session->body().size());
            json src = json::parse(str);
            std::string username = src.at("username");
            LOG_INFO("Find message username: {}", username);

            // TODO: Redis中查找username

            // 数据库中查找username
            std::string email;
            if (!MySqlMgr::find_username(username, email)) {
                LOG_WARN("find username failed");
                json err;
                err["error"] = ErrorCode::FIND_USER_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_FIND, s);
                return;
            }
            // TODO: 保存用户信息到Redis中

            json root;
            root["error"] = ErrorCode::SUCCESS;
            root["username"] = username;
            root["email"] = email;
            std::string s = root.dump();
            session->send_response(MsgType::MSG_FIND, s);
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_FIND, s);
        }
    };
    handlers_[MsgType::MSG_FRIEND_REQ] = [this](std::shared_ptr<Session> session) {
        try {
            std::string str = std::string(session->body().data(), session->body().size());
            json src = json::parse(str);
            uint16_t from_uid = src.at("from_uid");
            std::string to_username = src.at("to_username");
            std::string to_email = src.at("to_email");
            LOG_INFO("from_uid: {}, to_username: {}", from_uid, to_username);

            // 查询from_uid的用户名和邮箱
            std::string from_username;
            std::string from_email;
            if (!MySqlMgr::find_uid(from_uid, from_username, from_email)) {
                LOG_WARN("find uid failed");
                json err;
                err["error"] = ErrorCode::INSERT_FRIEND_REQUEST_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_FRIEND_REQ, s);
                return;
            }

            // 添加好友申请请求到数据库中
            uint16_t to_uid = 0;
            if (!MySqlMgr::insert_friend_req(from_uid, to_username, to_uid)) {
                LOG_WARN("insert friend request failed");
                json err;
                err["error"] = ErrorCode::INSERT_FRIEND_REQUEST_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_FRIEND_REQ, s);
                return;
            }

            json root;
            root["error"] = ErrorCode::SUCCESS;
            std::string s = root.dump();
            session->send_response(MsgType::MSG_FRIEND_REQ, s);
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_FRIEND_REQ, s);
        }
    };
    handlers_[MsgType::MSG_SHOW_FRIEND_REQ] = [this](std::shared_ptr<Session> session) {
        try {
            std::string str = std::string(session->body().data(), session->body().size());
            json src = json::parse(str);
            uint16_t uid = session->uid_;

            // 查询数据库好友申请表
            std::vector<std::pair<uint16_t, uint16_t>> fuid_status;
            if (!MySqlMgr::search_friend_req(uid, fuid_status)) {
                LOG_WARN("search friend request failed");
                json err;
                err["error"] = ErrorCode::SEARCH_FRIEND_REQUEST_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SHOW_FRIEND_REQ, s);
                return;
            }

            // 查询用户表获取用户信息
            std::vector<std::tuple<std::string, std::string, uint16_t>> user_infos;
            if (!MySqlMgr::search_users_infos(fuid_status, user_infos)) {
                LOG_WARN("search users infos failed");
                json err;
                err["error"] = ErrorCode::SEARCH_FRIEND_REQUEST_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SHOW_FRIEND_REQ, s);
                return;
            }

            json root;
            root["error"] = ErrorCode::SUCCESS;
            json array;
            for (auto& [username, email, status] : user_infos) {
                json user_info;
                user_info["username"] = username;
                user_info["email"] = email;
                user_info["status"] = status;
                array.push_back(user_info);
            }
            root["user_infos"] = array;
            std::string s = root.dump();
            session->send_response(MsgType::MSG_SHOW_FRIEND_REQ, s);
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_SHOW_FRIEND_REQ, s);
        }
    };
    handlers_[MsgType::MSG_FRIEND_RES] = [this](std::shared_ptr<Session> session) {
        try {
            std::string str(session->body_.data(), session->body_.size());
            json src = json::parse(str);
            std::string from_username = src.at("username");
            LOG_INFO("from_username: {}", from_username);

            // 获取uid
            uint16_t from_uid = 0;
            if (!MySqlMgr::find_username(from_username, from_uid)) {
                LOG_WARN("find username failed");
                json err;
                err["error"] = ErrorCode::SEARCH_FRIEND_RESPONSE_ERROR;
                std::string s = err.dump();
                session->write_buffer_ = prepare_msg(session->uid_, MsgType::MSG_FRIEND_RES, s.length(), s);
                session->do_write();
                return;
            }

            // 设置friend_req状态
            if (!MySqlMgr::set_friend_req_status(from_uid, session->uid_)) {
                LOG_WARN("set friend request failed");
                json err;
                err["error"] = ErrorCode::SEARCH_FRIEND_RESPONSE_ERROR;
                std::string s = err.dump();
                session->write_buffer_ = prepare_msg(session->uid_, MsgType::MSG_FRIEND_RES, s.length(), s);
                session->do_write();
                return;
            }

            // 更新friend表
            if (!MySqlMgr::update_friend(from_uid, session->uid_)) {
                LOG_WARN("update friend failed");
                json err;
                err["error"] = ErrorCode::SEARCH_FRIEND_RESPONSE_ERROR;
                std::string s = err.dump();
                session->write_buffer_ = prepare_msg(session->uid_, MsgType::MSG_FRIEND_RES, s.length(), s);
                session->do_write();
                return;
            }
            json root;
            root["error"] = ErrorCode::SUCCESS;
            std::string s = root.dump();
            session->write_buffer_ = prepare_msg(session->uid_, MsgType::MSG_FRIEND_RES, s.length(), s);
            session->do_write();
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->write_buffer_ = prepare_msg(session->uid_, MsgType::MSG_FRIEND_RES, s.length(), s);
            session->do_write();
        }
    };
    handlers_[MsgType::MSG_SHOW_CONTACT] = [this](std::shared_ptr<Session> session) {
        try {
            std::string str = std::string(session->body().data(), session->body().size());
            json src = json::parse(str);
            uint16_t self_uid = src.at("uid");
            LOG_INFO("self_uid: {}", self_uid);

            // 查询friend表获取friend_uid
            std::vector<uint16_t> friends_uid;
            if (!MySqlMgr::search_friends(self_uid, friends_uid)) {
                LOG_WARN("search friends failed");
                json err;
                err["error"] = ErrorCode::SEARCH_FRIENDS_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SHOW_CONTACT, s);
                return;
            }

            // 查询friends_uid的用户信息
            std::vector<std::tuple<std::string, std::string, uint16_t>> user_infos;
            if (!MySqlMgr::search_friends_infos(friends_uid, user_infos)) {
                LOG_WARN("search friends infos failed");
                json err;
                err["error"] = ErrorCode::SEARCH_FRIENDS_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SHOW_CONTACT, s);
                return;
            }
            json root;
            root["error"] = ErrorCode::SUCCESS;
            json array;
            for (auto& [username, email, friend_id] : user_infos) {
                json user_info;
                user_info["username"] = username;
                user_info["email"] = email;
                user_info["friend_id"] = friend_id;
                array.push_back(user_info);
            }
            root["user_infos"] = array;
            std::string s = root.dump();
            session->send_response(MsgType::MSG_SHOW_CONTACT, s);
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_SHOW_CONTACT, s);
        }
    };
    handlers_[MsgType::MSG_SHOW_MESSAGES] = [this](std::shared_ptr<Session> session) {
        try {
            std::string str(session->body().data(), session->body().size());
            json src = json::parse(str);
            uint16_t sender_uid = src.at("sender_uid");
            std::string receiver_name = src.at("receiver_name");
            std::string receiver_email = src.at("receiver_email");
            LOG_INFO("sender_uid:{}, receiver_name:{}, receiver_email:{}", sender_uid, receiver_name, receiver_email);
            // 根据receiver_name查找receiver_uid
            uint16_t receiver_uid = 0;
            if (!MySqlMgr::find_username(receiver_name, receiver_uid)) {
                LOG_WARN("search receiver uid failed");
                json err;
                err["error"] = ErrorCode::SEARCH_MESSAGES_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SHOW_MESSAGES, s);
                return;
            }
            // 根据sender_uid查找sender_name
            std::string sender_name, sender_email;
            if (!MySqlMgr::find_uid(sender_uid, sender_name, sender_email)) {
                LOG_WARN("search sender username failed");
                json err;
                err["error"] = ErrorCode::SEARCH_MESSAGES_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SHOW_MESSAGES, s);
                return;
            }
            // 查询消息列表
            std::vector<std::tuple<uint16_t, uint16_t, std::string>> messages;
            if (!MySqlMgr::search_chat_messages(sender_uid, receiver_uid, messages)) {
                LOG_WARN("search chat message failed");
                json err;
                err["error"] = ErrorCode::SEARCH_MESSAGES_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SHOW_MESSAGES, s);
                return;
            }
            json root;
            root["error"] = ErrorCode::SUCCESS;
            json array;
            for (auto& [sender_id, receiver_id, content] : messages) {
                json msg;
                msg["sender_id"] = sender_id;
                msg["receiver_id"] = receiver_id;
                msg["content"] = content;
                msg["sender_name"] = sender_id == sender_uid ? sender_name : receiver_name;
                msg["receiver_name"] = receiver_id == receiver_uid ? receiver_name : sender_name;
                array.push_back(msg);
            }
            root["messages"] = array;
            std::string s = root.dump();
            session->send_response(MsgType::MSG_SHOW_MESSAGES, s);
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_SHOW_MESSAGES, s);
        }
    };
    handlers_[MsgType::MSG_SEND_MESSAGE] = [this](std::shared_ptr<Session> session) {
        try {
            std::string str(session->body().data(), session->body().size());
            json src = json::parse(str);
            uint16_t sender_uid = src.at("sender_id");
            std::string receiver_name = src.at("receiver_name");
            std::string content = src.at("content");

            if (sender_uid != session->uid()) {
                LOG_WARN("Sender UID mismatch: req={}, session={}", sender_uid, session->uid());
                json err;
                err["error"] = ErrorCode::MSG_SEND_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SEND_MESSAGE, s);
                return;
            }

            // 查询数据库获取sender_name;
            std::string sender_name, sender_email;
            if (!MySqlMgr::find_uid(sender_uid, sender_name, sender_email)) {
                LOG_WARN("sender does not exist");
                json err;
                err["error"] = ErrorCode::MSG_SEND_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SEND_MESSAGE, s);
                return;
            }
            // 查询数据库获取receiver_id
            uint16_t receiver_uid = 0;
            if (!MySqlMgr::find_username(receiver_name, receiver_uid)) {
                LOG_WARN("receiver does not exist");
                json err;
                err["error"] = ErrorCode::MSG_SEND_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SEND_MESSAGE, s);
                return;
            }
            // 插入数据到chat_messages表中
            if (!MySqlMgr::insert_chat_messages(sender_uid, receiver_uid, content)) {
                LOG_WARN("insert chat message error");
                json err;
                err["error"] = ErrorCode::MSG_SEND_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SEND_MESSAGE, s);
                return;
            }

            auto server = session->server().lock();
            if (!server) {
                LOG_WARN("CServer instance not available");
                json err;
                err["error"] = ErrorCode::MSG_SEND_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SEND_MESSAGE, s);
                return;
            }
            auto to_session = server->find_session(receiver_uid);
            if (!to_session) {
                LOG_INFO("Receiver uid {} offline, skip forward", receiver_uid);
                json err;
                err["error"] = ErrorCode::MSG_SEND_ERROR;
                std::string s = err.dump();
                session->send_response(MsgType::MSG_SEND_MESSAGE, s);
                return;
            }

            json forward_msg;
            forward_msg["error"] = static_cast<int>(ErrorCode::SUCCESS);
            forward_msg["sender_name"] = sender_name;
            forward_msg["sender_id"] = sender_uid;
            forward_msg["content"] = content;
            std::string msg_str = forward_msg.dump();

            to_session->send_response(MsgType::MSG_RECV_MESSAGE, msg_str);
            LOG_INFO("Forward msg to receiver uid {} (from {})", receiver_uid, sender_uid);

            json err;
            err["error"] = ErrorCode::MSG_SEND_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_SEND_MESSAGE, s);
        } catch (const std::exception& e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            std::string s = err.dump();
            session->send_response(MsgType::MSG_SEND_MESSAGE, s);
        }
    };
}

LogicSystem::LogicSystem()
{
    init_handler();
}

std::vector<char> LogicSystem::prepare_msg(uint16_t uid, uint16_t type, uint16_t len, const std::string& data)
{
    if (len != data.size()) {
        LOG_ERROR("prepare_msg: len mismatch! len={}, data.size()={}", len, data.size());
        throw std::invalid_argument("len and data size mismatch");
    }

    const size_t MAX_MSG_LEN = 1024 * 1024;
    if (len == 0 || len > MAX_MSG_LEN) {
        LOG_ERROR("prepare_msg: invalid len={} (must be 1~{})", len, MAX_MSG_LEN);
        throw std::invalid_argument("invalid message length");
    }

    LOG_INFO("(uid:{}, type:{}, len:{})", uid, type, len);
    LOG_INFO("(data:{})", data);
    uint16_t uid_net = socket_ops::host_to_network_short(uid);
    uint16_t type_net = socket_ops::host_to_network_short(type);
    uint16_t len_net = socket_ops::host_to_network_short(len);

    std::vector<char> buffer;
    buffer.reserve(sizeof(uid_net) + sizeof(type_net) + sizeof(len_net) + len);
    buffer.insert(buffer.end(), reinterpret_cast<char*>(&uid_net),
        reinterpret_cast<char*>(&uid_net) + sizeof(uid_net));
    buffer.insert(buffer.end(), reinterpret_cast<char*>(&type_net),
        reinterpret_cast<char*>(&type_net) + sizeof(type_net));
    buffer.insert(buffer.end(), reinterpret_cast<char*>(&len_net),
        reinterpret_cast<char*>(&len_net) + sizeof(len_net));
    buffer.insert(buffer.end(), data.begin(), data.end());

    LOG_INFO("message len: {}", buffer.size());
    return buffer;
}

bool LogicSystem::handle_message(uint16_t msg_type, std::shared_ptr<Session> session)
{
    try {
        auto msg_type_enum = static_cast<MsgType>(msg_type);
        // 1. 校验消息类型合法性
        if (!is_valid_msg_type(msg_type_enum)) {
            LOG_ERROR("handle_message: invalid msg_type={}", msg_type);
            return false;
        }

        // 2. 查找处理函数
        auto iter = handlers_.find(msg_type_enum);
        if (iter == handlers_.end()) {
            LOG_WARN("handle_message: no handler for msg_type={}", msg_type);
            return false;
        }

        // 3. 执行业务逻辑
        iter->second(session);
        return true;
    } catch (const std::exception& e) {
        LOG_ERROR("handle_message exception: {} (msg_type={}, uid={})",
            e.what(), msg_type, session->uid());
        json err;
        err["error"] = ErrorCode::ERROR;
        std::string err_str = err.dump();
        auto err_buffer = prepare_msg(session->uid(), msg_type, err_str.size(), err_str);
        session->send_response(msg_type, err_str);
        return false;
    }
}

bool LogicSystem::is_valid_msg_type(MsgType type)
{
    switch (type) {
        case MsgType::MSG_LOGIN:
        case MsgType::MSG_FIND:
        case MsgType::MSG_FRIEND_REQ:
        case MsgType::MSG_FRIEND_RES:
        case MsgType::MSG_SHOW_FRIEND_REQ:
        case MsgType::MSG_SHOW_CONTACT:
        case MsgType::MSG_SHOW_MESSAGES:
        case MsgType::MSG_SEND_MESSAGE:
        case MsgType::MSG_RECV_MESSAGE:
            return true;
        default:
            return false;
    }
}

