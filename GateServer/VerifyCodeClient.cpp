//
// Created by tom on 25-10-2.
//

#include "VerifyCodeClient.h"
#include "ConfigMgr.h"
#include "ErrorCode.h"

VerifyCodeClient::VerifyCodeClient()
{
    std::string host = ConfigMgr::instance()->get_value("VerifyCodeServer", "host");
    std::string port = ConfigMgr::instance()->get_value("VerifyCodeServer", "port");
    std::string server_address = host + ":" + port;
    std::shared_ptr<Channel> channel = grpc::CreateChannel(
            server_address,
            grpc::InsecureChannelCredentials());
    stub_ = VerifyService::NewStub(channel);
}

GetVerifyRsp VerifyCodeClient::GetVerifyCode(const std::string &email)
{
    ClientContext context;
    GetVerifyReq request;
    GetVerifyRsp response;
    request.set_email(email);

    Status status = stub_->GetVerifyCode(&context, request, &response);
    if(status.ok()){
        return response;
    }else{
        response.set_error(ErrorCode::RPC_ERROR);
        return response;
    }
}