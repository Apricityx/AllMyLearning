#include <iostream>
#include "company.h"

using namespace std;

void Company::inputEmployee() {
    //Task 1: please implement this! todo
    while (true) {
        Employee emp;
        emp.input();
        if (emp.getName() == "*") {
            break;
        } else {
            empContainer.addHead(emp);
        }
    }
}

void Company::findBestPaid() {
    //Task 2: please implement this!
    if (empContainer.getSize() == 0) {
        return;
    }
    bestPaid = *empContainer.Begin();
    for (ListCont<Employee>::Iterator it = empContainer.Begin(); !(it == empContainer.End()); it++) {
        if ((*it) > bestPaid) {
            bestPaid = *it;
        }
    }
    bestPaid.output();
}

void Company::printBestPaid() const {
    cout << "The best-paid employee and gross pay: " << endl;
    bestPaid.output();
} // printBestPaid
