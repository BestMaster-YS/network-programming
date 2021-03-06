// 服务端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <headers/common.h>

int main(int argc, char *argv[])
{
  int server_socket;
  int client_socket;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  socklen_t client_addr_size;

  char message[] = "hello world!";

  if (argc != 2)
  {
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }

  // PF_INET 选择 IP 协议
  server_socket = socket(PF_INET, SOCK_STREAM, 0);

  if (server_socket == -1)
    error_handling("socket() error");

  memset(&server_addr, 0, sizeof(server_addr));

  // IP 地址族
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(argv[1]));

  if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    error_handling("bind() error");

  if (listen(server_socket, 5) == -1)
    error_handling("listen() error");

  client_addr_size = sizeof(client_addr);
  for (int i = 0; i < 2; ++i)
  {
    client_socket = accept(server_socket, (struct sockaddr *)&client_socket, &client_addr_size);

    if (client_socket == -1)
      error_handling("accept() error");
    ssize_t size1 = write(client_socket, message, sizeof(message));
    ssize_t size2 = write(client_socket, message, sizeof(message));
    if (size1 <= 0 || size2 <= 0)
    {
      printf("write error!\n");
    }
    printf("finished client connect.\n");
  }

  close(client_socket);
  close(server_socket);

  return 0;
}
