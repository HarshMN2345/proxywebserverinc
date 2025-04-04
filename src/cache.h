#ifndef CACHE_H
#define CACHE_H

#include <pthread.h>
#include <time.h>
#include "common.h"

typedef struct cache_element cache_element;

struct cache_element {
    char* data;
    int len;
    char* url;
    time_t lru_time_track;
    cache_element* next;
};

extern cache_element* head;
extern int cache_size;
extern pthread_mutex_t cache_lock;

void cache_init();
cache_element* find(char* url);
int add_cache_element(char* data, int size, char* url);
void remove_cache_element();

#endif