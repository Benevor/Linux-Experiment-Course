# 错误写法
# test:
# 	g++ -o test test.cpp CPluginEnumerator.cpp CPluginController.cpp IPrintPlugin.cpp -ldl

# lib:function.cpp function1.cpp
# 	g++ -fpic -shared -o ./plugin/libfunc.so function.cpp
# 	g++ -fpic -shared -o ./plugin/libfunc1.so function1.cpp

# 正确写法
test:
	g++ -o test test.cpp CPluginEnumerator.cpp CPluginController.cpp -ldl

lib:function.cpp function1.cpp
	g++ -fpic -shared -o ./plugin/libfunc.so function.cpp IPrintPlugin.cpp
	g++ -fpic -shared -o ./plugin/libfunc1.so function1.cpp IPrintPlugin.cpp

clean:
ifeq (test, $(wildcard test))
	rm test
endif

libclean:
ifeq (./plugin/libfunc.so, $(wildcard ./plugin/libfunc.so))
	rm plugin/libfunc.so
endif

ifeq (./plugin/libfunc1.so, $(wildcard ./plugin/libfunc1.so))
	rm plugin/libfunc1.so
endif