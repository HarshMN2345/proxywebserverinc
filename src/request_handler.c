#include "request_handler.h"
#include "common.h"
#include "cache.h"
#include <stdio.h>
#include "proxy_parse.h" 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int checkHTTPversion(char* msg) {
    if (strncmp(msg, "HTTP/1.1", 8) == 0 || strncmp(msg, "HTTP/1.0", 8) == 0) return 1;
    return -1;
}

int handle_request(int clientSocket, ParsedRequest* request, char* tempReq) {
    char* buffer = (char*)malloc(MAX_BYTES);
    snprintf(buffer, MAX_BYTES, "GET %s %s\r\n", request->path, request->version);
    // Additional header processing and remote server communication
    free(buffer);
    return 0;
}