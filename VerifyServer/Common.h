#pragma once

#include <string>

enum ErrorCode {
    SUCCESS = 0,
    ERROR = 1001
};

struct UserInfo {
    int32_t uid;
    std::string email;
    std::string password;
};