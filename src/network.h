#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>

int connectRemoteServer(char* host_addr, int port_num);
int sendErrorMessage(int socket, int status_code);

#endif