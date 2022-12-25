//
// Created by 26473 on 2022/12/25.
//

#include "client.h"

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
