//
// Created by tom on 25-10-9.
//

#ifndef GATESERVER_MYSQLCONNECTION_H
#define GATESERVER_MYSQLCONNECTION_H

#include <mysql/mysql.h>
#include <string>

class MySqlConnection {
private:
    MYSQL *m_con = nullptr;
    MYSQL_RES *m_result = nullptr;
    MYSQL_ROW m_row = nullptr;

    //释放结果集
    void free_res();

public:
    //1.初始化连接
    MySqlConnection();

    //2.销毁连接
    ~MySqlConnection();

    //3.连接数据库
    bool connect(const char *hostname, const char *username, const char *passwd,
                 const char *dbname, const unsigned short port);

    bool connect(const std::string hostname, const std::string username, const std::string passwd,
                 const std::string dbname, const unsigned short port);

    //4.更新数据库
    bool update(const char *sql);

    bool update(const std::string sql);

    //5.查询数据库
    bool query(const char *sql);

    bool query(const std::string sql);

    // 插入数据
    bool insert(const char *sql);

    bool insert(const std::string sql);

    //6.返回结果集中的一行数据
    bool row();

    //7.返回一行数据中指定的字段值
    std::string field(unsigned index);

    //8.设置事务
    bool set_transaction(bool mode);

    //9.提交事务
    bool commit();

    //10.事务回滚
    bool rollback();

    //11.返回结果集中字段的数量
    unsigned num_fields();

    // 返回结果集中行的数量
    unsigned num_rows();
};


#endif //GATESERVER_MYSQLCONNECTION_H
