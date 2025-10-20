cmake_minimum_required(VERSION 3.28)

project(ChatServer)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
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

add_executable(ChatServer ChatServer.cpp
        CServer.cpp
        CServer.h
        Common.h
        Session.cpp
        Session.h
        ConfigMgr.cpp
        ConfigMgr.h
        Singleton.h
        LogicSystem.cpp
        LogicSystem.h
        JsonParser.cpp
        JsonParser.h
        MySqlConnection.cpp
        MySqlConnection.h
        MySqlPool.cpp
        MySqlPool.h
        MySqlMgr.cpp
        MySqlMgr.h
        StatusServiceClient.cpp
        StatusServiceClient.h
        Logger.cpp
        Logger.h
        ScopeExit.cpp
        ScopeExit.h
        ErrorCode.h
)
target_include_directories(ChatServer PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(ChatServer PRIVATE
        Boost::headers
        nlohmann_json::nlohmann_json
        protobuf::libprotobuf
        message
        spdlog::spdlog
        ${MYSQL_LIB}
)
