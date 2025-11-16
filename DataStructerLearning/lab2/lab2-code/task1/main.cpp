#include "listTemp.h"
#include "company.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void insertTestData(int employ_num) {
    Company cmp1, cmp2;
    const int HEAD = cmp2.inputEmployeeHead(employ_num);
    const int TAIL = cmp1.inputEmployeeTail(employ_num);

    std::ofstream file("data.csv", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "无法打开文件!" << std::endl;
    }
    file << employ_num * 100 << ',' << HEAD << "," << TAIL << "\n";
    file.close();
    std::cout << "INSERTED" << std::endl;
}

int main() {
    for (int i = 0; i < 100; i++) {
        insertTestData(i * 100);
    }
    return 0;
}
