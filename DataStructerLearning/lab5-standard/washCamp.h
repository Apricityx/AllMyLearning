//
// Created by francessca on 24-11-23.
//
#include <queue>
#include "car.h"
#ifndef WASHCAMP_H
#define WASHCAMP_H


class WashCamp {
  private:
    std::queue<Car> carQueue;//车辆队列
    const int CAR_LIMITS; //清洗车辆数量限制
    const double LAMBDA; //车辆到达率
    const double MU;    //车辆服务率
    int numServedCars; //服务车辆数
    double totalWaitingTime; //总车辆等待时间
    size_t maxQueueLength;  //等待车辆队列最大长度
    int totalNums; // 车辆总到达数

    static double generateExTime(double rate);//生成指数级增长数方案
    void processArrivalNonEmptyQ(double arrivalTime);//处理空队列车辆到达
    void processArrivalEmptyQ(double arrivalTime);//处理非空队列车辆到达
    void processDeparture();//处理车辆离开
    void processRemain(double arrivalTime);//处理队列剩余车辆
public:
    WashCamp(double lambda,double mu,int catLimit);
    void resetStates();//对WashCamp状态进行重置
    void simulation(); //单次仿真洗车模拟
    void printStatistic() const; //打印WashCamp仿真数据
    void getAverageWaitT() const ; // 打印实际/理论平均等待时间
    void runMultipleSim(int simCount);//多伦仿真洗车模拟
};



#endif //WASHCAMP_H
