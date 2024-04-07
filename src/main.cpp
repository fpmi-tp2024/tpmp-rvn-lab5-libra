#include "../include/driverstorer.h"
#include "../config/config.hpp"
#include "../include/carstorer.h"
#include "../include/orderstorer.h"
#include "../include/driver.h"
#include "../include/car.h"
#include "../include/order.h"
#include <iostream>
#include <vector>

int main()
{
    std::cout << Config::getString("admine_password") << std::endl;
    std::cout << Config::getInt("commission_fees") << std::endl;
    std::cout << Config::getInt("MAX_COST") << std::endl;

    CarStorer carStorer("data/park.db");
    DriverStorer driverStorer("data/park.db");
    OrderStorer orderStorer("data/park.db");

    Car car("1234AB-7", "Volvo", "XC90", 2500, 10000);
    Order order(1, 123456789, 1, "1234AB-7", 1000, 1000, 1000);
    Driver driver(1, "login", "name", "B", "11.10.2004", 2000, "address");

    std::cout << car.toString() << std::endl;
    std::cout << order.toString() << std::endl;
    std::cout << driver.toString() << std::endl;

    return 0;
}