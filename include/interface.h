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

class Interface
{
protected:
    Auth auth = Auth("data/park.db");
    DriverStorer driverStorer = DriverStorer("data/park.db");
    CarStorer carStorer = CarStorer("data/park.db");
    OrderStorer orderStorer = OrderStorer("data/park.db");

public:
    virtual void run() = 0;
};

#endif