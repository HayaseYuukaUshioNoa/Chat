//
// Created by tom on 25-10-10.
//

#ifndef STATUSSERVER_COMMON_H
#define STATUSSERVER_COMMON_H

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace uuids = boost::uuids;

static std::string generate_token()
{
    uuids::random_generator generator;
    uuids::uuid uuid = generator();
    return uuids::to_string(uuid);
}

#endif //STATUSSERVER_COMMON_H
