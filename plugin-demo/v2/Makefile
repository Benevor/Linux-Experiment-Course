test:
	g++ -o test test.cpp CPluginEnumerator.cpp -ldl

lib:function.cpp function1.cpp
	g++ -fpic -shared -o ./plugin/libfunc.so function.cpp
	g++ -fpic -shared -o ./plugin/libfunc1.so function1.cpp

clean:
ifeq (./plugin/libfunc.so, $(wildcard ./plugin/libfunc.so))
	rm plugin/libfunc.so
endif

ifeq (./plugin/libfunc1.so, $(wildcard ./plugin/libfunc1.so))
	rm plugin/libfunc1.so
endif

ifeq (test, $(wildcard test))
	rm test
endif
