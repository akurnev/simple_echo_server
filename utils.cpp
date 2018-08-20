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

// returns total bytes sent or -1 in case of error
int sendall(int sockfd, const void* msg, int len, int flags)
{
  int total = 0;
  int numBytesSent;

  while (total < len)
  {
    numBytesSent = send(sockfd, (char*)msg + total, len - total, flags);

    if (numBytesSent == -1)
    {
      //all sent
      perror("");
      break;
    }

    total += numBytesSent;
  }

  return (numBytesSent == -1 ? -1 : total);
}

// return total bytes recv, 0 - broken connection
int recvall(int sockfd, void* msg, int len, int flags)
{
  int total = 0;
  int numBytesRecv;
  //const int socket_buffer_size = 1024;
  char buf [len];

  memset (buf, 0, sizeof(buf));

  do
  {
    numBytesRecv = recv(sockfd, buf, len-total, flags);

    if (numBytesRecv == -1)
    {
      //broken connection?
      perror("");
      break;
    }

    if (numBytesRecv == 0)
    {
      cout << "[recvall]: Client closed connection, probably. Need to stop waiting" <<endl;

      break;
    }

    total += numBytesRecv;

    cout << "[recvall]: numBytesRecv = "
        << numBytesRecv << ", total = " << total
        << ", buf = " << buf <<  endl;


    strcat((char*)msg, buf);
    memset (buf, 0, sizeof(buf));

    cout << "[recvall]: Message = "<< (char*)msg << endl;

  } while(total < len);

  return (numBytesRecv == 0 ? 0 : total);
}


/*
  while (total < len)
  {
    numBytesRecv = recv(sockfd, buf, len, flags);

    if (numBytesRecv == 0)
    {
      //broken connection
      perror("");
      break;
    }

    strcat((char*)msg, buf)

    total += numBytesRecv;
  }

*/
