#include "../include/driverstorer.h"
#include "../config/config.hpp"
#include "../include/carstorer.h"
#include "../include/orderstorer.h"
#include "../include/driver.h"
#include "../include/car.h"
#include "../include/order.h"
#include <iostream>
#include <vector>

long dateToSec(int year,int month,int day){
    tm *ltm = new tm;
    ltm->tm_mon=month - 1;
    ltm->tm_year = year - 1900;
    ltm->tm_mday = day;
    ltm->tm_hour = 0;
    ltm->tm_min = 0;
    ltm->tm_sec = 0;

    return mktime(ltm);
}

int main()
{
    std::cout << Config::getString("admine_password") << std::endl;
    std::cout << Config::getInt("commission_fees") << std::endl;
    std::cout << Config::getInt("MAX_COST") << std::endl;

    return 0;
}
