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
    std::tm t = {};
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    if (std::mktime(&t) == -1) {
        std::cerr << "Error: unable to make time using mktime\n";
        return -1;
    }

    return std::mktime(&t);
}

int main()
{
    CarStorer carStorer("data/park.db");
    DriverStorer driverStorer("data/park.db");
    OrderStorer orderStorer("data/park.db");

  
    return 0;
}
