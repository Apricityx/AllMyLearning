//
// Created by apric on 2024/3/6.
//
#include <unistd.h>
#include <ctime>
#include <iostream>
// 头文件防卫式声明
# ifndef CPPLEARNING_CLOCK_H
#define CPPLEARNING_CLOCK_H
using namespace std;
// 虚函数与派生
class Clock {
public:
    //用lambda表达式
    string time_now = [this] {
        this->set_time();
        return this->get_time();
    }();

    void set_time_out(int count) {
        while (count--) {
            cout << "当前时间为" << time_now << "还有" << count << "秒结束计时" << endl;
            time_now = [this] {
                this->set_time();
                return this->get_time();
            }();
            sleep(1);
        }
        cout << "计时结束" << endl;
    }

private:
    void set_time() {
        //获取系统时间
        time_t now = time(0);
        tm *ltm = localtime(&now);
        hour = ltm->tm_hour;
        minute = ltm->tm_min;
        second = ltm->tm_sec;
    };

    string get_time() const {
        //        cout << hour << ":" << minute << ":" << second << endl;
        return to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
    };
    int hour = 0;
    int minute = 0;
    int second = 0;
};

class BombClock : private Clock {
    //private继承，这代表着Clock的所有public成员在BombClock中都是private的，但BombClock的public成员仍然可以访问
public:
    //重载运算符
    BombClock operator+(const BombClock &b) const {
        cout << "已合成新的炸弹" << endl;
        BombClock new_bomb = *this;
        new_bomb.self_attr.radius = this->self_attr.radius + b.self_attr.radius;
        return new_bomb;
    }

    void set_bomb() {
        set_time_out(self_attr.go_off_counter);
        cout << "Boom!" << endl;
    }

    void set_radius(int r) {
        self_attr.radius = r;
    }

    void get_info() const {
        cout << "此爆炸半径为" << self_attr.radius << endl;
    }

private:
    struct {
        int radius = 10;
        int go_off_counter = 10;
    } self_attr;
};

# endif //CPPLEARNING_CLOCK_H