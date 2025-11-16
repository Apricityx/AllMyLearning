//
// Created by francessca on 24-11-23.
//

#ifndef CAR_H
#define CAR_H



class Car {
private:
    double arrivalTime;
    double departureTime;
    double waitingTime;
    double SERVICE_T{};
public:
    Car();
    explicit Car(double arrivalT);

    double getArrivalTime() const;
    double getDepartureTime() const;
    double getWaitingTime() const;

    void setDepartureAndWaitTime(double startServiceTime,double serviceTime);
    void printCarDeparture() const;
    void printCarArrival() const;
};



#endif //CAR_H
