#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h> //引入bool类型
#include <stdlib.h> //  ; 解决中文乱码问题
#include <string.h> //引入字符串操作函数
#define S(a) a*a;
double mysqrt(double x);
void diamond(int n,char syb);
void sort1(char *str);
void read_test();

bool isprime(int num);
void assignment1();
void assignment2();
void matrix_plus();
void input_tofile();
void outprime();
void array_average();
void array_plus();
void revert();
void float_array();
void check_num();
void check_num_switch();
void full_multiplication_table();
void half_multiplication_table();
void reverse_multiplication_table();
void MatrixMul();
void sort_input_arr();
void qfour();
void qfive();
void qthree();
void qtwo();
void qone();
void character();
void charReplace();
void replace();
void chickenAndRabbit();
void advanced_average();
void bubble_sort(int*,int);
void input_num();
void HD();
int isNarcissusNumber(int num);
extern void print_file();
extern int plus();
//这里的addtwonum函数是在main函数之后定义的，所以需要在main函数之前声明一下
//此函数的使用在第41行
extern int addtwonum(); //声明一个函数，其返回值为整型，函数名为addtwonum，参数为空，若不声明，调用时会报错
//声明仅仅是声明，不会占用存储空间
//C语言的函数调用主要是从存储出发，而不是从文件出发
//实现函数，此函数是外部函数，只能在main外部定义
extern int square(int z); //此函数的调用在129行
extern int max(int,int); //此处可以将变量简写，具体局部变量名将在实现中定义
extern int month();
//即使函数在main函数后或者在其他文件中有实现的代码，在main函数前也必须声明函数，否则无法调用
//此处可以声明全局变量
int x=1;
int y=20;
//此处的xy需要在main函数之前声明，否则会报错，因为需要让xy为全局变量，才能被其他的C文件引用
float null; //全局变量会被自动初始化为0，而局部变量不会

void function1(int i){
    printf("调用了函数function1,传参为%d\n",i);
}

void function2(int i){
    printf("调用了函数function2,传参为%d\n",i);
}


int main() { //此处的int表示main函数的返回值为整型
    system("chcp 65001"); // 解决中文乱码问题
    bool buer = true;
    if (buer) {
        printf("buer的值为true\n");
    }


    printf("Hello, World!\n");
    int a = 1;
    int b = 2;
    int c = a + b;
    printf("c = %d\n", c);
    printf("数据类型为： %llu\n", sizeof(c));



    //C中的数据转换
    //1.隐形自动转换
    int i = 10;
    float f = 3.14;
    double d = i + f; // 隐式将int类型转换为double类型
    printf("d = %f\n", d);

    //输入使用scanf函数

    int p = 1;
    //scanf("%d", &p);
    printf("p = %d\n", p);
    printf("p的数据类型为：%llu \n", sizeof(p));


    //引用外部函数
    int result;
    result = addtwonum();
    printf("外部函数result = %d\n", result);


#define PI 3.141592653589 //定义一个常量
    printf("%lf", PI);
    const int var = 10;
//const int var = 10; //定义常量
//define和const得到的结果基本一致，但最好使用const，const能捕获一些意外的问题


//存储类
    //register类
    register int miles = 10; //定义寄存器变量，寄存器变量只能定义在函数内部，不能定义在函数外部
    printf("\n寄存器中miles的值为%d，需要多次访问的变量存储在寄存器中，寄存器的读写速度很快", miles);

    //static类
    static int count = 10;
    printf("\nstatic类的count的值为%d\n", count);
    //没整明白，以后看

    //extern类
    extern int x;
    x = 10;
    //仅声明不定义，只是告诉编译器这个变量在别的文件中，不要报错。此方式不会分配内存。

    //++a和a++区别
    //a++是先返回a再给a赋值，++a是先给a赋值再返回a
    int a1 = 1;
    int b1 = a1++;
    printf("%d\n", b1); //此处可以看出，b1被赋值为a++之前a的值
    printf("%d\n", a1); //a1自增1

    int a2 = 1;
    int b2 = ++a2;
    printf("%d\n", b2); //此处可以看出，b2被赋值为++a之后a的值
    printf("%d\n", a2); //a2自增1

    //得出结论：a++先返回a再自增，++a先自增再返回a


    //?:三目运算符 表现形式为：表达式1 ? 表达式2 : 表达式3
    int aa1 = 15;
    int bb1 = (aa1 == 10) ? 10 : 20;//此处为三目运算符，相当于简写的if else语句
    printf("%d\n", bb1);

    //(a == 1)?a = 2 :a = 3; 这行代码是错误的，因为三目运算符不能赋值
    a = 2;
    (a == 1) ? printf("a的值为1\n") : printf("a的值不为1\n"); //此处为三目运算符，相当于简写的if else语句





    //switch语句
    //switch语句中的case后面的值必须是常量，不能是变量，也不能是表达式
    switch (aa1) {
        case 0 ... 10 :
            printf("aa1的值在0到10之间\n");
            break;
        case 11 ... 20 :
            printf("aa1的值在11到20之间\n");
            break;
        case 21 ... 30 :
            printf("aa1的值在21到30之间\n");
            break;
        default:
            break;
    }


    //循环控制

    for (int i = 0; i <= 10; i++) {
        if (i == 5) {
            continue; //跳过本次循环
        }
        printf("i = %d\n", i);
    }
    //从以上可以看出，continue跳过了i=5时候的循环
    //且C与py不同的一点是py中在for里对i进行操作后，下一次循环i的值会被重新赋值，而C中不会，i的值会在循环体中被改变

    a = 5;
    a = square(a);
    printf("a = %d\n", a);

    //do...while循环
    a = -1;
    do {
        printf("do while:a = %d\n", a);
        if (a == -1) {
            a = 10;
        }
        a--;
    } while (a > 0);
    //与while不同的是，do...while会先执行一次循环体，再判断条件是否成立，而while则是先判断条件是否成立，再执行循环体，可由do while先输出一次a=-1看出
    //故do while至少会执行一次循环体
    a = 10;
    while (a > 0) {
        printf("while:a = %d\n", a);
        a--;
    }

    a = max(2, 3);
    printf("a = %d\n", a);
    //局部变量会被优先使用
    x = 10;
    y = 20;
    printf("x + y = %d\n", x + y);
    printf("%f\n", null); //全局变量被初始化


    //数组
    int balance[5] = {1, 2, 3, 4, 5,}; //定义数组

    printf("balance[0] = %d\n", balance[0]); //输出索引为0的数组
    printf("输出数组为：%s", balance);
    //尝试给数组赋值

    balance[0] = 10;
    printf("balance[0] = %d\n", balance[0]); //再次输出索引为0的数组
    //得出结论：数组可以被赋值

    //输出数组长度
    printf("数组长度为: %llu",
           sizeof(balance) / sizeof(balance[5])); //获取长度的核心思想为：数组所占内存空间/数组中一个元素所占内存空间，sizeof函数的作用就是输出这个对象的内存占用
    printf("该数组占用内存为 %llu\n", sizeof(balance)); //sizeof的返回值类型为长整型

    //遍历打印数组
    int length = sizeof(balance) / sizeof(balance[0]);
    for (i = 0; i < length; i++) {
        printf("balance[%d] = %d\n", i, balance[i]);
    }


    //枚举类型

    enum color {
        red = 1, //索引为0的元素默认为0，这里指定为1
        green,   //后续元素默认依次加1
        blue
    }; //定义枚举类型

    enum color favorite_color; //定义枚举类型变量
    printf("favorite_color = %d\n", favorite_color); //输出枚举类型变量

    //遍历输出枚举类型; C语言中无法真正意义上的遍历一个枚举类型，若枚举类型不是连续的，那么就没有办法遍历
    for (i = red; i <= blue; i++) {
        printf("color = %d\n", i);
    }

/*    scanf("%u",&favorite_color); //switch语句中，若一个case为真且代码块中不含有break的时候，将继续执行下面的流程
    switch (favorite_color) {
        case red:
            printf("红色");
            break;
        case green:
            printf("绿色");
            break;
        case blue:
            printf("蓝色");
            break;
    }
*/

    //printf("结果是：%d\n",month());

    //指针

    int var1 = 10;
    int *pointer = NULL; //定义指针变量，指针的类型必须与var1一致，实质是16进制数，指向内存地址。初始化的时候最好指定为空指针
    pointer = &var1;
    printf("%p\n", pointer); //打印出var1的内存地址

    //检查空指针
    if (pointer) {
        printf("该指针为空\n");
    }


    //使用指针来遍历
    //数组的内存地址是连续的
    int var2[] = {10, 20, 30};
    int *ptr;//指针
    ptr = var2; //没有&符号，因为数组名就是内存地址
    for (int i = 0; i < 3; ++i) {
        printf("存储地址：var[%d] %p\n", i, ptr); //ptr为内存地址
        printf("存储值：var[%d] = %d\n", i, *ptr); //*ptr为原始值
        ptr++; //下一位地址
    }


    int var4 = 10;
    long long var3 = 10;
    int *pointer3 = &var3;
    int *pointer4 = &var4;

    printf("var3 占用内存空间为%llu\n", sizeof(var3));
    printf("var3的地址是%p\n", pointer3);
    pointer3++;
    printf("var3的地址是%p\n", pointer3);
    //000000485ffff7d0-000000485ffff7d8为var3所占用的空间
    printf("var4的地址是%p\n", pointer4);
    //分配原则：尽量连续

    printf("Hel%llu\n", &pointer3);

    printf("100以内的偶数和为:%d\n", plus());
    print_file("D:\\Desktop\\WorkPlace\\C\\text.txt");


    //函数指针
    int (*pointer_function)(int, int) = &max; //定义函数指针，函数指针的类型为返回值类型为int，参数为int,int的函数
    //返回值 (*指针名)(函数的参数类型1,函数的参数类型2,...);

    printf("函数指针的值为:%d\n", pointer_function(1, 2)); //调用函数指针
    //函数指针的调用方式与函数调用方式相同，只是将函数名换成了函数指针名
    //函数指针的作用：可以将函数作为参数传递给另一个函数


    int (*pointer_plus)() = &plus;
    printf("大的那个数为%d\n", max(1, plus()));
    printf("大的那个数为%d\n", max(1, pointer_plus()));
    //上面是两种调用函数plus()的方式

//    char str[100]; //定义一个字符数组，用来存储用户输入的字符串
//    printf("请输入一段字符串：\n"); //提示用户输入
//    scanf("%s", str); //读取用户输入的字符串，存入str数组
//    printf("你输入的字符串是：%s\n", str); //输出用户输入的字符串

    //回调函数
    //回调函数的核心思想是，未指定一个函数的具体实现，而是在需要的时候再指定具体的实现，一般使用函数指针来确定需要调用哪一个函数
    //下面是一个简单的实现


    void (*function_used)(int) = NULL;
    printf("请输入1或2+需要的参数：");
    a = 1;
    b = 2;
    //    scanf("%d %d",&a,&b);
    printf("\n");
    if (a == 1) {
        function_used = &function1;
    } else if (a == 2) {
        function_used = &function2;
    } else {
        printf("输入错误");
    }
    function_used(b);

    //字符串 （字符数组）
    char str1[6] = {'H', 'e', 'l', 'l', '0', '\0'};
    //根据数组初始化规则，也可以写作：
    char str2[] = "你好";
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    printf("str2的长度为：%llu\n", sizeof(str2)); //可以看出，此处输出为7，说明这里汉字使用了UTF-8编码，一个汉字占用3个字节，加上最后的\0，共占用7个字节

//    input_num();
//    HD();

    //C语言中，字符串通过字符数组的方式存储，数组的最后一个元素为\0，表示字符串的结束
    //当打印字符类型数组时，将会自动遍历打印出数组中的所有元素，直到遇到\0为止
    char str3[] = {'H', 'e', 'l', 'l', 'o', '\0', 'h', 'i', 'd', 'd', 'e', 'n'};
    printf("str3 = %s\n", str3); //此处输出为Hello，因为遇到\0就停止了


    char strarr1[] = "Hello";
    char strarr2[] = "World";
    strcpy(strarr1, strarr2);
    //C语言中常用的操作字符串的函数：
    printf("复制后的数组为%s\n", strarr1); //将str2复制给str1，与其说是复制，不如说是将str2的值赋值给str1
    strcpy(strarr1, "Hello");


    strcat(strarr1, strarr2);
    printf("连接后的数组为%s\n", strarr1);
    printf("数组strarr1的长度为%llu\n", strlen(strarr1)); //strlen函数用来获取字符串的长度，不包括\0

    //C语言中的结构体
    //结构体和字典非常相似，都是用来存储多个数据的
    //结构体和字典的区别在于，结构体中的元素是有序的，而字典中的元素是无序的

    struct Books {
        char title[50];
        char author[50];
        char subject[100];
        int book_id;
    }
            book1 = {"C语言", "张三", "编程", 0},
            book2 = {"疯狂JAVA讲义", "李四", "编程",2}; //定义结构体变量的同时进行初始化，这里的顺序即为Books中结构体变量的顺序

    printf("%s:\n信息\n作者:%s\n主题:%s\n编号:000%d\n", book1.title, book1.author, book1.subject, book1.book_id);
    printf("%s:\n信息\n作者:%s\n主题:%s\n编号:000%d\n", book2.title, book2.author, book2.subject, book2.book_id);

//共用体
//共用体与结构体类似，但是共用体中的所有元素共用一块内存空间，共用体的大小为最大的元素的大小

union Data {
        int i;
        float f[20];
        char str[9999];
    } data;
    printf("共用体大小为%llu\n",sizeof data);

union Data2{
    int i;
    float f[20];
    char str[999];
} data2;
    printf("共用体大小为%llu\n",sizeof data2);
    //共用体的形式可以极大的节省内存空间
    //共用体共用一块内存，所以对一个元素进行操作的时候有可能会影响到其他元素，这就意味着不能同时对多个元素进行操作，否则会出问题
    //从这里可以看出，共用体的大小为最大的元素的大小


    //typedef 没什么用的表达式，可以用来给数据类型起别名
    typedef int standard;
    standard a5 = 10;
    printf("a5 = %llu\n",sizeof a5);
    //typedef和#define的区别在于，typedef是在编译器编译的时候进行替换，而#define是在预编译的时候进行替换
    //指针练习
//    p是一个指针变量的名字，表示此指针变量指向的内存地址，如果使用%p来输出的话，它将是一个16进制数。
//    *p表示此指针指向的内存地址中存放的内容，一般是一个和指针类型一致的变量或者常量。
//    &是取地址运算符，&p就是取指针p的地址，&p就表示编译器为变量p分配的内存地址，而因为p是一个指针变量，这种特殊的身份注定了它要指向另外一个内存地址，程序员按照程序的需要让它指向一个内存地址，这个它指向的内存地址就用p表示
    char text[60] = "abcdef";
    char* p1 = text; //*p1指向text的首地址
    printf("指针练习\n");
    printf("%s,",p1);
    printf("%llu\n",sizeof(p1)); //此处输出为8，因为char*类型的指针占用8个字节

    printf("%s,",p1+1); //p1+1指向text的第二个元素,输出为bcdef,可以看出输出了第二个元素以及后面的所有元素
    printf("%llu\n",sizeof(p1 + 1));

    printf("%c,",*p1); //此处输出为a
    printf("%llu\n",sizeof(*p1)); //此处输出为1，因为char类型的数据占用一个字节

    printf("%c\n",(p1+1)[0]); //p1+1输出为原字符串去掉a，所以第0位为b

    printf("%p\n",&p1); //输出p1的地址
    printf("%p\n",&text); //输出text的地址
    printf("%p\n",p1); //输出p1所指向的地址
    //可以看出，指针的地址和指针指向的地址是不同的
    printf("%p\n",&p1); //输出p1的地址
    printf("%p\n",&p1 + 1); //输出p1指针本身的地址+1，即p1所指向的地址的下一个地址
    printf("%p\n",&p1); //
    printf("%p\n",&p1[0]); //

    //位域
    //位域是一种特殊的结构体，其成员变量的类型只能是int，unsigned int，signed int，不能是其他类型
    //位域的作用是指定变量占用的位数，可以节省内存空间

    struct
    {
        unsigned int widthValidated : 1;//大小为1byte
        unsigned int heightValidated : 1;
    } status1={1,2};

    printf("%llu\n",sizeof status1);
    //更好分配内存空间
    printf("%d\n",status1.heightValidated); //输出为0，因为heightValidated的值为2，而2的二进制为10，而heightValidated只有1位，所以输出为0，如果439行大小改成2，则正常输出

    //输入字符输出排序后的ASCII码
//    char first,second,third;
//    scanf ("%c %c %c",&first,&second,&third);
//    int firstint = first;
//    int secondint = second;
//    int thirdint = third;
//    int arr1[] = {firstint,secondint,thirdint};
//    bubble_sort(arr1,3);
//    printf("排序后的ASCII码为：%d %d %d\n",arr1[0],arr1[1],arr1[2]);

//每
// n个数求一次平均值    advanced_average();

//鸡兔同笼
    //chickenAndRabbit();

    //字符替换
    //    charReplace();

    //character();
    //    qone();
    //    qtwo();
    //    qthree();
    //   qfour();
    //    qfive();

    //MatrixMul();

    printf("=========================\n");
    //full_multiplication_table();
    //half_multiplication_table();
    //reverse_multiplication_table();
    //check_num();
    //check_num_switch();


    //    float_array();
//    revert();
//    array_average();
//    array_plus();
//    int num = 5;
//    printf("请输入一个数字：");
////    scanf("%d",&num);
//    if (isprime(num)){
//        printf("%d是素数\n",num);
//    } else{
//        printf("%d不是素数\n",num);
//    }
//    outprime();
//    input_tofile();
//    matrix_plus();
//    assignment1();
//    assignment2();
//    read_test();
//    count = 0;
//    for (x=0,y=0; (y!=123)|| (x<4);x++){
//        count = count +1;
//    }
//    printf("count = %d\n",count);
////指针遍历数组：
//    int arr[] = {1,2,3,4,5};
//    int *p0 = arr;
////    指针指向数组的首地址。。。
//    for (int i = 0; i < 5; ++i) {
//        printf("arr[%d] = %d\n",i,*(p0+i));
//    }
//
//    printf("\n");
//    int a111[] = {1,2,3,4,5,9},*p111=a111;
//    for (i=0;i<7;i++){
//        printf("a111 = %d\n",*(p111+i));
//    }
//    if(isNarcissusNumber(153)){
//        printf("是水仙花数\n");
//    }
//    else{
//        printf("不是水仙花数\n");
//    }
//
//    char strr[] = "hello";
//    char *str = strr;
//    sort1(str);
//    printf("排序后的字符串为：%s\n",str);
//    diamond(7,'*');
//    printf("%.8f\n", mysqrt(4));
//    printf("%d\n",sizeof("Hello"));
    int x111[2]={1,2};
    int *ppp = x111;
    *ppp++;
    printf("%d\n",x111[0]);
    int a222 = 1,a333 = 2;
    int temp = S(a333+a222);
    printf("%d",temp);
    return 0;
}





