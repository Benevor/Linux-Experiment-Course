LDFLAGS+=-lpthread

test : main.o process.o
	g++ -o test main.o process.o $(LDFLAGS)

main.o : main.cpp process.h
	g++ -o main.o -c main.cpp

process.o : process.cpp process.h
	g++ -o process.o -c process.cpp

clean :
ifneq ("", $(wildcard *.o))
	rm *.o
endif

ifeq (test, $(wildcard test))
	rm test
endif