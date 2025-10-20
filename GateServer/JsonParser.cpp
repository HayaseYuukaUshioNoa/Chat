//
// Created by tom on 25-10-9.
//

#include "JsonParser.h"

void JsonParser::parse(std::string &str)
{
    json root = json::parse(str);
    if (!root.is_object()) {
        throw std::runtime_error("json is not object");
    }

    json user_json = get_json_field(root, "username");
    json email_json = get_json_field(root, "email");
    json pwd_json = get_json_field(root, "password");
    json confirm_json = get_json_field(root, "confirm");
    json verify_json = get_json_field(root, "verifycode");

    if (user_json.is_string()) {
        username_ = user_json.get<std::string>();
    }
    if (email_json.is_string()) {
        email_ = email_json.get<std::string>();
    }
    if (pwd_json.is_string()) {
        password_ = pwd_json.get<std::string>();
    }
    if (confirm_json.is_string()) {
        confirm_ = confirm_json.get<std::string>();
    }
    if (verify_json.is_string()) {
        verifycode_ = verify_json.get<std::string>();
    }
}

std::string JsonParser::username() const
{
    return username_;
}

std::string JsonParser::email() const
{
    return email_;
}

std::string JsonParser::password() const
{
    return password_;
}

std::string JsonParser::confirm() const
{
    return confirm_;
}

std::string JsonParser::verifycode() const
{
    return verifycode_;
}

unsigned JsonParser::errcode() const
{
    return errcode_;
}

void JsonParser::set_username(std::string &username)
{
    username_ = username;
}

void JsonParser::set_email(std::string &email)
{
    email_ = email;
}

void JsonParser::set_password(std::string &password)
{
    password_ = password;
}

void JsonParser::set_confirm(std::string &confirm)
{
    confirm_ = confirm;
}

void JsonParser::set_verifycode(std::string &verifycode)
{
    verifycode_ = verifycode;
}

void JsonParser::set_errcode(unsigned int errcode)
{
    errcode_ = errcode;
}

json JsonParser::to_json() const
{
    json root;
    if (!username_.empty()) {
        root["username"] = username_;
    }
    if (!email_.empty()) {
        root["email"] = email_;
    }
    if (!password_.empty()) {
        root["password"] = password_;
    }
    if (!confirm_.empty()) {
        root["confirm"] = confirm_;
    }
    if (!verifycode_.empty()) {
        root["verifycode"] = verifycode_;
    }
    root["error"] = errcode_;
    return root;
}

json JsonParser::get_json_field(const json &root, const std::string &field_name)
{
    auto iter = root.find(field_name);
    if (iter == root.end()) {
        return json();
    }
    return *iter;
}
