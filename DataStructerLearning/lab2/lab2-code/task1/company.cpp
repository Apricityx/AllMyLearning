#include "company.h"
#include <iostream>
using namespace std;

int Company::inputEmployeeHead(int total_num) {
    //please implement this todo
    clock_t start_t = clock();
    for (int i = 0; i < total_num; i++) {
        Employee newEmployee;
        newEmployee.input(i);
        container.addHead(newEmployee);
    }
    clock_t end_t = clock();
    cout << "HEAD:" << end_t - start_t << "ms" << endl;
    return end_t - start_t;
}

int Company::inputEmployeeTail(int total_num) {
    //please implement this
    const clock_t start_t = clock();
    for (int i = 0; i < total_num; i++) {
        Employee newEmployee;
        newEmployee.input(i);
        container.addTail(newEmployee);
    }
    const clock_t end_t = clock();
    cout << "TAIL:" << end_t - start_t << "ms" << endl;
    return end_t - start_t;
}

void Company::findBestPaid() {
    bestPaid = Employee();
    ListTemp<Employee>::Iterator curr = container.Begin();
    while (!(curr == container.End())) {
        if (*curr > bestPaid)
            bestPaid = *curr;
        curr++;
    }
}

void Company::printBestPaid() const {
    cout << "The best-paid employee and gross pay: " << endl;
    bestPaid.output();
} // printBestPaid
