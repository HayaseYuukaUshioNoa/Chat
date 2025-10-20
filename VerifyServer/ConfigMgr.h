#pragma once

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