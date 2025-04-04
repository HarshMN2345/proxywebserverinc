#include "handler.h"
#include "common.h"
#include "cache.h"
#include "request_handler.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

extern sem_t seamaphore;

void* thread_fn(void* socketNew) {
    sem_wait(&seamaphore);
    int clientSocket = *(int*)socketNew;
    // Client handling logic here
    sem_post(&seamaphore);
    return NULL;
}