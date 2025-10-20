//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_MYSQLMGR_H
#define CHATSERVER_MYSQLMGR_H

#include "MySqlPool.h"
#include <vector>
#include <tuple>

class MySqlMgr {
public:
    static bool exists(const std::string &table, const std::string &field, const std::string &value);

    static bool verify_uid(uint16_t uid);

    static bool find_username(const std::string &username, std::string &email);

    static bool find_username(const std::string &username, uint16_t &uid);

    static bool find_uid(uint16_t uid, std::string &username, std::string &email);

    static bool insert_friend_req(uint16_t from_uid, const std::string &to_username, uint16_t &to_uid);

    static bool search_friend_req(uint16_t to_uid, std::vector<std::pair<uint16_t, uint16_t>> &fuid_status);

    static bool search_users_infos(const std::vector<std::pair<uint16_t, uint16_t>> &fuid_status,
                                   std::vector<std::tuple<std::string, std::string, uint16_t>> &user_infos);

    static bool set_friend_req_status(uint16_t from_uid, uint16_t to_uid);

    static bool update_friend(uint16_t from_uid, uint16_t to_uid);

    static bool search_friends(uint16_t self_uid, std::vector<uint16_t>& friends_uid);

    static bool search_friends_infos(const std::vector<uint16_t>& friends_uid,
                                     std::vector<std::tuple<std::string, std::string, uint16_t>> &user_infos);

    static bool search_chat_messages(uint16_t sender_id, uint16_t receiver_id,
                                     std::vector<std::tuple<uint16_t, uint16_t, std::string>> &messages);

    static bool insert_chat_messages(uint16_t sender_id, uint16_t receiver_id, const std::string &content);
};


#endif //CHATSERVER_MYSQLMGR_H
