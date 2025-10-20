//
// Created by tom on 25-10-9.
//

#ifndef GATESERVER_JSONPARSER_H
#define GATESERVER_JSONPARSER_H

#include <string>
#include <nlohmann/json.hpp>
#include "ErrorCode.h"

using json = nlohmann::json;

class JsonParser {
private:
    std::string username_;
    std::string email_;
    std::string password_;
    std::string confirm_;
    std::string verifycode_;
    unsigned errcode_ = ErrorCode::SUCCESS;

    json get_json_field(const json &root, const std::string &field_name);

public:
    JsonParser() = default;

    ~JsonParser() = default;

    void parse(std::string &str);

    std::string username() const;

    std::string email() const;

    std::string password() const;

    std::string confirm() const;

    std::string verifycode() const;

    unsigned errcode() const;

    void set_username(std::string &username);

    void set_email(std::string &email);

    void set_password(std::string &password);

    void set_confirm(std::string &confirm);

    void set_verifycode(std::string &verifycode);

    void set_errcode(unsigned errcode);

    json to_json() const;
};


#endif //GATESERVER_JSONPARSER_H
