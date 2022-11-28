安装gtest
参考链接：https://blog.csdn.net/wdcyf15/article/details/108855960?spm=1001.2014.3001.5502
git仓库地址: https://github.com/google/googletest
sudo apt install unzip
wget https://github.com/google/googletest/archive/refs/tags/release-1.8.1.zip
unzip release-1.8.1.zip
cd googletest-release-1.8.1/
cmake CMakeLists.txt
make
sudo make install
ls -l /usr/local/lib

运行测试
方法一：
    g++ ./test/gtest_main.cpp ./test/unit_test.cpp ./MyProject/my_math.cpp -o my_test -lgtest -lgmock -lpthread -std=c++11
方法二：使用cmake
    mkdir build
    cd build
    cmake ..
    make
    ./test_my_math