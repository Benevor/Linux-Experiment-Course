LDFLAGS+=-lpthread

main: main.cpp lazy.h hungry.h
	g++ -o main main.cpp $(LDFLAGS)

clean:
ifeq (main, $(wildcard main))
	rm main
endif