//
// Created by tom on 25-10-13.
//

#include "StatusServiceClient.h"
#include "ConfigMgr.h"
#include "ErrorCode.h"

StatusServiceClient::StatusServiceClient()
{
    std::string host = ConfigMgr::instance()->get_value("StatusServer", "host");
    std::string port = ConfigMgr::instance()->get_value("StatusServer", "port");
    std::string server_address = host + ":" + port;
    auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    stub_ = StatusService::NewStub(channel);
}

GetChatServerRsp StatusServiceClient::GetChatServer(int32_t uid)
{
    GetChatServerReq request;
    GetChatServerRsp response;
    ClientContext context;
    request.set_uid(uid);

    Status status = stub_->GetChatServer(&context, request, &response);
    if (status.ok()) {
        return response;
    } else {
        response.set_error(ErrorCode::RPC_ERROR);
        return response;
    }
}

LoginVerifyRsp StatusServiceClient::LoginVerify(uint32_t uid, const std::string &token)
{
    LoginVerifyReq request;
    LoginVerifyRsp response;
    ClientContext context;
    request.set_uid(uid);
    request.set_token(token);

    Status status = stub_->LoginVerify(&context, request, &response);
    if (status.ok()) {
        return response;
    } else {
        response.set_error(ErrorCode::RPC_ERROR);
        return response;
    }
}
