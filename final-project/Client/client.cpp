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
  int Init() {
    // nClientSocket_ init
    nClientSocket_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == nClientSocket_) {
      std::cout << "socket error" << std::endl;
      return -1;
    }

    // ServerAddress_ init
    memset(&ServerAddress_, 0, sizeof(sockaddr_in));
    ServerAddress_.sin_family = AF_INET;
    if (::inet_pton(AF_INET, m_strServerIP, &ServerAddress_.sin_addr) != 1) {
      std::cout << "inet_pton error" << std::endl;
      ::close(nClientSocket_);
      return -1;
    }
    ServerAddress_.sin_port = htons(m_nServerPort);

    if (::connect(nClientSocket_, (sockaddr *) &ServerAddress_, sizeof(ServerAddress_)) == -1) {
      std::cout << "connect error" << std::endl;
      ::close(nClientSocket_);
      return -1;
    }

    return 0;
  }

  int Run() {
    auto re = ClientFunction(nClientSocket_);
    return re;
  }

  int Close() {
    ::close(nClientSocket_);
    return 0;
  }

 private:
  virtual int ClientFunction(int nConnectedSocket) = 0;

 private:
  int m_nServerPort;
  char *m_strServerIP;

  // add by Benevor
  int nClientSocket_;
  sockaddr_in ServerAddress_;
};

class CMyTCPClient : public CTCPClient {
 public:
  CMyTCPClient(int nServerPort, const char *strServerIP) : CTCPClient(nServerPort, strServerIP) {
  }

  virtual ~CMyTCPClient() {
  }

 private:
  virtual int ClientFunction(int nConnectedSocket) {
    char buf[35];

    ::read(nConnectedSocket, buf, 35);

    std::cout << buf << std::endl;
    return 0;
  }
};

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }
  int server_port = atoi(argv[1]);
  CMyTCPClient client(server_port, "127.0.0.1");
  client.Init();

  client.Run();

  client.Close();

  return 0;
}
