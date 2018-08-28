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

#include "server.h"

//
// This is Echo Server
//

  using namespace std;

//
// Default constructor
//
Echo_Server::Echo_Server()
{
}

//
// Constructor
//
Echo_Server::Echo_Server(char* ip_address, int port, int num_of_conns)
{
  struct in_addr server_addr;

  if (inet_aton(ip_address, &server_addr) == 0)
  {
    // @TBD Exception to be thrown!

    cout << "TBD: Exception to be thrown!" << endl;
    perror("");
    exit (1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr = server_addr; // in network format

  listener_socket = socket (AF_INET, SOCK_STREAM, 0);

  if (listener_socket < 0)
  {
    // @TBD Exception to be thrown!

    cout << "TBD: Exception to be thrown!" << endl;

    perror ("");
    exit (1);
  }

  if (bind(listener_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    // @TBD Exception to be thrown!

    cout << "TBD: Exception to be thrown!" << endl;

    perror ("");
    exit (1);
  }

  listen (listener_socket, num_of_conns);
}

//
// Destructor
//
Echo_Server::~Echo_Server()
{
  close(listener_socket);

}

//
//
//
int Echo_Server::GetListenerSocket()
{
  return listener_socket;
}

int main(int argc, char *argv[])
{
  const int Number_Of_Connections = 1;

  cout << "TBD: It should be check of CLI parameters!" << endl;
  Echo_Server MyServer(argv[1], atoi(argv[2]), Number_Of_Connections);

  while(1)
  {
    int socket = 0;
    struct sockaddr client_addr;
    socklen_t client_addr_len;
    struct sockaddr_in addr;

    cout << "[Server]: Waiting for the new connection.." << endl;

    socket = accept(MyServer.GetListenerSocket(), &client_addr, &client_addr_len);

    cout << "[Server]: Accept returned socket: " << socket << endl;

    if (socket < 0)
    {
      // @TBD Exception to be thrown!

      cout << "TBD: Exception to be thrown!" << endl;

      perror("");
      exit (1);
    }

    if (getpeername(socket, &client_addr, &client_addr_len) < 0)
    {
      // @TBD Exception to be thrown!

      cout << "TBD: Exception to be thrown!" << endl;

      perror("");
      exit (1);

    }
    struct sockaddr_in *s = (struct sockaddr_in *)&addr;
    int port;
    char ipstr[INET6_ADDRSTRLEN];

    port = ntohs(s->sin_port);
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));
    printf("[Server]: Peer IP address: %s\n", ipstr);

    MyServer.sockets.push_back(socket);

    //
    //
    //
    close(socket);
  }

  return 0;
}







/*  while (1)
  {

  cout << "[Server]: Waiting for the new connection.." << endl;
    sock = accept(MyServer.GetListenerSocket(), &client_addr, &client_addr_len ); //need to improve remote addr and port

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





  int sock;
  int listener;
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


  // Part of consructor, if check is OK.
  listener = socket (AF_INET, SOCK_STREAM, 0);

  if (listener < 0)
  {
    perror ("");
    exit (1);
  }

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
*/
