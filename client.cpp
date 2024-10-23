#include <iostream>
#include "TCPClient.hpp"

int main() {
  Bobolle::TCPClient client(8080);
  client.start();
  client.stop();

  return 0;
}
