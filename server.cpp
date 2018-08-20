#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "utils.h"
#include <string.h>

//
// This is Echo Server
//

using namespace std;

int main(int argc, char *argv[])
{
  int sock;
  int listener;
  struct sockaddr_in addr;
  const int socket_buffer_size = 64;
  char buf[socket_buffer_size];

  int bytes_sent = 0;
  int bytes_read = 0;

  struct in_addr server_addr;

  struct sockaddr client_addr;
  socklen_t client_addr_len;

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

  listener = socket (AF_INET, SOCK_STREAM, 0);

  if (listener < 0)
  {
    perror ("");
    exit (1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr = server_addr; // in network format

  if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror ("");
    exit (1);
  }

  listen (listener, 1);

  while (1)
  {
    cout << "[Server]: Waiting for the new connection.." << endl;

    sock = accept(listener, &client_addr, &client_addr_len ); //need to improve remote addr and port

    cout << "[Server]: Accept returned sock: " << sock << endl;

    if (sock < 0)
    {
      perror("");
      exit (1);
    }

    //sock = accept(listener, NULL, NULL ); //need to improve remote addr and port

    if (getpeername(sock, &client_addr, &client_addr_len) < 0)
    {
      perror("");
      exit (1);

    }
    struct sockaddr_in *s = (struct sockaddr_in *)&addr;
    int port;
    char ipstr[INET6_ADDRSTRLEN];

    port = ntohs(s->sin_port);
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));
    printf("Peer IP address: %s\n", ipstr);

    while (1)
    {
      bytes_read = recvall (sock, buf, socket_buffer_size, 0);
      cout << "[Server]: Bytes read: " << bytes_read << endl;

      if (bytes_read <= 0)
      {
        break;
      }
      cout << "Message from Client: " << buf << endl;

      bytes_sent = send (sock, buf, bytes_read, 0);
      cout << "[Server]: Bytes sent: " << bytes_sent << endl;

      memset(buf, 0, sizeof(buf));
    }

    close (sock);

  }

  close (listener);

  return 0;
}
