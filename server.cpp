#include <iostream>
#include "TCPServer.hpp"

int main() {
  Bobolle::TCPServer server(8080);
  server.start();
  server.stop();

  return 0;
}
