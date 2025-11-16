#include <iostream>
#include "employee.h"
using namespace std;

Employee::Employee()
{
   name = "";
   grossPay = 0;
} // default constructor


void Employee::input(int id)
{
	//please implement this
} // input


void Employee::output() const
{
	cout << "name: " << name << "; gross pay: " << grossPay << endl;
} // output

void Employee::operator=(const Employee &otherEmployee)
{
	name = otherEmployee.name;
	grossPay = otherEmployee.grossPay;
}

bool Employee::operator>(const Employee &otherEmployee) const
{
   return grossPay > otherEmployee.grossPay;
} // compare

string Employee::getName() const
{
	return name;
}