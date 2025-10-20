//
// Created by tom on 25-10-2.
//

#ifndef GATESERVER_CSERVER_H
#define GATESERVER_CSERVER_H

#include "Common.h"
#include <memory>

class CServer : public std::enable_shared_from_this<CServer> {
private:
    ip::tcp::acceptor acceptor_;
public:
    ~CServer() = default;

    CServer(asio::io_context &io, unsigned port);

    void do_accept();
};


#endif //GATESERVER_CSERVER_H
