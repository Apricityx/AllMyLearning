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
							//Task 1: Please implement this!

	int getNumber() const; //return the number of employee
}; 

#endif