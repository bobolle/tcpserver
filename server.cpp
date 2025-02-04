#include <iostream>
#include "TCPServer.hpp"
#include <signal.h>

Bobolle::TCPServer server(8080);

void signal_handler(int signal) {
    std::cout << std::endl << "closing server..." << std::endl;
    server.stop();
    exit(0);
}

int main() {
    signal(SIGINT, signal_handler);
    server.start();

    return 0;
}
