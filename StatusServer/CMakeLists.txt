cmake_minimum_required(VERSION 3.22)

project(StatusServer)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

find_package(Boost REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(nlohmann_json REQUIRED)
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

add_executable(StatusServer StatusServer.cpp
        StatusServerImpl.cpp
        StatusServerImpl.h
        Common.h
        ConfigMgr.cpp
        ConfigMgr.h
        Singleton.h
        Logger.cpp
        Logger.h
        ErrorCode.h)
target_include_directories(StatusServer PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(StatusServer PRIVATE
        message
        protobuf::libprotobuf
        Boost::headers
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)