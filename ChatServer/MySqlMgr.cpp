//
// Created by tom on 25-10-13.
//

#include "MySqlMgr.h"
#include "ScopeExit.h"
#include "Logger.h"

bool MySqlMgr::exists(const std::string &table, const std::string &field, const std::string &value)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "SELECT 1 FROM %s WHERE %s = %d LIMIT 1", table.c_str(),
             field.c_str(), std::stoi(value));
    if (!con->query(sql)) {
        return false;
    }
    bool exist = con->num_rows() > 0;
    return exist;
}

bool MySqlMgr::verify_uid(uint16_t uid)
{
    // 查询uid是否存在
    if (exists("users", "id", std::to_string(uid))) {
        LOG_INFO("verify uid: {} exist", uid);
        return true;
    }
    return false;
}

bool MySqlMgr::find_username(const std::string &username, std::string &email)
{
    // 查询username
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "select email from users where username = '%s'",
             username.c_str());
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    if (!con->query(sql)) {
        return false;
    }
    if (!con->row()) {
        return false;
    }
    email = con->field(0);
    if (email.empty()) {
        LOG_WARN("Find username: {}, email is null", username);
        return false;
    }
    LOG_INFO("Find username: {}, email: {}", username, email);
    return true;
}

bool MySqlMgr::insert_friend_req(uint16_t from_uid, const std::string &to_username, uint16_t &to_uid)
{
    // 获取to_uid
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "select id from users where username = '%s'",
             to_username.c_str());
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    if (!con->query(sql)) {
        return false;
    }
    if (!con->row()) {
        return false;
    }
    std::string id = con->field(0);
    if (id.empty()) {
        LOG_WARN("to_username: {} doesn't exist");
        return false;
    }
    LOG_INFO("to_username: {}, id is {}", to_username, id);
    to_uid = std::stoul(id);

    // 插入数据
    memset(sql, 0, sizeof(sql));
    snprintf(sql, sizeof(sql), "insert into friend_req (from_uid, to_uid) values (%d, %d)"
                               " on duplicate key update from_uid = from_uid, to_uid = to_uid", from_uid, to_uid);
    if (!con->insert(sql)) {
        return false;
    }
    LOG_INFO("insert friend request success, from_uid:{}->to_uid:{}", from_uid, to_uid);
    return true;
}

bool MySqlMgr::find_uid(uint16_t uid, std::string &username, std::string &email)
{
    // 查询username
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "select username, email from users where id = %d",
             uid);
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    if (!con->query(sql)) {
        return false;
    }
    if (!con->row()) {
        return false;
    }
    username = con->field(0);
    email = con->field(1);
    if (username.empty()) {
        LOG_WARN("Find uid: {}, username is null", username);
        return false;
    }
    if (email.empty()) {
        LOG_WARN("Find uid: {}, email is null", email);
        return false;
    }
    LOG_INFO("Find uid: {}, username: {}, email: {}", uid, username, email);
    return true;
}

bool MySqlMgr::search_friend_req(uint16_t to_uid, std::vector<std::pair<uint16_t, uint16_t>> &fuid_status)
{
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "select from_uid, status from friend_req"
                               " where to_uid = %d", to_uid);
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    if (!con->query(sql)) {
        return false;
    }
    while (con->row()) {
        std::string uid = con->field(0);
        std::string state = con->field(1);
        if (uid.empty() || state.empty()) {
            LOG_WARN("uid or state is null");
            return false;
        }
        uint16_t from_uid = std::stoul(uid);
        uint16_t status = std::stoul(state);
        fuid_status.emplace_back(from_uid, status);
    }
    return true;
}

bool MySqlMgr::search_users_infos(const std::vector<std::pair<uint16_t, uint16_t>> &fuid_status,
                                  std::vector<std::tuple<std::string, std::string, uint16_t>> &user_infos)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    for (auto &[from_uid, status]: fuid_status) {
        char sql[512] = {0};
        snprintf(sql, sizeof(sql), "select username, email from users where id = %d", from_uid);
        if (!con->query(sql)) {
            return false;
        }
        if (!con->row()) {
            return false;
        }
        std::string username = con->field(0);
        std::string email = con->field(1);
        if (username.empty() || email.empty()) {
            LOG_WARN("username or email is null");
            return false;
        }
        user_infos.emplace_back(username, email, status);
    }
    return true;
}

bool MySqlMgr::find_username(const std::string &username, uint16_t &uid)
{
    // 查询username
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "select id from users where username = '%s'",
             username.c_str());
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    if (!con->query(sql)) {
        return false;
    }
    if (!con->row()) {
        return false;
    }
    std::string id = con->field(0);
    if (id.empty()) {
        LOG_WARN("username: {} id is null", username);
    }
    uid = std::stoul(id);
    LOG_INFO("find username: {}, id: {}", username, id);
    return true;
}

bool MySqlMgr::set_friend_req_status(uint16_t from_uid, uint16_t to_uid)
{
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "update friend_req set status = 1 where from_uid = %d"
                               " and to_uid = %d",
             from_uid, to_uid);
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    if (!con->update(sql)) {
        return false;
    }
    LOG_INFO("set friend request status success");
    return true;
}

bool MySqlMgr::update_friend(uint16_t from_uid, uint16_t to_uid)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "insert ignore friend (self_uid, friend_uid) values (%d, %d)",
             from_uid, to_uid);
    if (!con->insert(sql)) {
        return false;
    }
    memset(sql, 0, sizeof(sql));
    snprintf(sql, sizeof(sql), "insert ignore friend (self_uid, friend_uid) values (%d, %d)",
             to_uid, from_uid);
    if (!con->insert(sql)) {
        return false;
    }
    LOG_INFO("update friend success");
    return true;
}

bool MySqlMgr::search_friends(uint16_t self_uid, std::vector<uint16_t> &friends_uid)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "select friend_uid from friend where self_uid = %u", self_uid);
    if (!con->query(sql)) {
        return false;
    }
    while (con->row()) {
        std::string uid = con->field(0);
        if (uid.empty()) {
            LOG_WARN("self_uid:{} -> friend_uid is null", self_uid);
            return false;
        }
        uint16_t friend_uid = std::stoul(uid);
        LOG_INFO("search self_uid:{} -> friend_uid:{}", self_uid, friend_uid);
        friends_uid.push_back(friend_uid);
    }
    LOG_INFO("search self_uid:{} friend success", self_uid);
    return true;
}

bool MySqlMgr::search_friends_infos(const std::vector<uint16_t> &friends_uid,
                                    std::vector<std::tuple<std::string, std::string, uint16_t>> &user_infos)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    for (auto friend_uid: friends_uid) {
        char sql[512] = {0};
        snprintf(sql, sizeof(sql), "select username, email from users where id = %d", friend_uid);
        if (!con->query(sql)) {
            return false;
        }
        if (!con->row()) {
            return false;
        }
        std::string username = con->field(0);
        std::string email = con->field(1);
        if (username.empty() || email.empty()) {
            LOG_WARN("username or email is null");
            return false;
        }
        user_infos.emplace_back(username, email, friend_uid);
    }
    return true;
}

bool MySqlMgr::search_chat_messages(uint16_t sender_id, uint16_t receiver_id,
                                    std::vector<std::tuple<uint16_t, uint16_t, std::string>> &messages)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "select sender_id, receiver_id, content from chat_messages"
                               " where (sender_id = %d and receiver_id = %d) OR (sender_id = %d and receiver_id = %d)"
                               " order by send_time desc limit 10",
             sender_id, receiver_id, receiver_id, sender_id);
    if (!con->query(sql)) {
        return false;
    }
    while (con->row()) {
        std::string sender = con->field(0);
        std::string receiver = con->field(1);
        std::string content = con->field(2);
        if (sender.empty() || receiver.empty() || content.empty()) {
            LOG_WARN("sender, receiver or content is null");
            return false;
        }
        uint16_t sender_uid = std::stoul(sender);
        uint16_t receiver_uid = std::stoul(receiver);
        messages.emplace_back(sender_uid, receiver_uid, content);
    }
    return true;
}

bool MySqlMgr::insert_chat_messages(uint16_t sender_id, uint16_t receiver_id, const std::string &content)
{
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "insert into chat_messages (sender_id, receiver_id, content)"
                               " values (%d, %d, '%s')", sender_id, receiver_id, content.c_str());

    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con]() {
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    if (!con->insert(sql)) {
        return false;
    }
    LOG_INFO("insert_chat_messages success");
    return true;
}
