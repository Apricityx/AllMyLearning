// BestPaidEmployee.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "company.h"
#include <iostream>
using namespace std;

int main()
{
	Company cmp;
	cmp.inputEmployee();
	//cmp.findBestPaid();
	//cmp.printBestPaid();

	cout << "Number of employee: " << cmp.getSize() << endl;

	return 0;
}
