helloworld : main.o my_print.o
	g++ -o helloworld main.o my_print.o

test : test.o my_print.o
	g++ -o test test.o my_print.o

mian.o : mian.cpp my_print.h
	g++ -o mian.o -c main.cpp

test.o : test.cpp my_print.h
	g++ -o test.o -c test.cpp

my_print.o : my_print.cpp my_print.h
	g++ -o my_print.o -c my_print.cpp

clean :
	rm *.o
	rm helloworld
	rm test