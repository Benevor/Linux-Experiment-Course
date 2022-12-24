test : test.cpp  serializable.h
	g++ -o test test.cpp

clean :
ifeq (test, $(wildcard test))
	rm test
endif

ifeq (data, $(wildcard data))
	rm data
endif