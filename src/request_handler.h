#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "proxy_parse.h"
#include "network.h"

int handle_request(int clientSocket, ParsedRequest* request, char* tempReq);
int checkHTTPversion(char* msg);

#endif