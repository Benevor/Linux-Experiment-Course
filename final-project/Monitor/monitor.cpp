//
// Created by 26473 on 2022/12/25.
//

#pragma

#include "server.h"
#include "client.h"

int monitor(int server_port) {
  MonitorClient monitor(server_port, "127.0.0.1");
  monitor.Init();
  monitor.Run(nullptr);
  return -1;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Parameters error" << std::endl;
    return 0;
  }
  std::string src_path;
  int new_server_port = 0;
  int old_server_port = 0;
  std::string new_server_name;
  std::string new_server_host_path;

  if (strcmp(argv[1], "a") == 0) {
    src_path = HOST_A_PATH;
    src_path = src_path + SERVER_A_NAME + "-data";
    new_server_port = SERVER_A_RECOVERY_PORT;
    new_server_name = SERVER_A_NAME;
    new_server_host_path = HOST_B_PATH;
    old_server_port = SERVER_A_PORT;
  } else if (strcmp(argv[1], "b") == 0) {
    src_path = HOST_B_PATH;
    src_path = src_path + SERVER_B_NAME + "-data";
    new_server_port = SERVER_B_RECOVERY_PORT;
    new_server_name = SERVER_B_NAME;
    new_server_host_path = HOST_A_PATH;
    old_server_port = SERVER_B_PORT;
  }
  monitor(old_server_port);

  CMyTCPServer new_server(new_server_port, new_server_name, new_server_host_path);

  new_server.deserialize(src_path, &new_server);
  std::cout << CMyTCPServer::get_all_food_info(&new_server) << std::endl;
  std::cout << CMyTCPServer::get_all_record_info(&new_server) << std::endl;
}