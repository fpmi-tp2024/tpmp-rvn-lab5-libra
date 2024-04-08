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

    Car car1("5555AV-5", "Toyota", "Camry", 10000, 1000);
    Car car2("6666AV-4", "BMW", "x5", 15000, 2000);
    Car car3("7777AV-3", "Fiat", "Tipo", 22121, 1111);
    Car car4("8888AV-2", "Ford", "Escort", 11040, 13134);
/*
    carStorer.addCar(car1);
    carStorer.addCar(car2);
    carStorer.addCar(car3);
    carStorer.addCar(car4);
    */

    Driver driver1(-1, "driver1", "Ivan", "B", dateToSec(2000, 1, 1), 1984, "Minsk");
    Driver driver2(-1, "driver2", "Petr", "C", dateToSec(2005, 1, 1), 1992, "Minsk");
    Driver driver3(-1, "driver3", "Vasya", "D", dateToSec(2007, 1, 1), 1975, "Minsk");
    Driver driver4(-1, "driver4", "Kolya", "A", dateToSec(2010, 1, 1), 1950, "Minsk");

/*
    driverStorer.addDriver(driver1,"123");
    driverStorer.addDriver(driver2,"123");
    driverStorer.addDriver(driver3,"123");
    driverStorer.addDriver(driver4,"123");
    */

    Order order1(-1,dateToSec(2020,11,1),1,"5555AV-5",250,150,1000);
    Order order2(-1,dateToSec(2020,11,1),2,"6666AV-4",250,150,1000);
    Order order3(-1,dateToSec(2020,11,1),3,"7777AV-3",250,150,1000);
    Order order4(-1,dateToSec(2020,11,1),4,"8888AV-2",250,150,1000);

    /*
    orderStorer.addOrder(order1);
    orderStorer.addOrder(order2);
    orderStorer.addOrder(order3);
    orderStorer.addOrder(order4);
    */

   //driverStorer.getDriverWithMinimumTripsAndMoney();
    
    return 0;
}
