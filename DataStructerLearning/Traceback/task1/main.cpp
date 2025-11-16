// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "backtrack.h"
#include <iostream>
using namespace std;

int main()
{
	Application app;
	BackTrack btr(app);

	if (btr.backTrack(app.getStartPosition()))
		app.print();
	else
		cout << "Problem has no solution!" << endl;

	return 0;
}
