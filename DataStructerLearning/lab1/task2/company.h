#ifndef COMPCONT_H
#define COMPCONT_H

#include "employee.h"
#include "listCont.h"

class Company
{
private:
	Employee bestPaid;
	ListCont<Employee> empContainer;

public:
	void inputEmployee(); //when input employee from keyboard, store the input data in the container for later use;
							//Task 1: please implement this!

	void findBestPaid(); //go through the container to find the best paid employee
							//Task 2: please implement this!

	void printBestPaid() const;
}; 

#endif