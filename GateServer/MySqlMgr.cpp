//
// Created by tom on 25-10-9.
//

#include "MySqlMgr.h"
#include "ScopeExit.h"
#include "Logger.h"

bool MySqlMgr::exists(const std::string &table, const std::string &field, const std::string &value)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con](){
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    char sql[512] = {0};
    snprintf(sql, sizeof(sql), "SELECT 1 FROM %s WHERE %s = '%s' LIMIT 1", table.c_str(),
             field.c_str(), value.c_str());
    if (!con->query(sql)) {
        return false;
    }
    bool exist = con->num_rows() > 0;
    return exist;
}

bool MySqlMgr::register_user(const std::string &username, const std::string &email, const std::string &password)
{
    // 查询用户是否存在
    if (exists("users", "username", username)) {
        LOG_INFO("{} already exists", username);
        return false;
    }
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con](){
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    // 插入数据
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, email, password_hash) "
             "VALUES ('%s', '%s', '%s')",
             username.c_str(), email.c_str(), password.c_str());
    if (!con->insert(sql)) {
        return false;
    }
    return true;
}

bool MySqlMgr::reset_pwd(const std::string &username, const std::string &password)
{
    // 查询用户是否存在
    if (!exists("users", "username", username)) {
        LOG_WARN("{} doesn't exists", username);
        return false;
    }
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con](){
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    // 更新密码
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "UPDATE users SET password_hash = '%s' "
             "WHERE username = '%s'",
             password.c_str(), username.c_str());
    if (!con->insert(sql)) {
        return false;
    }
    return true;
}

bool MySqlMgr::login_user(const std::string &email, const std::string &password, UserInfo &user)
{
    auto con = MySqlPool::instance()->sql_connection();
    ScopeExit se([&con](){
        MySqlPool::instance()->recycle_sql_connection(con);
    });
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "SELECT * FROM users where email = '%s'",
             email.c_str());
    if (!con->query(sql)) {
        LOG_WARN("{} doesn't exists", email);
        return false;
    }
    // 获取一整行
    if (!con->row()) {
        return false;
    }
    // 检查密码是否匹配
    std::string pwd = con->field(3);
    if (pwd != password) {
        LOG_WARN("password don't match, src: {}, dest {}", password, pwd);
        return false;
    }
    std::string id = con->field(0);
    std::string username = con->field(1);

    user.uid = std::stoi(id);
    user.email = email;
    user.password = pwd;
    return true;
}
