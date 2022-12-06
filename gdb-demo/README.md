参考链接：https://blog.csdn.net/pbymw8iwm/article/details/7876797

```bash
set detach-on-fork off
show detach-on-fork
catch fork
r
info inferiors
break gdb_test.cpp:12
cont
info inferiors

break gdb_test.cpp:27
cont
info thread

inferior 2
break gdb_test.cpp:52
cont
cont

inferior 1
break gdb_test.cpp:43
cont
info thread

inferior 2
cont

inferior 1
cont

```
