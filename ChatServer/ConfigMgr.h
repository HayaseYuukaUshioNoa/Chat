//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_CONFIGMGR_H
#define CHATSERVER_CONFIGMGR_H

#include "Singleton.h"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class ConfigMgr : public Singleton<ConfigMgr> {
    friend class Singleton<ConfigMgr>;

private:
    json root;

    ConfigMgr();

public:
    ~ConfigMgr() = default;

    std::string get_value(const std::string &obj_name, const std::string &key);
};


#endif //CHATSERVER_CONFIGMGR_H
