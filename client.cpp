#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "utils.h"

using namespace std;

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in addr;
  struct in_addr server_addr;

  const int socket_buffer_size = 1024;
  char message[] = "Hello, I am Client!\n";
  char buf[socket_buffer_size];

  memset (buf, 0, sizeof(buf));

  if (argc != 2)
  {
    cout << "ip address" << endl;
    exit (1);
  }

  if (inet_aton(argv[1], &server_addr) == 0)
  {
    perror("");
    exit (1);
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0)
  {
    perror("");
    exit (1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons (1234);
  addr.sin_addr = server_addr; // in network format

  if (connect(sock,(struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror ("");
    exit (1);
  }

/*
  char tmp;
  while (1)
  {
    cout << "Sending message to server" << endl;
    cin >> tmp;

    if (tmp == 'x')
    {
      break;
    }

    send(sock, message, sizeof(message), 0);


  }

  recv(sock, buf, socket_buffer_size, 0);

  printf("%s", buf);
*/
  close(sock);

  return 0;
}
