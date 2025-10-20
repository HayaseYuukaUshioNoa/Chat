//
// Created by tom on 25-10-2.
//

#ifndef GATESERVER_COMMON_H
#define GATESERVER_COMMON_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace ip = boost::asio::ip;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

#endif //GATESERVER_COMMON_H
