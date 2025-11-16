// Created by francessca on 24-11-23.
//

#include "washCamp.h"
#include <iostream>
// #include <bits/random.h>
#include <random>// 用于随机数生成器
#include <cmath>    // 用于数学函数，如 exp 和 sqrt
#include <limits>   // 用于 numeric_limits
#include <cstdint>
// const int WashCamp::CAR_LIMITS=100;//limit of washing car
// const double WashCamp::LAMBDA = 0.05; //Arrival rate
// const double WashCamp::MU = 0.1; // Wash rate
double WashCamp::generateExTime(const double rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);
    const double U = dist(gen);
    const double T = -std::log(1 - U) / rate;
    return T;
}


WashCamp::WashCamp(const double lambda, const double mu, const int carLimits)
    : LAMBDA(lambda), MU(mu), CAR_LIMITS(carLimits) {
    totalWaitingTime = 0;
    numServedCars = 0;
    maxQueueLength = 0;
    totalNums = 0;
}

void WashCamp::printStatistic() const {
    std::cout << "车辆到达总数: " << totalNums << std::endl;
    std::cout << "总服务车辆数: " << numServedCars << std::endl;
    std::cout << "总等待时长: " << totalWaitingTime << std::endl;
    if (numServedCars > 0) {
        std::cout << "实际平均等待时间: " << totalWaitingTime / static_cast<double>(numServedCars) << std::endl;
        std::cout << "理论等待时间: " << LAMBDA / (MU * (MU - LAMBDA)) << std::endl;
    } else {
        std::cout << "服务车辆数为 0" << std::endl;
    }
    std::cout << "最大等待队列车辆数: " << maxQueueLength << std::endl;
}

void WashCamp::resetStates() {
    totalWaitingTime = 0;
    numServedCars = 0;
    maxQueueLength = 0;
}

void WashCamp::simulation() {
    double arrivalTime = 0;
    while (numServedCars < CAR_LIMITS) {
        totalNums++;
        //生成车辆到达时间间隔
        double interArrivalTime = generateExTime(LAMBDA);
        arrivalTime += interArrivalTime;
        if (carQueue.empty()) {
            processArrivalEmptyQ(arrivalTime);
        } else if (arrivalTime < carQueue.front().getDepartureTime()) {
            processArrivalNonEmptyQ(arrivalTime);
        } else {
            processDeparture();
        }
        if (carQueue.size() > maxQueueLength) {
            maxQueueLength = carQueue.size();
        }
    }
    processRemain(arrivalTime);
}

void WashCamp::runMultipleSim(int simCount) {
    for (int round = 0; round < simCount; ++round) {
        resetStates();
        simulation();
        std::cout << "========Round " << round + 1 << " statics: ========" << std::endl;
        printStatistic();
    }
}

// int WashCamp::getNextArrival() {
//     int tempT;
//     std::cout << "Please input the next arrival time (input 999 to terminate):\n";
//     std::cin >> tempT;
//     return tempT;
// }
void WashCamp::processArrivalEmptyQ(double arrivalTime) {
    double serviceTime = generateExTime(MU);
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.setDepartureAndWaitTime(arrivalTime, serviceTime);
    // arrivedCar.printCarArrival();
    carQueue.push(arrivedCar);
}

void WashCamp::processArrivalNonEmptyQ(double arrivalTime) {
    Car arrivedCar = Car(arrivalTime);
    carQueue.push(arrivedCar);
}

void WashCamp::processDeparture() {
    double currTime = carQueue.front().getDepartureTime();
    totalWaitingTime += carQueue.front().getWaitingTime();
    numServedCars++;
    carQueue.pop();
    if (!carQueue.empty()) {
        double serviceT = generateExTime(MU);
        carQueue.front().setDepartureAndWaitTime(currTime, serviceT);
    }
}

void WashCamp::processRemain(double arrivalTime) {
    while (!carQueue.empty()) {
        Car car = carQueue.front();
        double waitTime = arrivalTime - car.getArrivalTime();
        totalWaitingTime += waitTime;
        carQueue.pop();
    }
}
