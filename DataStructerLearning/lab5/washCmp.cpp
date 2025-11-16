#include "washCmp.h"
#include <iostream>
#include <random>

constexpr double LAMBDA = 0.05;
constexpr double U = 0.1;
const int WashCmp::CAPACITY = 5 + 1;

/*
 *根据传入的平均时间，生成一个随机的到达时间间隔或是服务时间
*/
double getRandomNumber(const double t) {
    std::random_device rd; // 获取随机设备作为种子
    std::mt19937 gen(rd()); // 初始化一个随机数生成器
    std::uniform_real_distribution<> dis(0.0, 1.0); // 生成 [0, 1] 之间的浮动随机数
    const double p = dis(gen);
    const double rate = t;
    return -1 / rate * log(1 - p);
}

WashCmp::WashCmp() {
    totalWaitingTime = 0;
    numServedCars = 0;
}

void WashCmp::printStatistic() const {
    std::cout << "LAMBDA: " << LAMBDA << std::endl;
    std::cout << "Number of served cars: " << numServedCars << std::endl;
    std::cout << "Total waiting time: " << totalWaitingTime << std::endl;
    std::cout << "Theoretical waiting time: " << LAMBDA / (U * (U - LAMBDA)) << std::endl;
    if (numServedCars > 0)
        std::cout << "The average waiting time is: " << (double) totalWaitingTime / numServedCars << std::endl;
    else
        std::cout << "The average waiting time is not applicable!" << std::endl;
}

void WashCmp::simulation() {
    int arrivalTime = 0; //get the next arrival time from keyboard input
    while (numServedCars < 100) {
        const double interArrivalTime = getRandomNumber(LAMBDA);//generate the arrival time interval
        arrivalTime += interArrivalTime; //update the arrival time
        if (carQueue.empty()) //queue empty, process arrival
        {
            processArrivalEmptyQ(arrivalTime);
        } else if (arrivalTime < carQueue.front().getDepartureTime()) //arrival first, process arrival
        {
            processArrivalNonEmptyQ(arrivalTime);
        } else //departure first or of the same time, process departure
        {
            processDeparture(); //no need to get next arrival
        }
    }

    //no more arrival, process the remaining cars in the queue
    processRemain();
}

int WashCmp::getNextArrival() {
    int tempT;
    std::cout << "Please input the next arrival time (input 999 to terminate):\n";
    std::cin >> tempT;
    return tempT;
}

void WashCmp::processArrivalEmptyQ(int arrivalTime) {
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.setDepartAndWaitTime(arrivalTime, getRandomNumber(U));
    //set the departure and waiting time of the arrived car
    arrivedCar.printCarArrival(); //print the arrival information of the arrived car
    carQueue.push(arrivedCar); //set the arrival time of the arrived car
}

void WashCmp::processArrivalNonEmptyQ(int arrivalTime) {
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.printCarArrival(); //print the arrival information of the arrived car
    carQueue.push(arrivedCar); //set the arrival time of the arrived car
}

void WashCmp::processDeparture() {
    int currTime = carQueue.front().getDepartureTime(); //get the current time

    totalWaitingTime += carQueue.front().getWaitingTime(); //update statistics
    numServedCars++; //update statistics

    carQueue.front().printCarDeparture(); //print departure information
    carQueue.pop(); //departs

    if (!carQueue.empty()) //set the departure and waiting time of
        carQueue.front().setDepartAndWaitTime(currTime, getRandomNumber(U));
    //the current front car in the queue
}

void WashCmp::processRemain() //wash the remaining cars in the queue
{
    while (!carQueue.empty())
        processDeparture();
}
