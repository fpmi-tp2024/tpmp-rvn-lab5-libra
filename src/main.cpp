#include "../include/park.h"
#include "../include/driverstorer.h"
#include "../config/config.hpp"
#include "../include/carstorer.h"
#include "../include/orderstorer.h"
#include<iostream>
#include<vector>


int main()
{
    std::cout << sum(1, 2) << std::endl;

    std::cout << Config::getString("admine_password") << std::endl;
    std::cout << Config::getInt("commission_fees") << std::endl;
    std::cout << Config::getInt("MAX_COST") << std::endl;

    CarStorer carStorer("data/park.db");
    DriverStorer driverStorer("data/park.db");
    OrderStorer orderStorer("data/park.db");

    std::pair<Driver,int> driver = driverStorer.getDriverWithMinimumTripsAndMoney();
    std::cout << driver.first.getName() << std::endl;
    std::cout<<driver.second<<std::endl;
    driverStorer.updateAddress(driver.first.getId(), "1");
    driverStorer.updateLogin(driver.first.getId(), "petya");
    driverStorer.updatePassword(driver.first.getId(), "12345");

    return 0;
}