test : test.cpp serializer.h serializable.h
	g++ -o test test.cpp

clean :
ifeq (test, $(wildcard test))
	rm test
endif

ifeq (data1, $(wildcard data1))
	rm data1
endif