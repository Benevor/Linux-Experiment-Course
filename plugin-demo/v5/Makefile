test:
	g++ -o test test.cpp CPluginEnumerator.cpp CPluginController.cpp -ldl

lib:function.cpp function1.cpp
	g++ -fpic -shared -o ./plugin/sl.so function.cpp IPrintPlugin.cpp
	g++ -fpic -shared -o ./plugin/sw.so function1.cpp IPrintPlugin.cpp

clean:
ifeq (test, $(wildcard test))
	rm test
endif

libclean:
ifeq (./plugin/sl.so, $(wildcard ./plugin/sl.so))
	rm plugin/sl.so
endif

ifeq (./plugin/sw.so, $(wildcard ./plugin/sw.so))
	rm plugin/sw.so
endif

dataclean:
ifeq (./data/1.txt, $(wildcard ./data/1.txt))
	rm data/1.txt
endif