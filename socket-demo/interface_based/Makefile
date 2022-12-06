all:
	g++ -o client client.cpp -g
	g++ -o server server.cpp -g

clean:
ifeq (client, $(wildcard client))
	rm client
endif

ifeq (server, $(wildcard server))
	rm server
endif