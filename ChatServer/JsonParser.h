//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_JSONPARSER_H
#define CHATSERVER_JSONPARSER_H

#include <nlohmann/json.hpp>
#include "ErrorCode.h"

using json = nlohmann::json;

class JsonParser {
private:
    uint16_t uid_;
    std::string token_;
    std::string username;
    unsigned errcode_ = ErrorCode::SUCCESS;

    json get_json_field(const json &root, const std::string &field_name);

public:
    JsonParser() = default;

    ~JsonParser() = default;

    void parse(std::string &str);

    uint16_t uid() const;

    std::string token() const;

    unsigned errcode() const;

    void set_uid(uint16_t uid);

    void set_token(std::string &token);

    void set_errcode(unsigned errcode);

    json to_json() const;
};


#endif //CHATSERVER_JSONPARSER_H
