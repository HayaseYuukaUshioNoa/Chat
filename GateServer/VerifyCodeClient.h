//
// Created by tom on 25-10-2.
//

#ifndef GATESERVER_VERIFYCODECLIENT_H
#define GATESERVER_VERIFYCODECLIENT_H

#include <grpcpp/grpcpp.h>
#include "Message.grpc.pb.h"
#include "Singleton.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVerifyReq;
using message::GetVerifyRsp;
using message::VerifyService;

class VerifyCodeClient : public Singleton<VerifyCodeClient> {
    friend class Singleton<VerifyCodeClient>;
private:
    std::unique_ptr<VerifyService::Stub> stub_;

    VerifyCodeClient();

public:
    GetVerifyRsp GetVerifyCode(const std::string &email);
};


#endif //GATESERVER_VERIFYCODECLIENT_H
