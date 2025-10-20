//
// Created by tom on 25-10-13.
//

#ifndef CHATSERVER_STATUSSERVICECLIENT_H
#define CHATSERVER_STATUSSERVICECLIENT_H


#include "Message.grpc.pb.h"
#include "Singleton.h"
#include <grpcpp/grpcpp.h>
#include <memory>
#include <cstdint>

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::StatusService;
using message::LoginVerifyReq;
using message::LoginVerifyRsp;
using grpc::Status;
using grpc::ClientContext;
using grpc::Channel;

class StatusServiceClient : public Singleton<StatusServiceClient> {
    friend class Singleton<StatusServiceClient>;

private:
    std::unique_ptr<StatusService::Stub> stub_;
    StatusServiceClient();
public:
    GetChatServerRsp GetChatServer(int32_t uid);
    LoginVerifyRsp LoginVerify(uint32_t uid, const std::string &token);
};


#endif //CHATSERVER_STATUSSERVICECLIENT_H
