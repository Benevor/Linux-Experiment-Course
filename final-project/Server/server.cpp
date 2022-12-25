//
// Created by 26473 on 2022/12/24.
//

#include "server.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }

  std::string server_name;
  std::string host_path;

  int server_port;

  if (strcmp(argv[1], "a") == 0) {
    server_name = SERVER_A_NAME;
    server_port = SERVER_A_PORT;
  } else if (strcmp(argv[1], "b") == 0) {
    server_name = SERVER_B_NAME;
    server_port = SERVER_B_PORT;
  } else {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }

  if (strcmp(argv[2], "a") == 0) {
    host_path = HOST_A_PATH;
    if (server_port == SERVER_B_PORT) {
      server_port = SERVER_B_RECOVERY_PORT;
    }
  } else if (strcmp(argv[2], "b") == 0) {
    host_path = HOST_B_PATH;
    if (server_port == SERVER_A_PORT) {
      server_port = SERVER_A_RECOVERY_PORT;
    }
  } else {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }

  CMyTCPServer my_server(server_port, server_name, host_path);
  my_server.Run();
  return 0;
}