//
// Created by tom on 25-10-9.
//

#ifndef GATESERVER_MYSQLMGR_H
#define GATESERVER_MYSQLMGR_H

#include "MySqlPool.h"
#include "Utility.h"

class MySqlMgr {
public:
    static bool exists(const std::string &table, const std::string &field, const std::string &value);

    static bool register_user(const std::string &username, const std::string &email, const std::string &password);

    static bool reset_pwd(const std::string &username, const std::string &password);

    static bool login_user(const std::string &email, const std::string &password, UserInfo &user);
};


#endif //GATESERVER_MYSQLMGR_H
