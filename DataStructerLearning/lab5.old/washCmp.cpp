#include "washCmp.h"
#include <ctime>    // time
#include <iostream>
#include <random>

const int WashCmp::CAPACITY = 5 + 1;
const int WashCmp::MEAN_ARRIVAL_TIME = 10; // lambda
// const int WashCmp::MEAN_SERVICE_TIME = 5; // u > lambda
WashCmp::WashCmp() {
    totalWaitingTime = 0;
    numServedCars = 0;
}

void WashCmp::printStatistic() {
    std::cout << "Number of served cars: " << numServedCars << std::endl;
    std::cout << "Total waiting time: " << totalWaitingTime << std::endl;
    if (numServedCars > 0)
        std::cout << "The average waiting time is: " << static_cast<double>(totalWaitingTime) / numServedCars << std::endl;
    else
        std::cout << "The average waiting time is not applicable!" << std::endl;
}

void WashCmp::simulation() {
    int arrivalTime = getNextArrival();
    while (true) {
        if (numServedCars > 100) // 更改为洗了100辆车就停止 //queue empty, process arrival
        {
            break;
        }
        if (carQueue.empty()) // 如果队列为空，则直接将到达的车辆加入到队列中
        {
            processArrivalEmptyQ(arrivalTime);
            arrivalTime = getNextArrival(); //get next arrival
            continue;
        }
        if (arrivalTime < carQueue.front().getDepartureTime()) // 如果到达时间小于队列中第一个车辆的离开时间，则该车到了还没洗完，需要将其加入等待队列
        {
            processArrivalNonEmptyQ(arrivalTime);
            arrivalTime = getNextArrival(); //get next arrival
        } else //departure first or of the same time, process departure
        {
            // 如果还没到达就已经有车辆离开了，那么直接处理离开的车辆
            std::cout<<"车辆离开"<<std::endl;
            processDeparture(); //no need to get next arrival
        }
    }

    //no more arrival, process the remaining cars in the queue
    processRemain();
}

int WashCmp::getNextArrival() const {
    // 更改为随机生成到达时间，服从指数分布
    // 若总时间为0，则返回10
    // 平均到达率为1/平均时间
    constexpr double arriveRate = 1.0 / static_cast<double>(MEAN_ARRIVAL_TIME);
    // tempT = (-1/arriveRate)*ln(1-q)
    std::random_device rd; // 获取随机设备作为种子
    std::mt19937 gen(rd()); // 初始化一个随机数生成器
    std::uniform_real_distribution<> dis(0.0, 1.0); // 生成 [0, 1] 之间的浮动随机数
    const double p = dis(gen);
    const double tempT = -1 / arriveRate * log(1 - p);
    std::cout << "随机时间: " << tempT << totalWaitingTime << '|' << p << std::endl;
    // std::cout << "Please input the next arrival time (input 999 to terminate):\n";
    std::string a = "123";
    return (int) tempT + 1;
}

void WashCmp::processArrivalEmptyQ(int arrivalTime) {
    // 如果队列为空，则证明是第一辆车到达，直接将到达时间设置为开始服务时间
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.setDepartAndWaitTime(arrivalTime); // 设置离开时间与等待时间
    arrivedCar.printCarArrival(); //print the arrival information of the arrived car
    carQueue.push(arrivedCar); //set the arrival time of the arrived car
}

void WashCmp::processArrivalNonEmptyQ(int arrivalTime) {
    // 如果队列不为空，则证明有车辆在等待，将到达的车辆加入到队列中
    if (carQueue.size()) //add the arrived car to the waiting queue
    {
        Car arrivedCar = Car(arrivalTime); // 离开时间与等待时间都初始化为0，后续设置
        arrivedCar.printCarArrival(); //print the arrival information of the arrived car
        carQueue.push(arrivedCar); //set the arrival time of the arrived car
    } else
        throw "Unknown error, this should not happen!";
}

void WashCmp::processDeparture() {
    // 车辆离开时
    const int currTime = carQueue.front().getDepartureTime(); //get the current time

    totalWaitingTime += carQueue.front().getWaitingTime(); //update statistics
    numServedCars++; //update statistics

    carQueue.front().printCarDeparture(); //print departure information
    carQueue.pop(); //departs

    if (!carQueue.empty()) //set the departure and waiting time of
        carQueue.front().setDepartAndWaitTime(currTime); // 在第一个车辆离开后，设置下一个车辆的离开时间与等待时间
}

void WashCmp::processRemain() //wash the remaining cars in the queue
{
    while (!carQueue.empty())
        processDeparture();
}
