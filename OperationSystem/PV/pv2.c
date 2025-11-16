#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_STUDENTS 5
#define MAX_CHAIRS 3

sem_t mutex;
sem_t chairs_sem;
sem_t ta_sleep;
sem_t helped;

void* student_thread(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sleep(rand() % 5 + 1);
        printf("Student %d: need help\n", id);

        sem_wait(&mutex);
        int val;
        sem_getvalue(&chairs_sem, &val);
        if (val > 0) {
            sem_wait(&chairs_sem);
            printf("Student %d: wait TA\n", id);
            sem_post(&ta_sleep);
            sem_post(&mutex);

            sem_wait(&helped);
            printf("Student %d: leave\n", id);
            sem_post(&chairs_sem);
        } else {
            sem_post(&mutex);
            printf("Student %d: no empty chiars\n", id);
        }
    }
    return NULL;
}

void* ta_thread(void* arg) {
    while (1) {
        sem_wait(&ta_sleep);
        printf("TA: Wake up\n");

        // 模拟帮助过程
        sleep(rand() % 3 + 1);
        printf("TA: Sleeping\n");
        sem_post(&helped);
    }
    return NULL;
}

int main() {
    pthread_t students[NUM_STUDENTS], ta;
    int ids[NUM_STUDENTS];

    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&chairs_sem, 0, MAX_CHAIRS);
    sem_init(&ta_sleep, 0, 0);
    sem_init(&helped, 0, 0);

    pthread_create(&ta, NULL, ta_thread, NULL);

    for (int i = 0; i < NUM_STUDENTS; ++i) {
        ids[i] = i + 1;
        pthread_create(&students[i], NULL, student_thread, &ids[i]);
    }

    pthread_join(ta, NULL);
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        pthread_join(students[i], NULL);
    }

    return 0;
}
