cmake_minimum_required(VERSION 3.15)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")

# 头文件
include_directories(
        ${PROJECT_SOURCE_DIR}/Server/
        ${PROJECT_SOURCE_DIR}/Client/
)

# 源文件
file(GLOB_RECURSE client
        ${PROJECT_SOURCE_DIR}/Client/*.cpp
        )

file(GLOB_RECURSE server
        ${PROJECT_SOURCE_DIR}/Server/*.cpp
        )

file(GLOB_RECURSE store
        ${PROJECT_SOURCE_DIR}/Store/*.cpp
        )

add_executable(client ${client})
add_executable(server ${server})
add_executable(store ${store})
#add_executable(server_b ${server_b})