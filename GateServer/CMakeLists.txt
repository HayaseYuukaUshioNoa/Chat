cmake_minimum_required(VERSION 3.28)

project(GateServer)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_library(HIREDIS_LIB hiredis REQUIRED)
find_library(MYSQL_LIB mysqlclient REQUIRED)
find_package(spdlog REQUIRED)

add_library(message Message.proto)
target_link_libraries(message PUBLIC gRPC::grpc++)

protobuf_generate(TARGET message)
protobuf_generate(
        TARGET message
        LANGUAGE grpc
        PLUGIN protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
)

add_executable(GateServer GateServer.cpp
        Common.h
        CServer.cpp
        CServer.h
        HttpConnection.cpp
        HttpConnection.h
        LogicSystem.cpp
        LogicSystem.h
        Singleton.h
        UriCode.cpp
        UriCode.h
        VerifyCodeClient.cpp
        VerifyCodeClient.h
        RedisMgr.cpp
        RedisMgr.h
        RedisPool.cpp
        RedisPool.h
        MySqlConnection.cpp
        MySqlConnection.h
        MySqlPool.cpp
        MySqlPool.h
        MySqlMgr.cpp
        MySqlMgr.h
        JsonParser.cpp
        JsonParser.h
        StatusServiceClient.cpp
        StatusServiceClient.h
        ConfigMgr.cpp
        ConfigMgr.h
        Logger.h
        Logger.cpp
        ScopeExit.cpp
        ScopeExit.h
        Utility.h
        ErrorCode.h
)
target_include_directories(GateServer PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(GateServer PRIVATE
        Boost::headers
        nlohmann_json::nlohmann_json
        protobuf::libprotobuf
        message
        spdlog::spdlog
        ${HIREDIS_LIB}
        ${MYSQL_LIB}
)
