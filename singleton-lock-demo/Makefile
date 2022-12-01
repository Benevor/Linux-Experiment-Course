LDFLAGS+=-lpthread

main:
	g++ -o main main.cpp $(LDFLAGS)

clean:
ifeq (main, $(wildcard main))
	rm main
endif