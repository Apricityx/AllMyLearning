#include "company.h"
#include <iostream>
using namespace std;

void Company::inputEmployee()
{
	Employee employee;

	employee.input();

	while (employee.getName() != "*")
	{
		container.Add(employee); // add to the container
		employee.input();
	}
}

void Company::findBestPaid()
{
	ArrayCont<Employee>::Iterator itr;
	for (itr = container.Begin(); !(itr == container.End()); itr++)
	{
		if (*itr > bestPaid) // overloading >
			bestPaid = *itr; //overloading =
	}
}

void Company::printBestPaid() const
{
	cout << "The best-paid employee and gross pay:" << endl;
	bestPaid.output();
} // printBestPaid

int Company::getSize() const
{
	return container.getSize();
} //get the number of employee