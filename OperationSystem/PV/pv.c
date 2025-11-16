#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/pthreadtypes.h>
#include <time.h>
#include <unistd.h>

/// 学生编程并问问题：
void *student_process() {
    /// 编程（随机等待）
    const int wait_time = rand() % 5 + 1;
    sleep(wait_time);
    /// 问问题

    return NULL;
}


/// 助教睡觉并回答问题：
void *ta_process() {
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, student_process, NULL);
    pthread_join(tid, NULL);

    return 0;
}
