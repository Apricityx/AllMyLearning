#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*外部变量声明*/
extern int x;
extern int y;

int addtwonum() //此处为函数的定义与实现
{
    return x + y;
}

//返回较大值
int max(int a, int b) {
    int n = (a > b) ? a : b;
    return n;
}


//返回平方值
int square(int z) { //此函数的调用在129行
    return z * z;
}

int month() {
    enum months {
        Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
    };
    enum months month;
    int days;
    printf("请输入月份：");
    scanf("%d", &month);

    switch (month) {
        case Jan:
        case Mar:
        case May:
        case Jul:
        case Aug:
        case Oct:
        case Dec:
            days = 31;
            break;

        case Apr:
        case Jun:
        case Sep:
        case Nov:
            days = 30;
            break;

        case Feb:
            days = 28;
            break;

        default:
            printf("输入错误");
            break;
    }
//1-100的偶数相加
    return days;
}

int plus() {
    int i;
    int sum = 0;
    for (i = 2; i <= 100; i += 2) {
        sum = sum + i;
    }
    return sum;
}


void print_file(char filename[]) { //一般“字符串类型”使用指针传参，也可使用数组进行传参，此处使用数组
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }
    printf("\n");

    fclose(file);
}

void input_num() {
    int nums[100];
    int i = 0;
    do {
        printf("请输入第%d个数，以-1结尾：", i + 1);
        scanf("%d", &nums[i]);
        i++;
    } while (nums[i - 1] != -1);
    int sum = 0;
    int max = 0;
    int min = 2147483647;

    //输出
    i = 0;
    while (nums[i] != -1) {
        if (nums[i] > max) {
            max = nums[i];
        }
        if (nums[i] < min) {
            min = nums[i];
        }
        sum = sum + nums[i];
        i++;
    }
    //输出平均数
    float average = (float) sum / i;
    printf("最大值为%d\n", max);
    printf("最小值为%d\n", min);
    printf("总和为%d\n", sum);
    printf("平均值为%.2f\n", average);
};

void HD() {
    printf("请输入学生个数：");
    int n;
    scanf("%d", &n);
    int nums[n];
    int i = 0;
    int sum = 0;
    while (i < n) {
        printf("请输入第%d个学生的成绩：", i + 1);
        scanf("%d", &nums[i]);
        if (nums[i] >= 80) {
            sum = sum + 1;
        }
        i++;
    }
    float rate = (float) sum / n;
    printf("80分以上的学生人数为%d\n", sum);
    printf("HD比率为：%.2f", rate);
};


void bubble_sort(int arr[], int length) {
    int i, j, temp;
    for (i = 0; i < length - 1; i++)
        for (j = 0; j < length - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
};



//每m个求一个平均值

void advanced_average() {
    int arr[100] = {-1};
    int var = 0;
    int count;
    printf("请输入n:");
    scanf("%d", &count);
    int m; //每m个求一个平均值
    printf("请输入m:");
    scanf("%d", &m);
    int group_count = count / m;
    int last_group_element_count = count % m;
    float sum = 0;
    for (int i = 0; i < count; i++) {
        var = var + 3;
        arr[i] = var;
        printf("赋值中，索引为%d的元素为%d\n", i, arr[i]);
    };
    printf("赋值完成\n");

    for (int i = 0; i < group_count; i++) { //i = 0 or 1
        for (int j = 0; j < m; j++) { //j = 0 or 1 or 2 or 3
            sum = sum + arr[m * i + j];
//            printf("索引为%d的元素为%d\n",m*i+j,arr[m*i+j]);
        }
        printf("第%d组的平均数为%.1f\n", i + 1, sum / m);
        sum = 0;
    };
    if (count % m != 0) {
        for (int i = 0; i < last_group_element_count; i++) {
            sum = sum + arr[group_count * m + i];
        };
        printf("最后一组的平均数为%.1f\n", sum / last_group_element_count);
        //思路：规定好要求多少组的平均数，单独求出最后落单那组的平均数
    } else printf("刚好分了%d组\n", group_count);
};


void chickenAndRabbit() {
    int head, foot;
    printf("请输入头的数量：");
    scanf("%d", &head);
    printf("请输入脚的数量：");
    scanf("%d", &foot);
    for (int i = 0; i <= head; i++) { //设i为鸡的数量
        if (i * 4 + (head - i) * 2 == foot) {
            printf("鸡的数量为%d\n", i);
            printf("兔的数量为%d\n", head - i);
            break;
        }
        if (i == head) printf("No answer\n");
    }
};

void charReplace() {
    char result[1000] = {'\0'};
    int i;
    int j = 0;
    char temp[100] = {'\0'};
    while (1) {

        for (int k = 0; k < 100; ++k) temp[k] = '\0';

        printf("请输入数据(输入E结束)：");
        gets(temp);
        if (temp[0] == 'E') break;
        i = 0;
        while (i < 100) {
            //将you替换为we
            if (temp[i] == 'y') {
                if (temp[i + 1] == 'o') {
                    if (temp[i + 2] == 'u') {
                        temp[i] = 'w';
                        temp[i + 1] = 'e';
                        temp[i + 2] = '\0';
                    }
                }
            }
            i = i + 1;
        }

        for (i = 0; i < 100; i++) {
            if (temp[i] != '\0') {
                j = j + 1;
                result[j] = temp[i];
            }
        }

        j = j + 1;
        result[j] = '\n';
    }

    printf("输出结果为：\n");
    for (i = 0; i < 1000; i++) {
        if (result[i] != '\0') {
            printf("%c", result[i]);
        }
    }
}

void character() {
    char result[100][2];
    int j = 0, index = 0;
    int temp = 0;
    int counter[26] = {0};
    char character[26] = {'\0'};
    for (int i = 97; i <= 123; i++) {
        character[i - 97] = i;
    }
    int sign = 0;
    while (1) {
        index = 25;
        temp = 0;

        char str[100];
        printf("请输入一串小写字符(E结束)：");
        gets(str);
        if (str[0] == 'E') break;
        for (int i = 0; i < 100; i++) {
            if (str[i] == '\0') break;
            for (int k = 0; k < 26; k++) {
                if (str[i] == character[k]) {
                    counter[k] = counter[k] + 1;
                }
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (counter[i] > temp) {
                temp = counter[i];
                index = i;
            }

        }
    }
    printf("%c为最多的，出现了%d次", character[index], temp);
}

void qone() {
    int num;
    char character[3] = {'\0'};
    printf("请输入三个字母：");
    scanf("%c%c%c", &character[0], &character[1], &character[2]);
    for (int i = 0; i < 3; i++) {
        num = character[i];
        num = num + 1;
        character[i] = num;
    }
    printf("输入字母的下一位分别为是%c%c%c", character[0], character[1], character[2]);
}

void qtwo() {
    char a = '\0', b = '\0', c = '\0';
    scanf("%c%c%c", &a, &b, &c);
    printf("a=%c b=%c c=%c", a, b, c);
};


void qthree() {
    char a;
    scanf("%c", &a);
    if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'A' || a == 'E' || a == 'I' || a == 'O' ||
        a == 'U') {
        printf("%c是元音字母\n", a);
    } else printf("不是元音字母\nd");
};

void qfour() {
    char original[1000];
    char find[1000] = {'\0'};
    printf("请输入原始数据：");
    gets(original);
    printf("请输入要查找的字符或者字符串：");
    scanf("%s", find);
    int i = 0;
    int count = 0;
    int length = 0, length_count = 0;
    while (find[i] != '\0') {
        i++;
        length++;
    }
    i = 0;

    do {
        if (original[i] == find[0]) {
            for (int j = 0; j < length; ++j) {
                if (original[i + j] == find[j]) {
                    length_count++;
                }
            }
            if (length_count == length) {
                count = i;
                break;
            } else length_count = 0;
        }
        i++;
    } while (original[i] != '\0');

    if (original[i] == '\0') {
        count = -1;
        printf("没找到\n");
    } else printf("数据在第%d位\n", count + 1);


};

void qfive() {
//输入一串数字，将这串数字排序并输出
    char input[30] = {'\0'};
    int result[30] = {-1};
    int i = 0;
    int temp = 0;
    printf("请输入一串数字：");
    gets(input);
    int length = 0;
    i = 0;
    while (input[i] != '\0') {
        length++;
        i++;
    }
    printf("长度为%d\n", length);
    //将char数组转化为int数组
    for (int j = 0; j < length; ++j) {
        result[j] = input[j] - 48;
    }
    printf("转化为int数组后为：");
    for (i = 0; i < length; ++i) {
        printf("%d", result[i]);
    }
    printf("\n");


    //冒泡排序
    for (i = 0; i < length; i++) {
        for (int j = 0; j < length - 1 - i; ++j) {
            if (result[j] > result[j + 1]) {
                temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }

    printf("排序后为：");
    for (i = 0; i < length; i++) {
        printf("%d", result[i]);
    }
}


void sort(int arr[], int length) {
    int temp;
    for (int i = 0; i < length; i++) {
        printf("正在对第%d进行排序\n", arr[i]);
        for (int j = 0; j < length - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
};

void sort_input_arr() {
    printf("请输入数组长度：");
    int length;
    scanf("%d", &length);
    int arr[length];
    int i = 0;
    for (i = 0; i < length; i++) {
        printf("请输入第%d个数：", i + 1);
        scanf("%d", &arr[i]);
    }
    sort(arr, length);
    printf("排序后为：");
    for (i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
};

void MatrixMul() {
    printf("请输入M,N,K");
    int M, N, K;
    scanf("%d%d%d", &M, &N, &K);
    int A[M][N];
    int B[N][K];
    int C[M][K];
    int i, j, k, l, p;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("请输入A[%d][%d]的值：", i, j);
            scanf("%d", &A[i][j]);
            for (l = 0; l < M; l++) {
                for (p = 0; p < K; p++) {
                    printf("%d ", C[l][p]);
                }
                printf("\n");
            }
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < K; j++) {
            printf("请输入B[%d][%d]的值：", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }

    printf("结果为：\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}

//在屏幕上输出完整的九九乘法表
void full_multiplication_table() {
    int i, j;
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            printf("%d*%d=%d\t ", j, i, i * j);
        }
        printf("\n");
    }
}

void half_multiplication_table() {
    int i, j;
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= i; j++) {
            printf("%d*%d=%d\t ", j, i, i * j);
        }
        printf("\n");
    }
}

//打印倒三角

void reverse_multiplication_table() {
    int i, j;
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            if (j >= i) { printf("%d*%d=%d\t", i, j, i * j); }
            else printf("\t");
        }
        printf("\n");
    }
}


void check_num() {
    int i = 0;
    while (i != -1) {
        printf("请输入一个数字：");
        scanf("%d", &i);
        if (i < 10) printf("its one\n");
        else if (i < 100) printf("its two\n");
        else if (i < 1000) printf("its three\n");
        else printf("its other\n");
    }

    printf("输入结束\n");
}

void check_num_switch() {
    int i = 0;
    int j;
    while (i != -1) {
        printf("请输入一个数字：");
        scanf("%d", &i);
        if (i < 10) j = 1;
        else if (i < 100) j = 2;
        else if (i < 1000) j = 3;
        else j = 4;

        switch (j) {
            case 1:
                printf("its one\n");
                break;
            case 2:
                printf("its two\n");
                break;
            case 3:
                printf("its three\n");
                break;
            default:
                printf("its other\n");
                break;
        }
    }
    printf("输入结束\n");
};


//请定义一个 float数组，数组长度为10，数组元素通过初始化给出，请逆序显示数组元素，求数组的最大值，最小值，平均值，求大于平均数的个数，最后按从小到大的顺序排序输出。
void float_array() {
    float arr[10] = {1.2, 3.4, 5.6, 7.8, 9.0, 2.3, 4.5, 6.7, 8.9, 9.1};
    float max = arr[0];
    float min = arr[0];
    float sum = 0;
    float average;
    int count = 0;
    int i, j;
    float temp = -1;
    for (i = 0; i < 10; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
        sum = sum + arr[i];
    }
    average = sum / 10;
    for (i = 0; i < 10; i++) {
        if (arr[i] > average) count++;
    }
    printf("最大值为%.1f\n", max);
    printf("最小值为%.1f\n", min);
    printf("平均值为%.2f\n", average);
    printf("大于平均数的个数为%d\n", count);
    //排序
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 9 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("排序后为：");
    for (i = 0; i < 10; i++) {
        printf("%.1f ", arr[i]);
        sizeof(float);
    }
    printf("\n");
}

void revert() {
    int a[2][3] = {{1, 2, 3},
                   {4, 5, 6}};
    int b[2][3] = {{0, 0},
                   {0, 0}};
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            b[j][i] = a[i][j];
        }
    }

    //输出a
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    //输出
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
}

void array_plus() {
    int a[4][3] = {{1,  2,  3},
                   {4,  5,  6},
                   {7,  8,  9},
                   {10, 11, 12}};
    int sum[4] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            sum[i] = sum[i] + a[i][j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", sum[i]);
    }
}

float get_average(int a[], int length) {
    float sum = 0;
    for (int i = 0; i < length; i++) {
        sum = sum + a[i];
    }
    return sum / length;
};

//已知一个4行3列的二维数组如下，编程 求每行元素的平均值和每列元素的平均值。
void array_average() {
    //行列
    int a[4][3] = {{45, 53, 68},
                   {37, 98, 86},
                   {87, 76, 54},
                   {59, 47, 82}};
    //打印行
    for (int i = 0; i < 4; i++) {
        printf("第%d行的平均值为%.2f\n", i + 1, get_average(a[i], 3));
    }
    //打印列
    for (int i = 0; i < 3; i++) {
        int temp[4] = {0};
        for (int j = 0; j < 4; j++) {
            temp[j] = a[j][i];
        }
        printf("第%d列的平均值为%.2f\n", i + 1, get_average(temp, 4));
    }
}

//判断是否为素数

bool isprime(int num) {
    int flag = 1;
    int i;
    for (i = 2; i < num; i++) {
        if (num % i == 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}

void outprime() {
    int i, flag = 0;
    for (i = 2; i <= 1000; i++) {
        if (isprime(i)) {
            printf("%d\t ", i);
            flag++;
        }
        if (flag == 6) {
            printf("\n");
            flag = 0;
        }
    }
}

void input_tofile() {
    char str[1000];
    char text[1000] = {'\0'};
    while (1) {
        printf("请输入一串字符(END结束输入)：");
        gets(str);
        //在str后面加上\n
        strcat(str, "\n");
        if (str[0] == 'E' && str[1] == 'N' && str[2] == 'D') break;
        strcat(text, str);
    }
    printf("输入结束\n");
    puts(text);
    FILE *file = fopen("../file1.txt", "w"); //此处目录为当前目录
    fputs(text, file);
    fclose(file);
}

//矩阵加法
void matrix_plus() {
    int a[2][3] = {{1, 2, 3},
                   {4, 5, 6}};
    int b[2][3] = {{7,  8,  9},
                   {10, 11, 12}};
    int c[2][3] = {{0, 0, 0},
                   {0, 0, 0}};
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
}


//输出C语言基本数据类型在内存中占用的字节数。基本数据类型包括：不同的整型，不同的浮点型，字符型。（20分）
void assignment1() {
    printf("int类型占用的字节数为%d\n", sizeof(int));
    printf("short类型占用的字节数为%d\n", sizeof(short));
    printf("long类型占用的字节数为%d\n", sizeof(long));
    printf("float类型占用的字节数为%d\n", sizeof(float));
    printf("double类型占用的字节数为%d\n", sizeof(double));
    printf("char类型占用的字节数为%d\n", sizeof(char));
}

//===============================================================
//求和函数：
int sum(int arr[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum = sum + arr[i];
    }
    return sum;
}

//方差函数
float variance(int arr[], int length) {
    float average = (float) sum(arr, length) / length;
    float sum_ = 0;
    for (int i = 0; i < length; i++) {
        sum_ = sum_ + (arr[i] - average) * (arr[i] - average);
    }
    return sum_ / length;
}

//最大值函数
int max_func(int arr[], int length) {
    int max = arr[0];
    for (int i = 0; i < length; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

//最小值函数
int min_func(int arr[], int length) {
    int min = arr[0];
    for (int i = 0; i < length; i++) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

//2.    以你的学号作为一个数字模43，如果结果小于10，则增加10，得到的结果作为一个int型数组的大小。例如，张三的学号是1254， 1254%43 = 7，则数组大小应为size=17。
//设计一个程序：计算数组元素的总和，平均值，方差，最大值，最小值，并且对数组进行从小到大的排序（要求将排序函数单独封装，其他功能写在main中）
void assignment2() {
    int size;
    long long num = 222023321062106;
    if (num % 43 < 10) size = num % 43 + 10;
    else size = num % 43;
    printf("数组大小为%d\n", size);
    srand((unsigned) num); //初始化随机数种子
    int *ptr = (int *) malloc(size * 4); //申请内存
    for (int i = 0; i < size; i++) {
        ptr[i] = rand() % 11 - 5;
    }
    printf("数组为：");
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    int sum_;
    sum_ = sum(ptr, size);
    printf("数组和为%d\n", sum_);
    float variance_;
    variance_ = variance(ptr, size);
    printf("数组方差为%.2f\n", variance_);
    int max_;
    max_ = max_func(ptr, size);
    printf("数组最大值为%d\n", max_);
    int min_;
    min_ = min_func(ptr, size);
    printf("数组最小值为%d\n", min_);
    bubble_sort(ptr, size);
    printf("排序后为：");
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    free(ptr); //释放内存
    ptr = NULL; //防止野指针
}

//=========================================================

//使用File I/O的方式读取test.txt，编程实现以下功能:
//a)	将test.txt中所有的字符逆序打印在屏幕上；
//b)	统计test.txt中字符e出现的次数；
//c)	将test.txt的文字以输出到另一个demo.dat的文件中（30分）

void read_test() {
    FILE *file = fopen("../test.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
    }
    char ch;
    char result[1000] = {'\0'};
    int i = 0;
    while ((ch = fgetc(file)) != EOF) {
        result[i] = ch;
        i++;
    }
    fclose(file);
    //读取完毕，关闭文件

    printf("逆序打印为：");
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", result[j]);
    }
    printf("\n");
    int count = 0;
    for (int j = 0; j < i; j++) {
        if (result[j] == 'e') count++;
    }
    printf("e出现的次数为%d\n", count);

    //写入demo.dat
    file = fopen("../demo.dat", "w");
    fputs(result, file);
    fclose(file);


    for (int j = 0; j <= 100; j++) {
        if (j % 2 == 0) printf("%d", j);
    }
}

void hello() {
    printf("hello world\n");
}


//指针遍历数数组
void pointer_array() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7};
    int *ptr = arr;
    for (int i = 0; i < 10; i++) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");
}


int isNarcissusNumber(int num){
    int ge = num/100%10;
    int shi = num/10%10;
    int bai = num%10;
    if (ge*ge*ge+shi*shi*shi+bai*bai*bai == num) return 1;
    else return 0;
}

void sort1(char *str){
    //插入排序
    int i,j;
    char key;
    for (i=1;i<strlen(str);i++){
        key = str[i];
        j = i-1;
        while (j>=0 && str[j]>key){
            str[j+1] = str[j];
            j--;
        }
        str[j+1] = key;
    }
}

void diamond(int n,char syb){
    n=n/2+1;
    int i=n,j,k;
    int flag;
    while (i>-1){
        if (i==n) i=i-1;
        for (j=0;j<i;j++) printf(" ");
        printf("%c",syb);
        if (i+1!=n){
            for(j=0;j<(n-i)*2-3;j++) printf(" ");
            printf("%c",syb);
        }
        printf("\n");
        i--;
    }
    i=1;
    while (i<n){
        for (j=0;j<i;j++) printf(" ");
        printf("%c",syb);
        if (i+1!=n){
            for(j=0;j<(n-i)*2-3;j++) printf(" ");
            printf("%c",syb);
        }
        printf("\n");
        i++;
    }
}


double mysqrt(double x){
    double low = 0,high = x,mid;
    while (high-low>1e-5){
        mid = (low+high)/2;
        if (mid*mid>x) high = mid;
        else low = mid;
    }
    return mid;
}