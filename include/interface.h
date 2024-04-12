#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <map>
#include <string>
#include "auth.h"
#include "../include/utilfuntions.h"
#include "../include/driverstorer.h"
#include "../include/orderstorer.h"
#include "../include/carstorer.h"
#include "../include/driver.h"
#include "../include/order.h"
#include "../include/car.h"
#include<limits>

class Interface
{
protected:
    Auth auth = Auth("data/park.db");
    DriverStorer driverStorer = DriverStorer("data/park.db");
    CarStorer carStorer = CarStorer("data/park.db");
    OrderStorer orderStorer = OrderStorer("data/park.db");

    int getNumberInput(const std::string& message){
	    int number;
        std::cout << message;
        while(!(std::cin >> number)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
    return number;
    }

public:
    virtual void run() = 0;
};

#endif