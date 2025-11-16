#include <iostream>
#include "employee.h"
#include <ctime>
#include <random>
using namespace std;

Employee::Employee() {
    name = "";
    grossPay = 0;
} // default constructor


void Employee::input(const int id) {
    //please implement this todo
    name = "employee" + to_string(id);
    // 利用C++11的随机数生成器生成随机数
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // uniform_int_distribution<> dis(1000, 10000);
    // int randomNumber = dis(gen);  // Generates a random number between 0 and 99
    int randomNumber = 1;  // Generates a random number between 0 and 99
    grossPay = randomNumber;
    this->grossPay = grossPay;
} // input


void Employee::output() const {
    cout << "name: " << name << "; gross pay: " << grossPay << endl;
} // output

void Employee::operator=(const Employee &otherEmployee) {
    name = otherEmployee.name;
    grossPay = otherEmployee.grossPay;
}

bool Employee::operator>(const Employee &otherEmployee) const {
    return grossPay > otherEmployee.grossPay;
} // compare

string Employee::getName() const {
    return name;
}
