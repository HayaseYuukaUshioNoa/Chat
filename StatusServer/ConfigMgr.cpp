//
// Created by tom on 25-10-11.
//

#include "ConfigMgr.h"
#include <fstream>

ConfigMgr::ConfigMgr()
{
    std::ifstream is("config/config.json");
    root = json::parse(is);
}

std::string ConfigMgr::get_value(const std::string &obj_name, const std::string &key)
{
    std::string res = root.at(obj_name).at(key);
    return res;
}
