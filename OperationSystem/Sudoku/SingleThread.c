#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
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
    int base_row = ((grid_num - 1) / 3) * 3;
    int base_col = ((grid_num - 1) % 3) * 3;
    int nums[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nums[i * 3 + j] = sudoku[base_row + i][base_col + j];
        }
    }
    return is_repeat(nums);
}

int check_matrix(int sudoku[9][9]) {
    // 检查行
    if (is_row_repeat(sudoku)) {
        return 0; // 不合法
    }
    // 检查列
    if (is_column_repeat(sudoku)) {
        return 0; // 不合法
    }
    // 检查9个子网格
    for (int i = 1; i <= 9; i++) {
        if (is_subgrid_repeat(sudoku, i)) {
            return 0; // 不合法
        }
    }
    return 1; // 合法
}

int matrix[9][9];

void read_matrix(int file_num) {
    char filename[] = "./puzzles/puzzle-";
    char numberStr[100];
    sprintf(numberStr, "%d", file_num); // 把数字转成字符串
    strcat(filename, numberStr);
    strcat(filename, ".txt");
    // printf("Reading matrix from file: %s\n", filename);
    FILE *file = fopen(filename, "r");
    char text[31];
    fgets(text, sizeof(text), file);
    int ch;
    int line = 0;
    int index = 0;
    int flag = 0;
    while ((ch = fgetc(file)) != EOF) {
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
    fclose(file);
}

int main(void) {
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    gettimeofday(&start_time, NULL);
    read_matrix(1);
    // // print matrix
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    FILE *file = fopen("output.txt", "w"); // 打开文件，"w"表示写模式
    for (int i = 1; i < 1001; i++) {
        read_matrix(i);
        int result = check_matrix(matrix);
        fprintf(file, "%d:%d\n", i, result);
    }
    gettimeofday(&end_time, NULL);

    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    printf("Time taken: %.6f seconds\n", elapsed);
    return 0;
}
