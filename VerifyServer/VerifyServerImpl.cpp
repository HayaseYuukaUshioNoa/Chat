#include "VerifyServerImpl.h"
#include "SendMail.h"
#include "Common.h"
#include "RedisPool.h"
#include "ScopeExit.h"
#include "Logger.h"

VerifyServerImpl::VerifyServerImpl()
{

}

Status VerifyServerImpl::GetVerifyCode(ServerContext *context, const GetVerifyReq *request, GetVerifyRsp *response)
{
    try {
        std::string email = request->email();
        auto redis_mgr = RedisPool::instance()->redis_mgr();
        ScopeExit se([&redis_mgr]() {
            RedisPool::instance()->recycle_redis_mgr(redis_mgr);
        });
        std::string verifycode;
        std::string value;
        // 查询redis
        if (redis_mgr->get(email, value)) {
            verifycode = value;
        } else {
            // 生成新的验证码
            verifycode = GenerateVerifycode();
            redis_mgr->set(email, verifycode);
            redis_mgr->expire(email, 600);
        }
        response->set_email(email);
        // 发送邮件
        LOG_INFO("will to send mail");
        if (SendMail(email, verifycode)) {
            response->set_error(ErrorCode::SUCCESS);
        } else {
            response->set_error(ErrorCode::ERROR);
        }
        return Status::OK;
    } catch (const std::exception &e) {
        LOG_INFO("{}", e.what());
        return Status::OK;
    }
}

VerifyServerImpl::~VerifyServerImpl()
{

}
