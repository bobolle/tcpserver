#include <netinet/in.h>

namespace Bobolle {

class TCPClient {
  private:
    int _port;
    int _clientSocket;
    sockaddr_in _serverAddress;
  public:
    TCPClient(int port);
    ~TCPClient();
    int start();
    void stop();
};

}
