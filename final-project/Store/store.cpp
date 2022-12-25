//
// Created by 26473 on 2022/12/25.
//

#include "client.h"

int main(int argc, char **argv) {
  // 初始化
  CMyTCPClient client(0, "127.0.0.1");
  int server_port = 0;

  std::cout << "Please enter your user name: ";
  std::cin >> client.user_name_;

  int connected = -1;
  while (connected == -1) {
    std::cout << "Please choose your server (a/b/ar/br): ";
    std::cin >> client.server_name_;

    if (strcmp(client.server_name_, "a") == 0) {
      server_port = SERVER_A_PORT;
    } else if (strcmp(client.server_name_, "b") == 0) {
      server_port = SERVER_B_PORT;
    } else if (strcmp(client.server_name_, "ar") == 0) {
      server_port = SERVER_A_RECOVERY_PORT;
    } else if (strcmp(client.server_name_, "br") == 0) {
      server_port = SERVER_B_RECOVERY_PORT;
    }

    connected = client.ReConnect(server_port);
  }
  std::cout << "connected to port " << server_port << " successfully" << std::endl;

  // 循环执行命令
  char command[50];
  bool need_run = true;
  std::cout << "Please enter your command: ";
  std::cin >> command;
  while (true) {
    if (strcmp(command, "recona") == 0) {
      server_port = SERVER_A_PORT;
      need_run = false;
    } else if (strcmp(command, "reconb") == 0) {
      server_port = SERVER_B_PORT;
      need_run = false;
    } else if (strcmp(command, "reconar") == 0) {
      server_port = SERVER_A_RECOVERY_PORT;
      need_run = false;
    } else if (strcmp(command, "reconbr") == 0) {
      server_port = SERVER_B_RECOVERY_PORT;
      need_run = false;
    }
    if (need_run) {
      auto re = client.Run(command);
      if (re != 0) {
        break;
      }
    } else {
      need_run = true;
      connected = client.ReConnect(server_port);
      if (connected != -1) {
        std::cout << "connected to port " << server_port << " successfully" << std::endl;
      }
    }
    std::cout << "Please enter your command: ";
    std::cin >> command;
  }

  client.Close();

  return 0;
}
