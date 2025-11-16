#ifndef COMPCONT_H
#define COMPCONT_H

#include <random>

#include "employee.h"
#include "listTemp.h"

class Company {
private:
    Employee bestPaid;
    ListTemp<Employee> container;

public:
    int inputEmployeeHead(int total_num); //please implement
    int inputEmployeeTail(int total_num); //please implement
    void findBestPaid();

    void printBestPaid() const;
};

#endif
