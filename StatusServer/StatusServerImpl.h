//
// Created by tom on 25-10-10.
//

#ifndef STATUSSERVER_STATUSSERVERIMPL_H
#define STATUSSERVER_STATUSSERVERIMPL_H

#include <grpcpp/grpcpp.h>
#include <Message.grpc.pb.h>
#include <unordered_map>
#include <mutex>

using grpc::Status;
using grpc::ServerContext;
using grpc::ServerBuilder;
using grpc::Server;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::StatusService;
using message::LoginVerifyReq;
using message::LoginVerifyRsp;

struct ChatServer {
    std::string host;
    std::string port;
};

class StatusServerImpl : public StatusService::Service {
private:
    ChatServer chat_server_;
    std::unordered_map<int32_t, std::string> uid_token_;
    std::mutex mutex_;

    void insert_uid_token(int32_t uid, const std::string& token);

public:
    StatusServerImpl();

    Status GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* response);
    Status LoginVerify(ServerContext* context, const LoginVerifyReq* request, LoginVerifyRsp* response);
};


#endif //STATUSSERVER_STATUSSERVERIMPL_H
