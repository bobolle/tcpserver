#include "TCPClient.hpp"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

namespace Bobolle {

// Constructor
TCPClient::TCPClient(int port) : _port(port) {
  this->_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  this->_serverAddress.sin_family = AF_INET;
  this->_serverAddress.sin_port = htons(this->_port);
  this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
}

// Deconstructor
TCPClient::~TCPClient() {
  stop();
}

// Client start
int TCPClient::start() {
  std::cout << "starting client..." << std::endl;
  if (connect(this->_clientSocket, (struct sockaddr*)&this->_serverAddress, sizeof(this->_serverAddress)) < 0) {
    std::cerr << "Connection failed" << std::endl;
    return -1;
  }

  char message[1024];
  while (1) {
    std::cout << "client: ";
    std::cin.getline(message, sizeof(message));

    if (strcmp(message, "exit") == 0) {
      stop();
      return 0;
    }

    if (send(this->_clientSocket, message, strlen(message), 0) < 0) {
      std::cerr << "Send failed" << std::endl;
    }

    char buffer[32] = {0};
    std::cout << "response from server: ";
    recv(this->_clientSocket, buffer, sizeof(buffer), 0);
    std::cout << buffer << std::endl;
  }
}

// Client stop
void TCPClient::stop() {
  close(this->_clientSocket);
}

}
