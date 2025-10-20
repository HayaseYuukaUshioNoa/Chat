//
// Created by tom on 25-10-2.
//

#include "LogicSystem.h"
#include "Common.h"
#include "VerifyCodeClient.h"
#include "StatusServiceClient.h"
#include "HttpConnection.h"
#include "RedisPool.h"
#include "MySqlMgr.h"
#include "JsonParser.h"
#include "Logger.h"
#include "ErrorCode.h"
#include "ScopeExit.h"

void LogicSystem::register_get(const std::string &url, LogicSystem::HttpHandler handler)
{
    get_handlers_.insert(std::make_pair(url, handler));
}

LogicSystem::LogicSystem()
{
    register_get("/get_test", [](std::shared_ptr<HttpConnection> connection) {

    });
    register_post("/get_verify_code", [](std::shared_ptr<HttpConnection> connection) {
        try {
            auto str = beast::buffers_to_string(connection->request_.body().data());
            connection->response_.set(http::field::content_type, "application/json");
            // 解析客户端json
            JsonParser parser;
            parser.parse(str);
            std::string email = parser.email();
            LOG_INFO("user email: {}", email);
            GetVerifyRsp response = VerifyCodeClient::instance()->GetVerifyCode(email);
            LOG_INFO("VerifyService response({}, {})", response.email(), response.error());

            json root;
            root["error"] = response.error();
            root["email"] = email;
            beast::ostream(connection->response_.body()) << root.dump();
        } catch (const std::exception &e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            beast::ostream(connection->response_.body()) << err.dump();
        }
    });
    register_post("/user_register", [this](std::shared_ptr<HttpConnection> connection) {
        try {
            auto str = beast::buffers_to_string(connection->request_.body().data());
            connection->response_.set(http::field::content_type, "application/json");
            // 解析客户端json
            JsonParser parser;
            parser.parse(str);
            std::string email = parser.email();
            std::string verifycode = parser.verifycode();
            LOG_INFO("register info({}, {})", email, verifycode);

            std::string value;
            auto redis_mgr = RedisPool::instance()->redis_mgr();
            ScopeExit se([&redis_mgr]() {
                RedisPool::instance()->recycle_redis_mgr(redis_mgr);
            });
            // 验证码超时
            if (!redis_mgr->get(email, value)) {
                LOG_WARN("verifycode expired");
                json root;
                root["error"] = ErrorCode::VERIFYCODE_EXPIRED;
                beast::ostream(connection->response_.body()) << root.dump();
                return;
            }
            // 验证码输入不正确
            if (verifycode != value) {
                LOG_WARN("verifycode don't match, src: {}, dest: {}", verifycode, value);
                json root;
                root["error"] = ErrorCode::VERIFYCODE_ERROR;
                beast::ostream(connection->response_.body()) << root.dump();
                return;
            }

            // 注册用户
            std::string username = parser.username();
            std::string password = parser.password();
            if (!MySqlMgr::register_user(username, email, password)) {
                LOG_WARN("register user error");
                json root;
                root["error"] = ErrorCode::REGISTER_USER_ERROR;
                beast::ostream(connection->response_.body()) << root.dump();
                return;
            }

            parser.set_errcode(ErrorCode::SUCCESS);
            json root = parser.to_json();
            beast::ostream(connection->response_.body()) << root.dump();
            LOG_INFO("register success");
        } catch (const std::exception &e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            beast::ostream(connection->response_.body()) << err.dump();
        }
    });
    register_post("/reset_pwd", [this](std::shared_ptr<HttpConnection> connection) {
        try {
            auto str = beast::buffers_to_string(connection->request_.body().data());
            connection->response_.set(http::field::content_type, "application/json");
            // 解析客户端json
            JsonParser parser;
            parser.parse(str);
            std::string email = parser.email();
            std::string verifycode = parser.verifycode();
            LOG_INFO("reset info({}, {})", email, verifycode);

            std::string value;
            auto redis_mgr = RedisPool::instance()->redis_mgr();
            ScopeExit se([&redis_mgr]() {
                RedisPool::instance()->recycle_redis_mgr(redis_mgr);
            });
            // 验证码超时
            if (!redis_mgr->get(email, value)) {
                LOG_WARN("verifycode expired");
                json root;
                root["error"] = ErrorCode::VERIFYCODE_EXPIRED;
                beast::ostream(connection->response_.body()) << root.dump();
                return;
            }
            // 验证码输入不正确
            if (verifycode != value) {
                LOG_WARN("verifycode don't match, src: {}, dest: {}", verifycode, value);
                json root;
                root["error"] = ErrorCode::VERIFYCODE_ERROR;
                beast::ostream(connection->response_.body()) << root.dump();
                return;
            }

            // 重置密码
            std::string username = parser.username();
            std::string password = parser.password();
            if (!MySqlMgr::reset_pwd(username, password)) {
                LOG_WARN("reset password error");
                json root;
                root["error"] = ErrorCode::RESET_PWD_ERROR;
                beast::ostream(connection->response_.body()) << root.dump();
                return;
            }

            parser.set_errcode(ErrorCode::SUCCESS);
            json root = parser.to_json();
            beast::ostream(connection->response_.body()) << root.dump();
            LOG_INFO("reset password success");
        } catch (const std::exception &e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            beast::ostream(connection->response_.body()) << err.dump();
        }
    });
    register_post("/user_login", [this](std::shared_ptr<HttpConnection> connection) {
        try {
            auto str = beast::buffers_to_string(connection->request_.body().data());
            connection->response_.set(http::field::content_type, "application/json");
            // 解析客户端json
            JsonParser parser;
            parser.parse(str);
            std::string email = parser.email();
            LOG_INFO("user login email: {}", email);

            std::string password = parser.password();
            UserInfo user;
            // 用户登录
            if (!MySqlMgr::login_user(email, password, user)) {
                LOG_WARN("user login failed");
                json root;
                root["error"] = ErrorCode::USER_LOGIN_ERROR;
                beast::ostream(connection->response_.body()) << root.dump();
                return;
            }

            // 查询StatusServer寻找ChatServer
            int32_t uid = user.uid;
            GetChatServerRsp response = StatusServiceClient::instance()->GetChatServer(uid);
            json root;
            root["uid"] = user.uid;
            root["host"] = response.host();
            root["port"] = response.port();
            root["token"] = response.token();
            root["error"] = response.error();
            beast::ostream(connection->response_.body()) << root.dump();
            LOG_INFO("uid:{}, host:{}, port:{}, token:{}, error:{}", uid, response.host(),
                     response.port(), response.token(), response.error());
            LOG_INFO("user login success");
        } catch (const std::exception &e) {
            LOG_WARN("{}", e.what());
            json err;
            err["error"] = ErrorCode::JSON_ERROR;
            beast::ostream(connection->response_.body()) << err.dump();
        }
    });
}

bool LogicSystem::handle_get(const std::string &url, std::shared_ptr<HttpConnection> connection)
{
    if (get_handlers_.find(url) == get_handlers_.end()) {
        return false;
    }
    get_handlers_[url](connection);
    return true;
}

void LogicSystem::register_post(const std::string &url, LogicSystem::HttpHandler handler)
{
    post_handlers_.insert(std::make_pair(url, handler));
}

bool LogicSystem::handle_post(const std::string &url, std::shared_ptr<HttpConnection> connection)
{
    if (post_handlers_.find(url) == post_handlers_.end()) {
        return false;
    }
    post_handlers_[url](connection);
    return true;
}
