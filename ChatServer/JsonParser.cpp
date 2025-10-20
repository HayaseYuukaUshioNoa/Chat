//
// Created by tom on 25-10-13.
//

#include "JsonParser.h"

json JsonParser::get_json_field(const json &root, const std::string &field_name)
{
    auto iter = root.find(field_name);
    if (iter == root.end()) {
        return json();
    }
    return *iter;
}

void JsonParser::parse(std::string &str)
{
    json root = json::parse(str);
    if (!root.is_object()) {
        throw std::runtime_error("json is not object");
    }

    json uid_json = get_json_field(root, "uid");
    json token_json = get_json_field(root, "token");

    if (uid_json.is_number()) {
        uid_ = uid_json.get<std::uint16_t>();
    }
    if (token_json.is_string()) {
        token_ = token_json.get<std::string>();
    }
}

uint16_t JsonParser::uid() const
{
    return uid_;
}

std::string JsonParser::token() const
{
    return token_;
}

unsigned JsonParser::errcode() const
{
    return errcode_;
}

void JsonParser::set_uid(uint16_t uid)
{
    uid_ = uid;
}

void JsonParser::set_token(std::string &token)
{
    token_ = token;
}

json JsonParser::to_json() const
{
    json root;
    root["uid"] = uid_;
    if (!token_.empty()) {
        root["token"] = token_;
    }
    root["error"] = errcode_;
    return root;
}

void JsonParser::set_errcode(unsigned int errcode)
{
    errcode_ = errcode;
}
