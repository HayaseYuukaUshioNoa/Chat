//
// Created by tom on 25-10-10.
//

#include "StatusServerImpl.h"
#include "Common.h"
#include "ConfigMgr.h"
#include "Logger.h"
#include "ErrorCode.h"

Status
StatusServerImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* response)
{
    std::string token = generate_token();
    int32_t uid = request->uid();
    response->set_host(chat_server_.host);
    response->set_port(std::stoi(chat_server_.port));
    response->set_token(token);
    insert_uid_token(uid, token);
    response->set_error(ErrorCode::SUCCESS);
    return Status::OK;
}

Status StatusServerImpl::LoginVerify(ServerContext* context, const LoginVerifyReq* request, LoginVerifyRsp* response)
{
    int uid = request->uid();
    std::string token = request->token();
    std::lock_guard<std::mutex> lock(mutex_);
    if (!uid_token_.count(uid)) {
        response->set_error(ErrorCode::UID_INVALID);
    } else if (uid_token_[uid] != token) {
        response->set_error(ErrorCode::TOKEN_INVALID);
    } else {
        response->set_error(ErrorCode::SUCCESS);
    }
    return Status::OK;
}

StatusServerImpl::StatusServerImpl()
{
    chat_server_.host = ConfigMgr::instance()->get_value("ChatServer", "host");
    chat_server_.port = ConfigMgr::instance()->get_value("ChatServer", "port");
}

void StatusServerImpl::insert_uid_token(int32_t uid, const std::string& token)
{
    std::lock_guard<std::mutex> lock(mutex_);
    uid_token_[uid] = token;
}
