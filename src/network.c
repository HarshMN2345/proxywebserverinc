#include "network.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

int sendErrorMessage(int socket, int status_code) {
    char str[1024];
    char currentTime[50];
    time_t now = time(0);
    struct tm* data = gmtime(&now);
    strftime(currentTime, sizeof(currentTime), "%a, %d %b %Y %H:%M:%S %Z", data);

    const char* response;
    switch(status_code) {
        case 400: response = "HTTP/1.1 400 Bad Request\r\n..."; break;
        case 403: response = "HTTP/1.1 403 Forbidden\r\n..."; break;
        case 404: response = "HTTP/1.1 404 Not Found\r\n..."; break;
        case 500: response = "HTTP/1.1 500 Internal Server Error\r\n..."; break;
        case 501: response = "HTTP/1.1 501 Not Implemented\r\n..."; break;
        case 505: response = "HTTP/1.1 505 HTTP Version Not Supported\r\n..."; break;
        default: return -1;
    }
    return send(socket, response, strlen(response), 0);
}

int connectRemoteServer(char* host_addr, int port_num) {
    int remoteSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (remoteSocket < 0) return -1;

    struct hostent* host = gethostbyname(host_addr);
    if (!host) { close(remoteSocket); return -1; }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    memcpy(&server_addr.sin_addr.s_addr, host->h_addr, host->h_length);

    if (connect(remoteSocket, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
        close(remoteSocket); return -1;
    }
    return remoteSocket;
}