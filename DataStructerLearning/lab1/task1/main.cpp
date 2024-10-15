#include "company.h"
#include <iostream>

using namespace std;

int main()
{
    Company cmp;
    cmp.inputEmployee();

    cout << "Number of employee: " << cmp.getNumber() << endl;
    return 0;
}