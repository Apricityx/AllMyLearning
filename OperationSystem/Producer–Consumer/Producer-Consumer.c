#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "buffer.h"

void *producer(void *param);
void *consumer(void *param);

int min_delay = 1, max_delay = 3;
int main() {
    int run_time = 1000;
    int num_producers = 35;
    int num_consumers = 15;

    init_buffer();

    pthread_t producers[num_producers], consumers[num_consumers];

    for (int i = 0; i < num_producers; ++i)
        pthread_create(&producers[i], NULL, producer, NULL);
    for (int i = 0; i < num_consumers; ++i)
        pthread_create(&consumers[i], NULL, consumer, NULL);

    sleep(run_time);

    printf("Main thread exiting.\n");
    return 0;
}

void *producer(void *param) {
    while (1) {
        sleep(rand() % (max_delay - min_delay + 1) + min_delay);
        int item = rand() % 100;
        insert_item(item);
        printf("Producer produced: %d\n", item);
    }
}


void *consumer(void *param) {
    while (1) {
        sleep(rand() % 3);
        int item;
        remove_item(&item);
        printf("Consumer consumed: %d\n", item);
    }
}
