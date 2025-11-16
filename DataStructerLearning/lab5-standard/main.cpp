#include <iostream>
#include "washCamp.h"
int main()
{
    constexpr int SIM_COUNT = 20;
    constexpr double Lambda = 0.05;
    constexpr double Mu = 0.1;
    constexpr int CarLimit = 100;
    WashCamp cmp(Lambda,Mu,CarLimit);
    cmp.runMultipleSim(SIM_COUNT);
    cmp.printStatistic();
    return 0;
}