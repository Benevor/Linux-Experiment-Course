# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

# 头文件
include_directories(
        ${PROJECT_SOURCE_DIR}/MyProject
)

# 源文件
file(GLOB_RECURSE my_math
        ${PROJECT_SOURCE_DIR}/MyProject/*.cpp
        ${PROJECT_SOURCE_DIR}/test/*.cpp
        )

add_executable(test_my_math ${my_math})

# 链接测试库
target_link_libraries( test_my_math
        ${GTEST_BOTH_LIBRARIES}
        pthread )

# 添加到测试
gtest_discover_tests(test_my_math)
