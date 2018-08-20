all: Server Client

Server: server.o
	 g++ -o Server server.o utils.o

server.o: server.cpp
	 g++ -c -g server.cpp utils.cpp

Client: client.o
	 	 g++ -o Client client.o utils.o

client.o: client.cpp
	 	 g++ -c -g client.cpp utils.cpp

clean:
	 rm -f *.o Server Client
