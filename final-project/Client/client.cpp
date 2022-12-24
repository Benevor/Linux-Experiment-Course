#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#define REQUEST_BYTE_MAX 100
#define RESPONSE_BYTE_MAX 500

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

  int Run(char *command) {
    auto re = ClientFunction(nClientSocket_, command);
    return re;
  }

  void Close() {
    ::close(nClientSocket_);
  }

 private:
  virtual int ClientFunction(int nConnectedSocket, char *command) = 0;

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
  virtual int ClientFunction(int nConnectedSocket, char *command) {
    if (command == nullptr) {
      return -1;
    }

    if (strcmp(command, "getfood") == 0) {
      // send request
      char request[REQUEST_BYTE_MAX];
      memset(request, 0, REQUEST_BYTE_MAX);
      int offset = 0;
      memcpy(request + offset, user_name_, strlen(user_name_));
      offset += strlen(user_name_);
      memcpy(request + offset, "|", 1);
      offset += 1;
      memcpy(request + offset, command, strlen(command));
      offset += strlen(command);
      memcpy(request + offset, "|", 1);
      ::write(nConnectedSocket, request, REQUEST_BYTE_MAX);

      // receive response
      char response[RESPONSE_BYTE_MAX];
      memset(response, 0, RESPONSE_BYTE_MAX);
      ::read(nConnectedSocket, response, RESPONSE_BYTE_MAX);
      std::cout << response << std::endl;
    } else {
      std::cout << "else" << std::endl;
    }
    return 0;
  }

 public:
  char user_name_[20];
};

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }
  int server_port = atoi(argv[1]);
  CMyTCPClient client(server_port, "127.0.0.1");
  client.Init();

  std::cout << "Please enter your user name: ";
  std::cin >> client.user_name_;

  char command[50];
  std::cout << "Please enter your command: ";
  std::cin >> command;
  while (strcmp(command, "q") != 0 && strcmp(command, "exit") != 0) {
    client.Run(command);
    std::cout << "Please enter your command: ";
    std::cin >> command;
  }

  client.Close();

  return 0;
}
