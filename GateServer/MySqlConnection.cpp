//
// Created by tom on 25-10-9.
//

#include "MySqlConnection.h"
#include "Logger.h"

void MySqlConnection::free_res()
{
    if (m_result != nullptr) {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}

MySqlConnection::MySqlConnection()
{
    m_con = mysql_init(nullptr);
    if (m_con == nullptr) {
        LOG_WARN("mysql_init error: {}", mysql_error(m_con));
        return;
    }
    //设置数据库字符集
    mysql_set_character_set(m_con, "utf8mb4");
}

MySqlConnection::~MySqlConnection()
{
    if (m_con == nullptr) {
        return;
    }
    free_res();
    mysql_close(m_con);
}

bool MySqlConnection::connect(const char *hostname, const char *username, const char *passwd, const char *dbname,
                              const unsigned short port)
{
    m_con = mysql_real_connect(m_con, hostname, username, passwd, dbname, port, nullptr, 0);

    if (m_con == nullptr) {
        LOG_WARN("mysql_real_connect error: {}", mysql_error(m_con));
        return false;
    }
    return true;
}

bool MySqlConnection::connect(const std::string hostname, const std::string username, const std::string passwd,
                              const std::string dbname, const unsigned short port)
{
    const char *hname = hostname.c_str();
    const char *uname = username.c_str();
    const char *pwd = passwd.c_str();
    const char *databasename = dbname.c_str();
    return connect(hname, uname, pwd, databasename, port);
}

bool MySqlConnection::update(const char *sql)
{
    int ret = mysql_query(m_con, sql);
    if (ret != 0) {
        LOG_WARN("mysql_query error: {}", mysql_error(m_con));
        return false;
    }
    return true;
}

bool MySqlConnection::update(const std::string sql)
{
    const char *sqlstr = sql.c_str();
    return update(sqlstr);
}

bool MySqlConnection::query(const char *sql)
{
    //释放上一次查询的结果集
    free_res();
    int ret = mysql_query(m_con, sql);
    if (ret != 0) {
        LOG_WARN("mysql_query error: {}", mysql_error(m_con));
        return false;
    }
    //保存结果集
    m_result = mysql_store_result(m_con);
    if (m_result == nullptr) {
        LOG_WARN("mysql_store_result error: {}", mysql_error(m_con));
        return false;
    }
    return true;
}

bool MySqlConnection::query(const std::string sql)
{
    const char *sqlstr = sql.c_str();
    return query(sqlstr);
}

bool MySqlConnection::row()
{
    if (m_result == nullptr) {
        return false;
    }
    m_row = mysql_fetch_row(m_result);
    if (m_row == nullptr) {
        LOG_WARN("mysql_fetch_row error: {}", mysql_error(m_con));
        return false;
    }
    return true;
}

std::string MySqlConnection::field(unsigned int index)
{
    unsigned fields_num = mysql_num_fields(m_result);
    if (index >= fields_num) {
        return "";
    }
    const char *val = m_row[index];
    //获取字段长度
    unsigned long len = mysql_fetch_lengths(m_result)[index];
    return std::string(val, len);
}

bool MySqlConnection::set_transaction(bool mode)
{
    return mysql_autocommit(m_con, mode);
}

bool MySqlConnection::commit()
{
    return mysql_commit(m_con);
}

bool MySqlConnection::rollback()
{
    return mysql_rollback(m_con);
}

unsigned MySqlConnection::num_fields()
{
    return mysql_num_fields(m_result);
}

bool MySqlConnection::insert(const char *sql)
{
    int ret = mysql_query(m_con, sql);
    if (ret != 0) {
        LOG_WARN("mysql_query error: {}", mysql_error(m_con));
        return false;
    }
    return true;
}

bool MySqlConnection::insert(const std::string sql)
{
    return insert(sql.c_str());
}

unsigned MySqlConnection::num_rows()
{
    return mysql_num_rows(m_result);
}
