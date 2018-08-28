#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class Echo_Server
{
public:
  Echo_Server();
  ~Echo_Server();
  Echo_Server(char* ip_address, int port, int num_of_conns);

  //
  vector<int> sockets;
  int GetListenerSocket();

private:
  int listener_socket;
  struct sockaddr_in addr;
};
