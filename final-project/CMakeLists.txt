cmake_minimum_required(VERSION 3.15)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")

# 头文件
include_directories(
        ${PROJECT_SOURCE_DIR}/HostA/ServerA
)

# 源文件
file(GLOB_RECURSE client
        ${PROJECT_SOURCE_DIR}/Client/*.cpp
        )

file(GLOB_RECURSE server_a
        ${PROJECT_SOURCE_DIR}/HostA/ServerA/*.cpp
        )

file(GLOB_RECURSE server_b
        ${PROJECT_SOURCE_DIR}/HostB/ServerB/*.cpp
        )

add_executable(client ${client})
add_executable(server_a ${server_a})
#add_executable(server_b ${server_b})