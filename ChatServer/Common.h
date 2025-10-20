//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_COMMON_H
#define CHATSERVER_COMMON_H

#include <boost/asio.hpp>

namespace asio = boost::asio;
namespace ip = boost::asio::ip;
namespace socket_ops = boost::asio::detail::socket_ops;

using boost::system::error_code;
using tcp = boost::asio::ip::tcp;

#endif //CHATSERVER_COMMON_H
