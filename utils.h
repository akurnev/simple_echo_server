
// returns total bytes sent or -1 in case of error
int sendall(int sockfd, const void* msg, int len, int flags);

// return total bytes recv, 0 - broken connection
int recvall(int sockfd, void* msg, int len, int flags);
