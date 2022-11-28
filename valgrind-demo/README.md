参考链接：https://www.cnblogs.com/freedomabcd/p/7771551.html

```bash
make

valgrind --tool=memcheck ./my_leak

valgrind --tool=memcheck --leak-check=full ./my_leak
```