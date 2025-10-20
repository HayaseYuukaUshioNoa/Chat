#include "SendMail.h"
#include "ConfigMgr.h"
#include <boost/python.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Logger.h"

namespace py = boost::python;
namespace uuids = boost::uuids;

std::string GenerateVerifycode()
{
    uuids::random_generator generator;
    uuids::uuid uuid = generator();
    std::string uuid_str = uuids::to_string(uuid);
    return uuid_str.substr(0, 4);
}

bool SendMail(const std::string& recipient, const std::string& verifycode)
{
    // 获取GIL
    PyGILState_STATE gstate = PyGILState_Ensure();
    bool result = true;
    try {
        py::object sys = py::import("sys");
        sys.attr("path").attr("append")("python");
        // 导入email_sender模块
        py::object email_sender = py::import("email_sender");
        py::object send_mail = email_sender.attr("send_mail");
        std::string username = ConfigMgr::instance()->get_value("email", "user");
        std::string pwd = ConfigMgr::instance()->get_value("email", "pass");
        result = py::extract<bool>(send_mail(username, pwd, verifycode));
        LOG_INFO("send mail success");
    } catch (py::error_already_set& e) {
        PyErr_Print();
        LOG_WARN("send mail failed");
        result = false;
    } catch (const std::exception& e) {
        LOG_WARN("{}", e.what());
        result = false;
    }
    // 释放GIL
    PyGILState_Release(gstate);
    return result;
}
