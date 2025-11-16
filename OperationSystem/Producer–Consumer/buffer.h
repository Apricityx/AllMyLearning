#ifndef BUFFER_H
#define BUFFER_H

#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5
typedef int buffer_item;

int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void init_buffer();

extern buffer_item buffer[BUFFER_SIZE];
extern int in, out;
extern pthread_mutex_t mutex;
extern sem_t full, empty;

#endif
