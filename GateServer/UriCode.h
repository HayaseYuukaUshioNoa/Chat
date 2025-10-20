//
// Created by tom on 25-10-2.
//

#ifndef GATESERVER_URICODE_H
#define GATESERVER_URICODE_H

#endif //GATESERVER_URICODE_H

#include <string>
#include <unordered_map>
#include <vector>

std::string encode_uri(const std::string& input);

std::string decode_uri(const std::string& input);

// 解析URI查询字符串，返回键值对映射
std::unordered_map<std::string, std::string> parse_query(const std::string& query);

// 解析URI查询字符串，返回所有键值对（包括重复键）
std::vector<std::pair<std::string, std::string>> parse_query_pairs(const std::string& query);

// 从完整URI中提取并解析查询字符串
std::unordered_map<std::string, std::string> parse_uri_query(const std::string& uri);

// 从完整URI中提取路径部分（去除查询参数和片段）
std::string extract_path(const std::string& uri);

// 分割路径为组件列表（如"/a/b/c"分割为["a", "b", "c"]）
std::vector<std::string> split_path(const std::string& path);

// 规范化路径（处理.和..）
// 例如"/a/./b/../c"规范化为"/a/c"
std::string normalize_path(const std::string& path);

// 合并路径组件为完整路径
std::string join_path(const std::vector<std::string>& components);