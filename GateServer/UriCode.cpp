//
// Created by tom on 25-10-2.
//

#include "UriCode.h"
#include <cstdint>
#include <sstream>
#include <iomanip>

std::string encode_uri(const std::string &input)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (auto c: input) {
        if (std::isalnum(static_cast<uint8_t>(c)) || c == '-' || c == '_' ||
            c == '.' || c == '!' || c == '~' || c == '*' || c == '\'' || c == '(' ||
            c == ')' || c == ';' || c == '/' || c == '?' || c == ':' || c == '@' ||
            c == '&' || c == '=' || c == '+' || c == '$' || c == ',' || c == '#') {
            escaped << c;
        } else {
            // 字符被编码为 %XX 形式，其中 XX 是字符 ASCII 码的十六进制表示
            escaped << std::uppercase;
            escaped << '%' << std::setw(2)
                    << static_cast<int>(static_cast<unsigned char>(c));
            escaped << std::nouppercase;
        }
    }

    return escaped.str();
}

std::string decode_uri(const std::string &input)
{
    std::string decoded;
    std::istringstream iss(input);
    char c;

    while (iss.get(c)) {
        if (c == '%') {
            // 处理%XX形式的编码字符
            char hex1, hex2;
            if (!iss.get(hex1) || !iss.get(hex2)) {
                // 不完整的编码序列，直接添加%
                decoded += c;
                continue;
            }

            // 转换十六进制字符为数值
            int value;
            std::istringstream hex_ss(std::string(1, hex1) + std::string(1, hex2));
            if (hex_ss >> std::hex >> value) {
                decoded += static_cast<char>(value);
            } else {
                // 无效的十六进制值，添加所有字符
                decoded += c;
                decoded += hex1;
                decoded += hex2;
            }
        } else if (c == '+') {
            // 处理空格的特殊表示
            decoded += ' ';
        } else {
            // 普通字符直接添加
            decoded += c;
        }
    }

    return decoded;
}

std::vector<std::pair<std::string, std::string>> parse_query_pairs(const std::string &query)
{
    std::vector<std::pair<std::string, std::string>> pairs;
    if (query.empty()) {
        return pairs;
    }

    size_t start = 0;
    size_t end = query.find('&');

    while (end != std::string::npos) {
        // 处理每个键值对
        std::string pair_str = query.substr(start, end - start);
        size_t eq_pos = pair_str.find('=');

        std::string key, value;
        if (eq_pos != std::string::npos) {
            key = decode_uri(pair_str.substr(0, eq_pos));
            value = decode_uri(pair_str.substr(eq_pos + 1));
        } else {
            // 没有值的键，如"key"
            key = decode_uri(pair_str);
            value = "";
        }

        pairs.emplace_back(key, value);

        start = end + 1;
        end = query.find('&', start);
    }

    // 处理最后一个键值对
    std::string last_pair = query.substr(start);
    if (!last_pair.empty()) {
        size_t eq_pos = last_pair.find('=');
        std::string key, value;

        if (eq_pos != std::string::npos) {
            key = decode_uri(last_pair.substr(0, eq_pos));
            value = decode_uri(last_pair.substr(eq_pos + 1));
        } else {
            key = decode_uri(last_pair);
            value = "";
        }

        pairs.emplace_back(key, value);
    }

    return pairs;
}

std::unordered_map<std::string, std::string> parse_query(const std::string &query)
{
    std::unordered_map<std::string, std::string> result;
    auto pairs = parse_query_pairs(query);

    // 对于重复的键，后面的值会覆盖前面的值
    for (const auto &pair: pairs) {
        result[pair.first] = pair.second;
    }

    return result;
}

std::unordered_map<std::string, std::string> parse_uri_query(const std::string &uri)
{
    // 找到问号位置，提取查询字符串部分
    size_t query_start = uri.find('?');
    if (query_start == std::string::npos) {
        return {}; // 没有查询字符串
    }

    std::string query = uri.substr(query_start + 1);
    // 忽略可能存在的片段标识符（#后面的部分）
    size_t fragment_start = query.find('#');
    if (fragment_start != std::string::npos) {
        query = query.substr(0, fragment_start);
    }

    return parse_query(query);
}

// 从完整URI中提取路径部分
std::string extract_path(const std::string &uri)
{
    // 查找查询参数开始位置(?)和片段开始位置(#)
    size_t query_pos = uri.find('?');
    size_t fragment_pos = uri.find('#');

    // 路径结束位置取最早出现的分隔符
    size_t path_end = uri.size();
    if (query_pos != std::string::npos) {
        path_end = std::min(path_end, query_pos);
    }
    if (fragment_pos != std::string::npos) {
        path_end = std::min(path_end, fragment_pos);
    }

    // 查找路径开始位置（在协议之后）
    size_t path_start = uri.find("//");
    if (path_start != std::string::npos) {
        path_start = uri.find('/', path_start + 2);
        if (path_start == std::string::npos) {
            return ""; // 没有路径
        }
    } else {
        path_start = 0; // 没有协议部分，从开头开始
    }

    // 提取并解码路径
    std::string path = uri.substr(path_start, path_end - path_start);
    return decode_uri(path); // 使用之前实现的URI解码函数
}

// 分割路径为组件
std::vector<std::string> split_path(const std::string &path)
{
    std::vector<std::string> components;
    std::string current;

    for (char c: path) {
        if (c == '/') {
            if (!current.empty()) {
                components.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }

    // 添加最后一个组件（如果存在）
    if (!current.empty()) {
        components.push_back(current);
    }

    return components;
}

// 规范化路径
std::string normalize_path(const std::string &path)
{
    // 先分割路径
    std::vector<std::string> components = split_path(path);
    std::vector<std::string> normalized;

    for (const std::string &comp: components) {
        if (comp == ".") {
            // 当前目录，忽略
            continue;
        } else if (comp == "..") {
            // 上级目录，如果有可弹出的组件则弹出
            if (!normalized.empty()) {
                normalized.pop_back();
            }
        } else {
            // 普通组件，添加到结果
            normalized.push_back(comp);
        }
    }

    // 合并规范化后的组件
    return join_path(normalized);
}

// 合并路径组件
std::string join_path(const std::vector<std::string> &components)
{
    if (components.empty()) {
        return "/";
    }

    std::string result;
    for (const std::string &comp: components) {
        result += "/" + comp;
    }

    return result;
}
