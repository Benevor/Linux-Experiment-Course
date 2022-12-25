//
// Created by 26473 on 2022/12/24.
//

#include "client.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }
  int server_port = 0;

  if (strcmp(argv[1], "a") == 0) {
    server_port = SERVER_A_PORT;
  } else if (strcmp(argv[1], "b") == 0) {
    server_port = SERVER_B_PORT;
  } else if (strcmp(argv[1], "ar") == 0) {
    server_port = SERVER_A_RECOVERY_PORT;
  } else if (strcmp(argv[1], "br") == 0) {
    server_port = SERVER_B_RECOVERY_PORT;
  }

  CMyTCPClient client(server_port, "127.0.0.1");
  client.Init();

  std::cout << "Please enter your user name: ";
  std::cin >> client.user_name_;

  char command[50];
  std::cout << "Please enter your command: ";
  std::cin >> command;
  while (true) {
    auto re = client.Run(command);
    if (re != 0) {
      break;
    }
    std::cout << "Please enter your command: ";
    std::cin >> command;
  }

  client.Close();

  return 0;
}
