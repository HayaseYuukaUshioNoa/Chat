#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

enum ReqId {
    ID_GET_VERIFY_CODE = 1001, // 获取验证码
    ID_USER_REGISTER = 1002, // 用户注册
    ID_RESET_PASSWORD = 1003, // 重置密码
    ID_USER_LOGIN = 1004, // 用户登录
    ID_CHAT_LOGIN = 1005 // 用户登录聊天服务器
};

enum Module{
    MOD_REGISTER = 0, // 注册模块
    MOD_RESET = 1, // 重置密码模块
    MOD_LOGIN = 2 // 登录模块
};

enum ErrorCode{
    CODE_SUCCESS = 0,
    CODE_NETWORK_ERROR = 1, // 网络错误
    CODE_PARSE_JSON_ERROR = 1001 // json解析失败
};

enum MsgType{
    MSG_LOGIN = 0, // 登录消息
    MSG_FIND = 1, // 查找用户消息
    MSG_FRIEND_REQ = 2, // 添加好友请求
    MSG_FRIEND_RES = 3, // 添加好友响应
    MSG_SHOW_FRIEND_REQ = 4, // 显示好友请求
    MSG_SHOW_CONTACT = 5, // 显示联系人
    MSG_SHOW_MESSAGES = 6, // 显示消息
    MSG_SEND_MESSAGE = 7, // 发送消息
    MSG_RECV_MESSAGE = 8 // 接收消息
};

struct ServerInfo{
    int uid;
    QString username;
    QString email;
    QString host;
    int port;
    QString token;
};

extern ServerInfo g_server_info;

#endif // GLOBAL_H
