#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

// client
int main(int argc, char** argv) {
  // AF_INET, specifies ipv4 protocol family
  // SOCK_STREAM, defines TCP type socket
  // create socket
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  // store adress of socket
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  // htons, convert unsigned int from machine byte order to network byte order
  serverAddress.sin_port = htons(8080);
  // dont bind socket to certain IP, listen to all
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // connect socket to adress
  if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
    std::cerr << "Connection failed" << std::endl;
  }

  // send message on a socket
  const char* message = "test message";
  send(clientSocket, message, strlen(message), 0);

  // get response
  char buffer[1024] = {0};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  std::cout << buffer << std::endl;

  close(clientSocket);

  return 0;
}
