#pragma once

#include <string>

std::string GenerateVerifycode();

bool SendMail(const std::string& recipient, const std::string& verifycode);