#include <netinet/in.h>
namespace Bobolle {


class TCPServer {
  private:
    int _port;
    int _serverSocket;
    int _clientSocket;
    sockaddr_in _serverAddress;
  public:
    TCPServer(int port);
    ~TCPServer();
    void signal_handler(int signal);
    int start();
    void stop();
};

}
