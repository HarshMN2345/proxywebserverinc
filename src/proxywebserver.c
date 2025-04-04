#include "common.h"
#include "cache.h"
#include "network.h"
#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>

int port_number = 8080;
int proxy_socketId;
pthread_t tid[MAX_CLIENTS];
sem_t seamaphore;

int main(int argc, char* argv[]) {
    cache_init();
    sem_init(&seamaphore, 0, MAX_CLIENTS);
    // Server setup and loop
    return 0;
}