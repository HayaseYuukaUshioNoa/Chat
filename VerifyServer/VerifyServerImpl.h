#pragma once

#include <Message.grpc.pb.h>
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::Status;
using grpc::ServerContext;
using grpc::ServerBuilder;

using message::GetVerifyReq;
using message::GetVerifyRsp;
using message::VerifyService;

class VerifyServerImpl : public VerifyService::Service {
public:
    VerifyServerImpl();
    ~VerifyServerImpl();
    Status GetVerifyCode(ServerContext* context, const GetVerifyReq* request, GetVerifyRsp* response);
};