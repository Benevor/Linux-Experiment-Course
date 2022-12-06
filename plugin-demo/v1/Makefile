test:test.o libfunc.so
	g++ -o test test.o -ldl
	rm *.o

test.o:test.cpp
	g++ -o test.o -c test.cpp -ldl

libfunc.so:a.h a.cpp
	g++ -fpic -shared -o libfunc.so a.cpp 

lib:a.h a.cpp  
	g++ -fpic -shared -o libfunc.so a.cpp 

clean:
ifeq (libfunc.so, $(wildcard libfunc.so))
	rm libfunc.so
endif

ifeq (test, $(wildcard test))
	rm test
endif