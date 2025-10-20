cmake_minimum_required(VERSION 3.22)

project(VerifyServer)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(PYTHON_INCLUDE_PATH "/usr/include/python3.12")

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_library(HIREDIS_LIB hiredis REQUIRED)
find_library(PYTHON_LIB python3.12 REQUIRED)
find_library(BOOST_PYTHON_LIB boost_python312 REQUIRED)
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

add_executable(VerifyServer VerifyServer.cpp
        Common.h
        Singleton.h
        RedisMgr.cpp
        RedisMgr.h
        RedisPool.cpp
        RedisPool.h
        ConfigMgr.cpp
        ConfigMgr.h
        SendMail.h
        SendMail.cpp
        VerifyServerImpl.h
        VerifyServerImpl.cpp
        Logger.cpp
        Logger.h
        ScopeExit.cpp
        ScopeExit.h
)
target_include_directories(VerifyServer PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${PYTHON_INCLUDE_PATH})
target_link_libraries(VerifyServer PRIVATE
        Boost::headers
        nlohmann_json::nlohmann_json
        protobuf::libprotobuf
        message
        spdlog::spdlog
        ${HIREDIS_LIB}
        ${PYTHON_LIB}
        ${BOOST_PYTHON_LIB}
)