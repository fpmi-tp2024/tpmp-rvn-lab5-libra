#include "../include/driverstorer.h"
#include "../config/config.hpp"
#include "../include/carstorer.h"
#include "../include/orderstorer.h"
#include "../include/driver.h"
#include "../include/car.h"
#include "../include/order.h"
#include "../include/menuinterface.h"
#include <iostream>
#include <vector>

int main()
{
    MenuInterface menuInterface;
    
    menuInterface.run();

    return 0;
}
