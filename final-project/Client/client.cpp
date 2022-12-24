#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

class CTCPClient {
 public:
  CTCPClient(int nServerPort, const char *strServerIP) {
    m_nServerPort = nServerPort;

    int nlength = strlen(strServerIP);
    m_strServerIP = new char[nlength + 1];
    strcpy(m_strServerIP, strServerIP);
  }

  virtual ~CTCPClient() {
    delete[] m_strServerIP;
  }

 public:
  int Run() {
    int nClientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == nClientSocket) {
      std::cout << "socket error" << std::endl;
      return -1;
    }

    sockaddr_in ServerAddress;
    memset(&ServerAddress, 0, sizeof(sockaddr_in));
    ServerAddress.sin_family = AF_INET;
    if (::inet_pton(AF_INET, m_strServerIP, &ServerAddress.sin_addr) != 1) {
      std::cout << "inet_pton error" << std::endl;
      ::close(nClientSocket);
      return -1;
    }

    ServerAddress.sin_port = htons(m_nServerPort);

    if (::connect(nClientSocket, (sockaddr *) &ServerAddress, sizeof(ServerAddress)) == -1) {
      std::cout << "connect error" << std::endl;
      ::close(nClientSocket);
      return -1;
    }

    ClientFunction(nClientSocket);

    ::close(nClientSocket);

    return 0;
  }

 private:
  virtual void ClientFunction(int nConnectedSocket) = 0;

 private:
  int m_nServerPort;
  char *m_strServerIP;
};

class CMyTCPClient : public CTCPClient {
 public:
  CMyTCPClient(int nServerPort, const char *strServerIP) : CTCPClient(nServerPort, strServerIP) {
  }

  virtual ~CMyTCPClient() {
  }

 private:
  virtual void ClientFunction(int nConnectedSocket) {
    char buf[35];

    ::read(nConnectedSocket, buf, 35);

    std::cout << buf << std::endl;
  }
};

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }
  int server_port = atoi(argv[1]);
  CMyTCPClient client(server_port, "127.0.0.1");
  client.Run();

  return 0;
}
