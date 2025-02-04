#include "TCPServer.hpp"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>


namespace Bobolle {

//Constructor
TCPServer::TCPServer(int port) : _port(port) {
  this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  this->_serverAddress.sin_family = AF_INET;
  this->_serverAddress.sin_port = htons(this->_port);
  this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
}

// Deconstructor
TCPServer::~TCPServer() {
  stop();
}

// Server start
int TCPServer::start() {
  std::cout << "starting server..." << std::endl;

  if (bind(this->_serverSocket, (struct sockaddr*) &this->_serverAddress, sizeof(this->_serverAddress)) < 0) {
    std::cerr << "bind failed" << std::endl;
    return -1;
  }

  if (listen(this->_serverSocket, 5) < 0) {
    std::cerr << "listen failed" << std::endl;
    return -1;
  }

  struct timeval timeout;
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;


  while (1) {
      this->_clientSocket = accept(this->_serverSocket, nullptr, nullptr);
      setsockopt(this->_clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

      while (1) {
        char buffer[1024] = {0};
        recv(this->_clientSocket, buffer, sizeof(buffer), 0);
        std::cout << "server: " << buffer << std::endl;

        if (errno == EAGAIN) {
            close(this->_clientSocket);
            break;
        }
      }
  }

  this->stop();
}

// Server Close
void TCPServer::stop() {
  close(this->_serverSocket);
  close(this->_clientSocket);
}

}
