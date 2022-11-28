#include <stdio.h>
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__); //打印入口函数文件名称
    testing::InitGoogleTest(&argc, argv);         //初始化GTEST
    //执行所有测试，执行与主程序一起编译的所有测试用例
    return RUN_ALL_TESTS();
}