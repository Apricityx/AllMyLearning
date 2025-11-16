#include "car.h"

#include <cmath>
#include <iostream>
#include <random>

const int Car::SERVICE_T = 5; // 应该比到达时间小
Car::Car() {
    arrivalTime = 0;
    departureTime = 0;
    waitingTime = 0;
}

Car::Car(int arrivalT) {
    arrivalTime = arrivalT;
    departureTime = 0; //to be set later
    waitingTime = 0; //to be set later
}

int Car::getArrivalTime() {
    return arrivalTime;
}

int Car::getDepartureTime() {
    return departureTime;
}

int Car::getWaitingTime() {
    return waitingTime;
}

void Car::setDepartAndWaitTime(int startServiceTime) {
    // 每次服务时间更改为随机时间
    std::random_device rd; // 获取随机设备作为种子
    std::mt19937 gen(rd()); // 初始化一个随机数生成器
    std::uniform_real_distribution<> dis(0.0, 1.0); // 生成 [0, 1] 之间的浮动随机数
    constexpr double serviceRate = 1.0 / static_cast<double>(SERVICE_T);
    const double p = dis(gen);
    const double tempT = -1 / serviceRate * log(1 - p);
    departureTime = startServiceTime + tempT; // 每次服务时间是确定的，那么离开时间就是开始时间加上服务时间

    waitingTime = startServiceTime - arrivalTime; // 等待时间是到达时间减去开始服务时间
}

void Car::printCarDeparture() {
    std::cout << "A car is washed and departs!\n";
    std::cout << "\tArrival time: " << arrivalTime << std::endl;
    std::cout << "\tDeparture time: " << departureTime << std::endl;
    std::cout << "\tWaiting time: " << waitingTime << std::endl;
}

void Car::printCarArrival() {
    std::cout << "A car arrives!\n";
    std::cout << "\tArrival time: " << arrivalTime << std::endl;
}
