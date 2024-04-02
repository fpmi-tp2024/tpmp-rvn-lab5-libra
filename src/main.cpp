#include "../include/park.h"
#include "../include/driverstorer.h"
#include "../config/config.hpp"
#include "../include/carstorer.h"
#include "../include/orderstorer.h"
#include<iostream>


int main()
{
    std::cout << sum(1, 2) << std::endl;

    std::cout << Config::getString("admine_password") << std::endl;
    std::cout << Config::getInt("commission_fees") << std::endl;
    std::cout << Config::getInt("MAX_COST") << std::endl;

    CarStorer carStorer("data/park.db");
    OrderStorer orderStorer("data/park.db");


    carStorer.removeCar("1234AB-7");

    return 0;
}