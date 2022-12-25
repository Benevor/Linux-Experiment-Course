//
// Created by 26473 on 2022/12/24.
//

#include "server.h"

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