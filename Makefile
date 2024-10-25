CC = g++
CFLAGS = -Wall -g

all: server client

server: server.o TCPServer.o
	$(CC) $(CFLAGS) -o server server.o TCPServer.o

server.o: server.cpp TCPServer.hpp
	$(CC) $(CFLAGS) -c server.cpp

TCPServer.o: TCPServer.hpp

client: client.o TCPClient.o
	$(CC) $(CFLAGS) -o client client.o TCPClient.o

client.o: server.cpp TCPClient.hpp
	$(CC) $(CFLAGS) -c client.cpp

TCPClient.o: TCPClient.hpp
