#include "TCPServer.hpp"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

namespace Bobolle {

//Constructor
TCPServer::TCPServer(int port) : _port(port) {
  this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  this->_serverAddress.sin_family = AF_INET;
  this->_serverAddress.sin_port = htons(this->_port);
  this->_serverAddress.sin_addr.s_addr = INADDR_ANY;

  if (bind(this->_serverSocket, (struct sockaddr*) &this->_serverAddress, sizeof(this->_serverAddress)) < 0) {
    std::cerr << "bind failed" << std::endl;
  }
}

// Deconstructor
TCPServer::~TCPServer() {
  stop();
}

// Server start
void TCPServer::start() {
  std::cout << "starting server..." << std::endl;
  if (listen(this->_serverSocket, 5) < 0) {
    std::cerr << "listen failed" << std::endl;
  }

  int clientSocket = accept(this->_serverSocket, nullptr, nullptr);

  while (1) {
    std::cout << "server: ";

    char buffer[128] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "message from client: " << buffer << std::endl;
    
    const char* message = "402";
    send(clientSocket, message, strlen(message), 0);
  }
}

// Server Close
void TCPServer::stop() {
  close(this->_serverSocket);
}

}
