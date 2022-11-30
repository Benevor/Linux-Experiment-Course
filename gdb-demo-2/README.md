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

inferior 2
break gdb_test.cpp:51
cont
cont

inferior 1
break gdb_test.cpp:42
cont
cont

