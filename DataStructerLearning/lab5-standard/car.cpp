//
// Created by francessca on 24-11-23.
//

#include "car.h"
#include <iostream>

// const int Car::SERVICE_T = 10;

Car::Car(){
    arrivalTime = 0;
    departureTime =0;
    waitingTime = 0;
}
Car::Car(double arrivalT) {
    arrivalTime =arrivalT;
    departureTime = 0;
    waitingTime =0;
}

double Car::getArrivalTime() const {
    return arrivalTime;
}
double Car::getDepartureTime() const {
    return departureTime;
}
double Car::getWaitingTime() const {
    return waitingTime;
}
void Car::setDepartureAndWaitTime(double startServiceTime,double serviceTime) {
    departureTime =  startServiceTime + serviceTime;
    waitingTime = startServiceTime - arrivalTime;
}

void Car::printCarDeparture() const {
    std::cout << "A car has washed and departs!\n";
    std::cout<<"\tArrival time : " << arrivalTime << std::endl;
    std::cout << "\tDeparture time : " << departureTime << std::endl;
    std::cout << "\tWaiting time : " << waitingTime << std::endl;
 }
void Car::printCarArrival() const {
    std::cout << "A car arrives !\n";
    std::cout << "\tArrival time: " << arrivalTime << std::endl;
}





