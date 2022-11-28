helloworld : main.o print.o
	g++ -o helloworld main.o print.o

test : test.o print.o
	g++ -o test test.o print.o

mian.o : mian.cpp print.h
	g++ -o mian.o -c main.cpp

test.o : test.cpp print.h
	g++ -o test.o -c test.cpp

print.o : print.cpp print.h
	g++ -o print.o -c print.cpp

clean :
	rm *.o
	rm test
	rm helloworld