#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

cache_element* head = NULL;
int cache_size = 0;
pthread_mutex_t cache_lock;

void cache_init() {
    pthread_mutex_init(&cache_lock, NULL);
}

cache_element* find(char* url) {
    cache_element* site = NULL;
    pthread_mutex_lock(&cache_lock);
    if (head != NULL) {
        site = head;
        while (site != NULL) {
            if (strcmp(site->url, url) == 0) {
                site->lru_time_track = time(NULL);
                break;
            }
            site = site->next;
        }
    }
    pthread_mutex_unlock(&cache_lock);
    return site;
}

int add_cache_element(char* data, int size, char* url) {
    pthread_mutex_lock(&cache_lock);
    int element_size = size + strlen(url) + sizeof(cache_element);
    if (element_size > MAX_ELEMENT_SIZE) {
        pthread_mutex_unlock(&cache_lock);
        return 0;
    }
    while (cache_size + element_size > MAX_SIZE) {
        remove_cache_element();
    }
    cache_element* element = (cache_element*)malloc(sizeof(cache_element));
    element->data = strdup(data);
    element->url = strdup(url);
    element->len = size;
    element->lru_time_track = time(NULL);
    element->next = head;
    head = element;
    cache_size += element_size;
    pthread_mutex_unlock(&cache_lock);
    return 1;
}

void remove_cache_element() {
    pthread_mutex_lock(&cache_lock);
    if (head == NULL) {
        pthread_mutex_unlock(&cache_lock);
        return;
    }
    cache_element *prev = NULL, *curr = head, *oldest = head, *prev_oldest = NULL;
    time_t oldest_time = head->lru_time_track;
    while (curr != NULL) {
        if (curr->lru_time_track < oldest_time) {
            oldest = curr;
            oldest_time = curr->lru_time_track;
            prev_oldest = prev;
        }
        prev = curr;
        curr = curr->next;
    }
    if (prev_oldest == NULL) {
        head = head->next;
    } else {
        prev_oldest->next = oldest->next;
    }
    cache_size -= (oldest->len + sizeof(cache_element) + strlen(oldest->url));
    free(oldest->data);
    free(oldest->url);
    free(oldest);
    pthread_mutex_unlock(&cache_lock);
}