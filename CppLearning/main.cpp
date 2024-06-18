#include <any>
#include <deque>
#include <iostream>
#include "Clock.h"
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <list>

void mySort(int *arg, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (arg[j] > arg[j + 1]) {
                swap(arg[j], arg[j + 1]);
            }
        }
    }
}

// 模板类与继承
template<typename T>
class TemplateClass {

};

class DerivedClass : public TemplateClass<int> {

};

// 枚举类型
enum Color {
    color_red,
    color_green,
    color_blue,
};

// 按引用传递指针
void nullify(int *&arg) {
    arg = nullptr;
}
// 指针有*的时候代表改变指针指向的对象的值，没有*的时候代表改变指针的值
// 引用传递实践

void refTest(int &arg) { //此处的&代表不再拷贝一个值进入函数进行处理，而是引用原来的值，更改这个参数会导致原来的值同样被更改
    arg += 1;
}
// 一般来说，当我们不想修改实参的值的时候，可以用const引用



void refTestConst(const int &arg) {
//    arg +=1; no
    cout << "传参为" << arg << endl;
}

// 采用按地址传递的函数实现可选参数
void greeting(std::string *arg = nullptr) {
    cout << "HELLO, " << (arg ? *arg : "Undefined") << "!" << endl;
}

template<typename Type1>
Type1 templateTest(Type1 arg) {
    cout << "The type of arg is " << typeid(arg).name() << endl;
    return arg;
}


void incrementAndPrint() {
    // 静态变量实验
    static int inc = 1;
    cout << ++inc;
}

extern double pai; // extern关键字声明为占位符

int add(int a, int b); // 向前声明，声明有这么个函数但是不给出具体实现，在后续的代码中再对其进行补充
int gVar = 5;

namespace space {
    int a = 1;
}

int getGlobalVar() {
    return gVar;
}

// C++模板
// 模板函数
template<typename T>
int templateFunction(T arg) {
    cout << typeid(T).name() << endl;
    return 1;
}


// 模板类
template<class type>
class templateClass {
};

using namespace std; // 这一行的意思是使用std命名空间下的所有标识符
//from CSDN: 这样命名空间std内定义的所有标识符都有效（曝光）。就好像它们被声明为全局变量一样
class throwError : public exception {
public:
    string content = "Undefined";

    explicit throwError(string error) {
        content = std::move(error);
    }

    [[nodiscard]] const char *what() const noexcept override {
        return &content[0];
    }
};

class Box {
public:
    double length; // 盒子的长度
    double breadth; // 盒子的宽度
    double height; // 盒子的高度
    [[nodiscard]] double get_volume() const {
        // 这里const表示此函数不会修改类的成员变量
        // nodiscard是C++11的新特性，用于告诉编译器，这个函数的返回值不应该被忽略
        return length * breadth * height;
    };

    void init(double l, double b, double h) {
        length = l;
        breadth = b;
        height = h;
    }

    auto echo() const {
        cout << length;
    }

    // static 函数
};


int main() {
    //解决控制台中文乱码问题
    system("chcp 65001");
    cout << "Hello, world!" << endl;
    // C中的枚举类型
    //    enum color {
    //        red, blue = 5, yellow
    //    } a;
    //    b = blue;
    //    cout << blue << endl;
    // 枚举类型内的变量在外面也可以使用
    //Cpp中的强制类型转换
    int i;
    double d = 3.14;
    i = static_cast<int>(d);

    float p = static_cast<float>(d);
    //IDE报错：Clang-Tidy: Narrowing conversion from 'float' to 'int';
    cout << p << endl;

    double volume = 0.0;
    Box box1{};
    box1.length = 5.0;
    box1.breadth = 6.0;
    box1.height = 7.0;
    volume = box1.get_volume();
    Box box2{};
    box2.init(5.0, 6.1, 7.8);
    volume = box2.get_volume();
    cout << "Volume of Box1 : " << volume << endl; //输出结果：Volume of Box1 : 210

    //字符串数组
    char array_str[] = "HELLO WORLD";
    cout << array_str << endl;
    //string类
    string class_str1 = "Hello";
    string class_str2 = "World";
    string class_str = class_str1 + " " + class_str2;
    //string类和数组的区别是，string类可以直接用+号连接，而数组不行，需要用strcat函数，且string类可以直接输出
    cout << class_str << endl;
    //引用
    int reference_ori = 1;
    int &reference = reference_ori;
    cout << "引用值为" << reference << endl;
    reference_ori = 2;
    cout << "原来的值更改后，引用值为" << reference << endl;
    // 引用值相当于原来的值的别名，更改原来的值，引用值也会更改
    reference = 3;
    cout << "引用值更改后，原来的值为" << reference_ori << endl;
    // 引用值更改后，原来的值也会更改
    // 故引用值和原来的值是同一个值，只是有两个名字而已
    //时间
    const time_t time = 0;
    //time的数据类型是time_t，是一个长整型
    char *time_now = ctime(&time);
    //ctime函数的作用是将time_t类型的时间戳转换为字符串，并将字符串指针返回，指针指向的字符串是一个静态的字符串，所以不需要释放
    //指针指向的字符串是一个静态的字符串，这个静态的字符串储存在一个静态的内存区域
    cout << "当前时间戳为" << time_now << endl;
    //输入输出流
    //读取文件

    ifstream file;
    file.open("../test.txt", ios::in);
    if (!file) cout << "文件打开失败" << endl;
    string file_content, file_content_now;
    while (getline(file, file_content_now))
        file_content += file_content_now + "\n";
    file >> file_content;
    cout << "读取到内容\n" << file_content << endl;
    file.close();
    //写入文件
    ofstream file_write;
    file_write.open("../test.txt", ios::app);
    //将file_content转换为int
    // 写指针向前移动一位
    file_write.seekp(-1, ios::end);
    file_write << '1';
    //    char last_word = file_content[file_content.length() - 2];
    //    int file_content_int = last_word - '0';
    //    int file_content_int = 0;
    //    cout << "写入的内容为" << file_content_int + 1 << endl;
    //    file_write << file_content_int + 1;
    file_write.close();
    //定义类
    Clock clock{};
    cout << "当前时间为" << clock.time_now << endl;
    //    clock.set_time_out(5);
    BombClock C4{};
    //    C4.set_bomb();
    C4.set_radius(5);
    BombClock C5{};
    C5.set_radius(10);
    //重载运算符
    BombClock C6 = C4 + C5; // 合成新的炸弹
    C6.get_info();
    // 异常捕获
    // try {
    //     C6.set_bomb();
    // }
    // catch (exception &e) {
    //     cout << e.what() <<endl;
    // }
    //static变量
    static int static_i = 10;
    cout << "static变量为" << static_i << endl;
    //static函数

    // 错误处理
    try {
        throw throwError("content");
    } catch (throwError &e) {
        cout << "错误为" << e.what() << endl;
    }
    // 几种初始化变量的方式
    int init_var_a(5); // 直接初始化
    int init_var_b{1}; // 括号初始化
    // 未定义行为
    int undefined_var{}; // {}初始化为0
    cout << "未定义变量为" << undefined_var << endl;
    cout << add(1, 2) << endl;
#if 0
    cout << "这些文字不会被输出到控制台" << endl;
#endif
    signed int signed_int = 1;
    // 静态类型转换
    //    signed int 和 int 是一样的
    //    add(1, static_cast<int>(2.2));
    //    int static_cast_int = static_cast<int>(2.2);
    // constexpr关键字，编译时常量，这个值不是在程序运行中途决定的
    //    constexpr int constexpr_int{1};
    //    string get_line_var = "";
    //    getline(cin >> ws, get_line_var);
    // ws是一个流控制符，表示忽略前面的空白符，直到遇到第一个非空白符为止
    //    cout << "输入的内容为" << get_line_var << endl;
    // 只读的访问方式
    string_view read_only_string_var = "1234";
    cout << read_only_string_var << endl;
    read_only_string_var = "1223";
    cout << read_only_string_var << endl;
    // space命名空间
    cout << space::a << endl;
    cout << &getGlobalVar << endl;
    templateFunction(1.1);
    // STL容器
    // 顺序容器
    // vector容器
    vector<int> vec;
    vec.push_back(1);
    cout << vec[0] << endl;
    // vector容器只支持从前面插入

    //deque容器
    deque<int> deq = {1, 2, 3, 4, 5};
    deq.push_back(6);
    deq.push_front(0);
    for (int deq_i = 0; deq_i < 7; deq_i++) {
        cout << deq[deq_i];
    }
    cout << endl;
    //deque容器支持双向插入

    //尝试迭代器访问deque
    deque<int>::iterator it;
    it = deq.begin();
    int counter = 5;
    while (it != deq.end()) {
        *it = counter;
        counter++;
        ++it;
    }
    it = deq.begin();
    while (it != deq.end()) {
        cout << *it << endl;
        ++it;
    }
    // 字典容器
    map<int, string> cMap;
    cMap.insert(make_pair(1, "123123"));
    auto it2 = cMap.cbegin();
    while (it2 != cMap.cend()) {
        if (it2->first == 1) {
            cout << "it2中1对应的元素为" << it2->second << endl;
        }
        ++it2; // 使用 ++i 可以更明确地表示“我们不关心操作符的返回值，只关心它的副作用（即增加变量的值），尤其是i为一个对象的时候
    }
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint(); // static变量只能在相应代码块中被访问，外边访问不到，在代码块结束后static变量仍然会保留
    // 除非变量永远不需要被重置，否则要避免使用静态局部变量
    cout << endl;
    cout << pai << endl;
    templateTest(2.0);
    int lvalue = 1;
    const int &refLvalue = lvalue;
    cout << refLvalue << endl;
    lvalue = 2;
    cout << refLvalue << endl;
    // 可变变量 Const引用
    refTest(lvalue);
    cout << lvalue << endl;
    refTestConst(lvalue);
    // 可见，传递引用会直接修改此参数的值

    // const指针
    const int constTest1 = 1;
    const int constTest2 = 2;
    int constTest3 = 3;
    const int *constPtrTest = &constTest1;
    int *NormalPtrTest{};
    cout << *constPtrTest << endl;
    constPtrTest = &constTest2;
    cout << *constPtrTest << endl;
    constPtrTest = &constTest3;
//    *constPtrTest = 4; Not Allowed
    NormalPtrTest = &constTest3;
    *NormalPtrTest += 1; // Allowed
    cout << *NormalPtrTest << endl;
    string greetingName{"Alex"};
    greeting(&greetingName);
    // 事实上，用函数重载会比较好
    nullify(NormalPtrTest);
    cout << NormalPtrTest << endl;
    cout << time_now;
    // STL排序
    int sortingArr[]{3, 4, 5, 1, 3, 5, 6, 2, 5, 7, 3, 2, 4};
    int *pointerToArr = sortingArr;
    mySort(sortingArr, 13);
    for (i = 0; i < 13; i++) {
        cout << pointerToArr[i] << ' ';
    }
    cout << endl;
    // 动态数组

    return 0;
}


// 向前声明
int add(const int a, const int b) {
    return a + b;
}
