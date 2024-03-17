#include <iostream>
#include "Clock.h"
#include <string>
#include <fstream>
#include <map>
using namespace std; // 这一行的意思是使用std命名空间下的所有标识符
//form CSDN: 这样命名空间std内定义的所有标识符都有效（曝光）。就好像它们被声明为全局变量一样
class Box {
public:
    double length;   // 盒子的长度
    double breadth;  // 盒子的宽度
    double height;   // 盒子的高度
    [[nodiscard]] double get_volume() const { //nodiscard是C++11的新特性，用于告诉编译器，这个函数的返回值不应该被忽略
        return length * breadth * height;
    };

    void init(double l, double b, double h) {
        length = l;
        breadth = b;
        height = h;
    }
};

int main() {
//解决控制台中文乱码问题
    system("chcp 65001");
    cout << "Hello, world!" << endl;
    // C中的枚举类型
    enum color {
        red, blue = 5, yellow
    } a;
//    b = blue;
    cout << blue << endl;
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
    cout << "Volume of Box1 : " << volume << endl;  //输出结果：Volume of Box1 : 210

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
    file.open("../test.txt", ios::out);
    if (!file) cout << "文件打开失败" << endl;
    string file_content, file_content_now;
    while(getline(file, file_content_now))
        file_content += file_content_now + "\n";
    file >> file_content;
    cout << "读取到内容\n" << file_content << endl;
    file.close();
    //写入文件
    ofstream file_write;
    file_write.open("../test.txt", ios::app);
    //将file_content转换为int
    char last_word = file_content[file_content.length() - 2];
    int file_content_int = last_word - '0';
    cout<< "写入的内容为" << file_content_int + 1 << endl;
    file_write << file_content_int + 1;
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

    
    return 0;
}