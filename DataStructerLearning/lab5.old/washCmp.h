#ifndef WASH_H
#define WASH_H

#include <queue>
#include "car.h"

class WashCmp {
private:
    std::queue<Car> carQueue;
    const static int CAPACITY;
    // static int TOTAL_WASHED_CAR;
    int numServedCars;
    int totalWaitingTime;

    int getNextArrival() const; //accept user input to get the next arrival time
    void processArrivalNonEmptyQ(int currTime); //a car arrives and the waiting queue is not empty
    void processArrivalEmptyQ(int currTime); //a car arrives and the waiting queue is empty
    void processDeparture();

    void processRemain(); //no more arriving cars, process the remaining cars in the waiting queue

public:
    static const int MEAN_ARRIVAL_TIME;

    static const int MEAN_SERVICE_TIME;

    WashCmp();

    void simulation();

    void printStatistic();
};


#endif
