//
// Created by apricityx on 25-5-27.
//
#include <stdio.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
int in = 0, out = 0;
pthread_mutex_t mutex;
sem_t full, empty;

void init_buffer() {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
}

int insert_item(buffer_item item) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    return 0;
}

int remove_item(buffer_item *item) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return 0;
}
