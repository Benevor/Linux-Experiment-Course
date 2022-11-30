LDFLAGS+=-lpthread

gdb_test:
	g++ -g gdb_test.cpp -o gdb_test $(LDFLAGS)

clean:
ifeq (gdb_test, $(wildcard gdb_test))
	rm gdb_test
endif