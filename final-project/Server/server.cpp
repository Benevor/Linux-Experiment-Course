#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "serializable.h"

#define SERVER_A_NAME "ServerA"
#define SERVER_B_NAME "ServerB"
#define HOST_A_PATH "/home/liujibo/Linux-Experiment-Course/final-project/HostA/"
#define HOST_B_PATH "/home/liujibo/Linux-Experiment-Course/final-project/HostB/"

#define REQUEST_BYTE_MAX 100
#define RESPONSE_BYTE_MAX 500

class CTCPServer {
 public:
  CTCPServer(int nServerPort,
             std::string server_name,
             std::string file_path,
             int nLengthOfQueueOfListen = 100,
             const char *strBoundIP = nullptr) {
    m_nServerPort = nServerPort;
    m_nLengthOfQueueOfListen = nLengthOfQueueOfListen;

    if (strBoundIP == nullptr) {
      m_strBoundIP = nullptr;
    } else {
      auto length = strlen(strBoundIP);
      m_strBoundIP = new char[length + 1];
      memcpy(m_strBoundIP, strBoundIP, length + 1);
    }

    server_name_ = new char[server_name.size()];
    strcpy(server_name_, server_name.c_str());

    file_path_ = new char[file_path.size()];
    strcpy(file_path_, file_path.c_str());
  }

  virtual ~CTCPServer() {
    if (m_strBoundIP != nullptr) {
      delete[] m_strBoundIP;
    }
    delete file_path_;
  }

 public:
  int Run() {
    int nListenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (nListenSocket == -1) {
      std::cout << "socket error" << std::endl;
      return -1;
    }

    sockaddr_in ServerAddress;
    memset(&ServerAddress, 0, sizeof(sockaddr_in));
    ServerAddress.sin_family = AF_INET;

    if (m_strBoundIP == nullptr) {
      ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
      if (::inet_pton(AF_INET, m_strBoundIP, &ServerAddress.sin_addr) != 1) {
        std::cout << "inet_pton error" << std::endl;
        ::close(nListenSocket);
        return -1;
      }
    }

    ServerAddress.sin_port = htons(m_nServerPort);

    if (::bind(nListenSocket, (sockaddr *) &ServerAddress, sizeof(sockaddr_in)) == -1) {
      std::cout << "bind error" << std::endl;
      ::close(nListenSocket);
      return -1;
    }

    if (::listen(nListenSocket, m_nLengthOfQueueOfListen) == -1) {
      std::cout << "listen error" << std::endl;
      ::close(nListenSocket);
      return -1;
    }

    // LJB:: 修改为无限次响应的服务器
    while (true) {
      sockaddr_in ClientAddress;
      socklen_t LengthOfClientAddress = sizeof(sockaddr_in);
      int nConnectedSocket = ::accept(nListenSocket, (sockaddr *) &ClientAddress, &LengthOfClientAddress);
      if (nConnectedSocket == -1) {
        std::cout << "accept error" << std::endl;
        ::close(nListenSocket);
        return -1;
      }

      auto re = ServerFunction(nConnectedSocket, nListenSocket);

      ::close(nConnectedSocket);
      if (re != 0) {
        break;
      }
    }

    ::close(nListenSocket);
    return 0;
  }

 private:
  virtual int ServerFunction(int nConnectedSocket, int nListenSocket) = 0;
  virtual bool serialize() = 0;
  virtual bool deserialize() = 0;

 private:
  int m_nServerPort;
  char *m_strBoundIP;
  int m_nLengthOfQueueOfListen;
  char *file_path_;
  char *server_name_;
};

class CMyTCPServer : public CTCPServer {
 public:
  CMyTCPServer(int nServerPort,
               std::string server_name,
               std::string file_path,
               int nLengthOfQueueOfListen = 100,
               const char *strBoundIP = nullptr) : CTCPServer(
      nServerPort,
      server_name,
      file_path,
      nLengthOfQueueOfListen,
      strBoundIP) {
  }

  virtual ~CMyTCPServer() {
  }

 private:
  virtual int ServerFunction(int nConnectedSocket, int nListenSocket) {
    char request[REQUEST_BYTE_MAX];
    std::vector<char *> result;

    while (!(result.size() == 2 && strcmp(result[1], "close") == 0)) {
      if (!result.empty()) {
        // 执行命令
        do_command(nConnectedSocket, result);
      }

      // 循环接收命令
      result.clear();
      memset(request, 0, REQUEST_BYTE_MAX);
      ::read(nConnectedSocket, request, REQUEST_BYTE_MAX);

      // 切割命令
      char delims[] = "|";
      char *tmp = nullptr;
      tmp = strtok(request, delims);
      while (tmp != nullptr) {
        result.push_back(tmp);
        tmp = strtok(nullptr, delims);
      }
    }

    std::cout << "close connection !!! " << std::endl;
    return 0;
  }

  virtual bool serialize() {
    return true;
  }

  virtual bool deserialize() {
    return true;
  };

  void do_command(int nConnectedSocket, std::vector<char *> result) {
    if (result.size() == 2 && strcmp(result[1], "getfood") == 0) {
      Food f(2, "food1");
      add_food(&f);
      auto info = get_all_food_info();
      ::write(nConnectedSocket, info.c_str(), strlen(info.c_str()));
    }
  }

  std::string get_all_food_info() {
    std::stringstream ss;
    for (int i = 0; i < foods_.size(); ++i) {
      ss << foods_[i]->get_info();
      ss << "\n";
    }
    std::string str = ss.str();
    return str;
  }

  std::string get_all_record_info() {
    return "";
  }

  void add_food(Food *f) {
    foods_.push_back(f);
  }

  std::vector<Food *> foods_;
  std::vector<Record *> records_;
};

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }

  int server_port = atoi(argv[1]);
  std::string server_name;
  std::string host_path;

  if (strcmp(argv[2], "a") == 0) {
    server_name = SERVER_A_NAME;
  } else if (strcmp(argv[2], "b") == 0) {
    server_name = SERVER_B_NAME;
  } else {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }

  if (strcmp(argv[3], "a") == 0) {
    host_path = HOST_A_PATH;
  } else if (strcmp(argv[3], "b") == 0) {
    host_path = HOST_B_PATH;
  } else {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }

  CMyTCPServer my_server(server_port, server_name, host_path);
  my_server.Run();
  return 0;
}