#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <map>
#include <string>
#include "../include/utilfuntions.h"
#include "../include/driverstorer.h"
#include "../include/orderstorer.h"
#include "../include/carstorer.h"
#include "../include/driver.h"
#include "../include/order.h"
#include "../include/car.h"

class Interface
{
protected:
    DriverStorer driverStorer = DriverStorer("data/park.db");
    OrderStorer orderStorer = OrderStorer("data/park.db");
    CarStorer carStorer = CarStorer("data/park.db");

public:
    virtual void run() = 0;
};

#endif