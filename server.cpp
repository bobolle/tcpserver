#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

// server
int main() {
  // AF_INET, specifies ipv4 protocol family
  // SOCK_STREAM, defines TCP type socket
  // create socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // store adress of socket
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  // htons, convert unsigned int from machine byte order to network byte order
  serverAddress.sin_port = htons(8080);
  // dont bind socket to certain IP, listen to all
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // assign adress to socket
  if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
    std::cerr << "Bind failed" << std::endl;
  }

  // listen for connections, backlog limits listen queue
  if (listen(serverSocket, 5) < 0) {
    std::cerr << "Listen failed" << std::endl;
  }

  std::cout << "Listening..." << std::endl;
  while (1) {
    // accept a new connection on a socket
    // socket, address, address_len
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // start receiving data from client
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer << std::endl;

    // send back response?
    const char* message = "402";
    send(clientSocket, message, strlen(message), 0);
  }

  close(serverSocket);

  return 0;
}
