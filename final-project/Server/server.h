//
// Created by 26473 on 2022/12/25.
//

#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <mutex>

#include "serializable.h"
#include "common.h"

class CTCPServer;
struct threadPara {
  int nConnectedSocket;
  int nListenSocket;
  CTCPServer *server;
};

class CTCPServer {
 public:
  CTCPServer() {
    this->m_nServerPort = 0;
    this->m_strBoundIP = nullptr;
    this->m_nLengthOfQueueOfListen = 0;
    this->file_path_ = nullptr;
    this->server_name_ = nullptr;
  };
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

    // Benevor:: 修改为无限次响应的服务器
    while (true) {
      sockaddr_in ClientAddress;
      socklen_t LengthOfClientAddress = sizeof(sockaddr_in);
      int nConnectedSocket = ::accept(nListenSocket, (sockaddr *) &ClientAddress, &LengthOfClientAddress);
      if (nConnectedSocket == -1) {
        std::cout << "accept error" << std::endl;
        ::close(nListenSocket);
        return -1;
      }

      // Benevor:: 这里改为子线程处理，就可以使server同时处理多个client的请求
      threadPara tp{nConnectedSocket, nListenSocket, this};
      ServerFunction((void *) (&tp));
    }
    //    ::close(nListenSocket);
    //    return 0;
  }

 private:
  virtual void ServerFunction(void *arg) = 0;
 public:
  virtual void deserialize(std::string src_path, std::string dest_path, CTCPServer *new_server) = 0;

 protected:
  int m_nServerPort;
  char *m_strBoundIP;
  int m_nLengthOfQueueOfListen;
  char *file_path_;
  char *server_name_;

  std::mutex file_lock_;
};

class CMyTCPServer : public CTCPServer {
 public:
  CMyTCPServer() : CTCPServer() {};
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
    for (auto &food: foods_) {
      delete food;
    }
    for (auto &record: records_) {
      delete record;
    }
  }

 private:
  virtual void ServerFunction(void *arg) {
    pthread_t pt;
    pthread_create(&pt, NULL, run_thread, arg);
  }

  static void *run_thread(void *arg) {
    auto tp = (threadPara *) arg;
    int nConnectedSocket = tp->nConnectedSocket;
    auto server = dynamic_cast<CMyTCPServer *>(tp->server);
    //    int nListenSocket = tp->nListenSocket;

    char request[REQUEST_BYTE_MAX];
    std::vector<char *> result;

    while (!(result.size() == 2 && strcmp(result[1], "close") == 0)) {
      if (!result.empty()) {
        // 执行命令
        do_command(nConnectedSocket, result, server);
      }

      // 循环接收命令
      result.clear();
      memset(request, 0, REQUEST_BYTE_MAX);
      if (::read(nConnectedSocket, request, REQUEST_BYTE_MAX) <= 0) {
        break;
      }

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
    ::close(nConnectedSocket);
    return nullptr;
  }

  static bool serialize(SerializableBase *s, class_type type, CMyTCPServer *server) {
    std::string path(server->file_path_);
    std::string server_name(server->server_name_);
    path = path + server_name + "-data";
    FILE *fp = fopen(path.c_str(), "a+");
    if (fp == nullptr) { return false; }
    fwrite(&type, sizeof(int), 1, fp);
    s->serialize(fp);
    fclose(fp);
    return true;
  }

  static void do_command(int nConnectedSocket, std::vector<char *> result, CMyTCPServer *server) {
    // command: getfood
    if (result.size() == 2 && strcmp(result[1], "getfood") == 0) {
      auto info = get_all_food_info(server);
      if (info == "") {
        ::write(nConnectedSocket, "empty store", 11);
      } else {
        ::write(nConnectedSocket, info.c_str(), strlen(info.c_str()));
      }
      return;
    }

    // command: getrecord
    if (result.size() == 2 && strcmp(result[1], "getrecord") == 0) {
      auto info = get_all_record_info(server);
      if (info == "") {
        ::write(nConnectedSocket, "empty record", 12);
      } else {
        ::write(nConnectedSocket, info.c_str(), strlen(info.c_str()));
      }
      return;
    }

    // command: buyfood
    if (result.size() == 4 && strcmp(result[1], "buyfood") == 0) {
      int32_t price = -1;
      int num = atoi(result[3]);
      for (auto &food: server->foods_) {
        if (strcmp(result[2], food->get_name()) == 0) {
          price = num * food->get_price();
          break;
        }
      }
      if (price != -1) {
        Record *r = new Record(result[0], result[2], num, price);
        add_record(r, server);
        std::cout << get_all_record_info(server) << std::endl;
        ::write(nConnectedSocket, "buy success", 11);
      } else {
        ::write(nConnectedSocket, "error command", 13);
      }
      return;
    }

    // command: addfood
    if (result.size() == 4 && strcmp(result[1], "addfood") == 0) {
      int32_t price = atoi(result[3]);
      Food *f = new Food(price, result[2]);
      add_food(f, server);
      std::cout << get_all_food_info(server) << std::endl;
      ::write(nConnectedSocket, "add success", 11);
      return;
    }

    ::write(nConnectedSocket, "error command", 13);
  }

  static void add_food(Food *f, CMyTCPServer *server) {
    server->file_lock_.lock();
    server->foods_.push_back(f);
    // 序列化
    serialize(f, CLASS_FOOD, server);
    server->file_lock_.unlock();
  }

  static void add_record(Record *r, CMyTCPServer *server) {
    server->file_lock_.lock();
    server->records_.push_back(r);
    // 序列化
    serialize(r, CLASS_RECORD, server);
    server->file_lock_.unlock();
  }

 public:
  virtual void deserialize(std::string src_path, std::string dest_path, CTCPServer *new_server) {
    //    new_server->file_lock_.lock(); // 错误 ?
    auto my_server = dynamic_cast<CMyTCPServer *>(new_server);
    std::cout << "src_path: " << src_path.c_str() << std::endl;
    FILE *fp = fopen(src_path.c_str(), "r+");
    class_type nType = CLASS_NONE;
    auto re = fread(&nType, sizeof(int), 1, fp);
    while (re != 0) {
      if (nType == CLASS_FOOD) {
        Food f;
        auto tmp = f.deserialize(fp);
        Food *food = dynamic_cast<Food *>(tmp);
        add_food(food, my_server);
      } else if (nType == CLASS_RECORD) {
        Record r;
        auto tmp = r.deserialize(fp);
        auto record = dynamic_cast<Record *>(tmp);
        add_record(record, my_server);
      }
      re = fread(&nType, sizeof(int), 1, fp);
    }
    fclose(fp);
  };

  static std::string get_all_food_info(CMyTCPServer *server) {
    server->file_lock_.lock();
    std::stringstream ss;
    for (auto &food: server->foods_) {
      ss << food->get_info();
      ss << "\n";
    }
    std::string str = ss.str();
    server->file_lock_.unlock();
    return str;
  }

  static std::string get_all_record_info(CMyTCPServer *server) {
    server->file_lock_.lock();
    std::stringstream ss;
    for (auto &record: server->records_) {
      ss << record->get_info();
      ss << "\n";
    }
    std::string str = ss.str();
    server->file_lock_.unlock();
    return str;
  }

 private:
  std::vector<Food *> foods_;
  std::vector<Record *> records_;
};

