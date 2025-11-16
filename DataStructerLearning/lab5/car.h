#ifndef CAR_H
#define CAR_H

class Car
{
private:
	int arrivalTime;
	int departureTime;
	int waitingTime;

public:
	const static int SERVICE_T;
	Car();
	Car(int arrivalT);

	int getArrivalTime();
	int getDepartureTime();
	int getWaitingTime();

	void setDepartAndWaitTime(int startServiceTime, int serviceTime);
	void printCarDeparture();
	void printCarArrival();
};


#endif
