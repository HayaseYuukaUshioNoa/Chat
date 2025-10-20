//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_MYSQLPOOL_H
#define CHATSERVER_MYSQLPOOL_H


#include "Singleton.h"
#include "MySqlConnection.h"
#include <list>
#include <mutex>
#include <condition_variable>

class MySqlPool : public Singleton<MySqlPool> {
    friend class Singleton<MySqlPool>;

private:
    std::list<std::shared_ptr<MySqlConnection>> sql_connections_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_ = false;

    MySqlPool();

public:
    ~MySqlPool();

    void close();

    std::shared_ptr<MySqlConnection> sql_connection();

    void recycle_sql_connection(std::shared_ptr<MySqlConnection> con);
};

#endif //CHATSERVER_MYSQLPOOL_H
