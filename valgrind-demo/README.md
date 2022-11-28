参考链接：https://www.cnblogs.com/freedomabcd/p/7771551.html
valgrind --tool=memcheck ./my_leak
valgrind --tool=memcheck --leak-check=full ./my_leak