#include <netinet/in.h>
namespace Bobolle {

class TCPServer {
  private:
    int _port;
    int _serverSocket;
    sockaddr_in _serverAddress;
  public:
    TCPServer(int port);
    ~TCPServer();
    void start();
    void stop();
};

}
