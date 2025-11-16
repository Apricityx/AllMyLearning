#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_THREADS 16

FILE *file;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int is_repeat(const int *nums) {
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (nums[i] == nums[j]) {
                return 1; // 有重复
            }
        }
    }
    return 0; // 没有重复
}

int is_row_repeat(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        if (is_repeat(sudoku[i])) {
            return 1; // 有重复
        }
    }
    return 0;
}

int is_column_repeat(int sudoku[9][9]) {
    for (int j = 0; j < 9; j++) {
        int column[9];
        for (int i = 0; i < 9; i++) {
            column[i] = sudoku[i][j];
        }
        if (is_repeat(column)) {
            return 1;
        }
    }
    return 0;
}

int is_subgrid_repeat(int sudoku[9][9], int grid_num) {
    const int base_row = ((grid_num - 1) / 3) * 3;
    const int base_col = ((grid_num - 1) % 3) * 3;
    int nums[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nums[i * 3 + j] = sudoku[base_row + i][base_col + j];
        }
    }
    return is_repeat(nums);
}

int check_matrix(int sudoku[9][9]) {
    if (is_row_repeat(sudoku)) {
        return 0; // 不合法
    }
    if (is_column_repeat(sudoku)) {
        return 0; // 不合法
    }
    for (int i = 1; i <= 9; i++) {
        if (is_subgrid_repeat(sudoku, i)) {
            return 0; // 不合法
        }
    }
    return 1; // 合法
}

void read_matrix_to(int file_num, int matrix[9][9]) {
    char filename[] = "./puzzles/puzzle-";
    char numberStr[100];
    sprintf(numberStr, "%d", file_num);
    strcat(filename, numberStr);
    strcat(filename, ".txt");
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Cannot open file %s\n", filename);
        return;
    }
    char text[31];
    fgets(text, sizeof(text), f);
    int ch;
    int line = 0;
    int index = 0;
    int flag = 0;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '-') {
            flag = 1;
            continue;
        }
        if (flag) {
            flag = 0;
            continue;
        }
        if (ch >= '1' && ch <= '9') {
            matrix[line][index] = ch - '0';
            index++;
        } else if (ch == '\n') {
            line++;
            index = 0;
        }
    }
    fclose(f);
}

typedef struct {
    int start;
    int end;
} ThreadData;

void *check_sudoku_range(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start = data->start;
    int end = data->end;
    int local_matrix[9][9];
    for (int i = start; i <= end; i++) {
        read_matrix_to(i, local_matrix);
        int result = check_matrix(local_matrix);
        pthread_mutex_lock(&mutex);
        fprintf(file, "%d:%d\n", i, result);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

