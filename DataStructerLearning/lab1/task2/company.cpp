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
        }
        empContainer.pushFromEnd(emp);
    }
}

Employee *Company::findBestPaidReverse() {
    double maxSalary = 0;
    int counter = 0; // 计数器，计算经过多少次查找
    int final_counter = 0; // 计数器最终结果
    Employee *bestPaidEmployee = nullptr;
    // 使用迭代器从尾部向头部遍历
    for (auto it = empContainer.end(); it != --empContainer.begin(); --it) {
        // 移动到上一个员工
        counter++;
        if ((*it).grossPay > maxSalary) {
            maxSalary = (*it).grossPay;
            bestPaidEmployee = &(*it);
            final_counter = counter;
        }
    }
    this->bestPaid = *bestPaidEmployee;
    cout << "经过" << final_counter << "次查找" << endl;
    return bestPaidEmployee; // 返回收入最高的员工
}

void Company::findBestPaid() {
    //Task 2: please implement this!
    int counter = 0; // 计数器，计算经过多少次查找
    int final_counter = 0; // 计数器最终结果
    bestPaid = *empContainer.begin();
    for (auto it = empContainer.begin(); it != ++empContainer.end(); ++it) {
        counter++;
        if ((*it) > bestPaid) {
            bestPaid = *it;
            final_counter = counter;
        }
    }
    cout << "经过" << final_counter << "次查找" << endl;
}

void Company::printBestPaid() const {
    cout << "The best-paid employee and gross pay: " << endl;
    bestPaid.output();
} // printBestPaid
