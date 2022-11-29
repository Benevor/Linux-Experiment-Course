all:
	g++ -o client client.cpp
	g++ -o server server.cpp

clean:
ifeq (client, $(wildcard client))
	rm client
endif

ifeq (server, $(wildcard server))
	rm server
endif