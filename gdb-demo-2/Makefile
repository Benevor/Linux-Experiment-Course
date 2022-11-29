LDFLAGS+=-lpthread

gdb_test:
	g++ -g gdb_test.cpp -o gdb_test $(LDFLAGS)

clean:
ifeq (my_leak, $(wildcard my_leak))
	rm gdb_test
endif