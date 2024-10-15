#include <iostream>

using namespace std;

#include "company.h"

void Company::inputEmployee() {
    //Task 1: Please implement this!
    while (true) {
        Employee emp;
        emp.input();
        if (emp.getName() == "*") {
            break;
        } else {
            empContainer.addHead(emp);
        }
    }
    //todo
}

int Company::getNumber() const {
    return empContainer.getSize();
}