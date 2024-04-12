#include "../include/menuinterface.h"
#include <iostream>
#include <vector>

void addTestData()
{
    Auth auth("data/park.db");
    DriverStorer driverStorer("data/park.db");
    CarStorer carStorer("data/park.db");
    OrderStorer orderStorer("data/park.db");

    if (auth.userExists("admin"))
    {
        return;
    }

    auth.addUser("admin", "admin", UserType::ADMIN);
    auth.addUser("login", "password", UserType::DRIVER);
    auth.addUser("ivanov_ivan", "12345", UserType::DRIVER);
    auth.addUser("johnsmith", "qwerty", UserType::DRIVER);
    auth.addUser("petrov_petr", "password", UserType::DRIVER);
    auth.addUser("sidorov_sidr", "word", UserType::DRIVER);
    auth.addUser("smith_john", "1234", UserType::DRIVER);

    Driver driver0(-1, "login", "name", "A", DatabaseHelper::dateToSec(1990, 1, 1), 1990, "Minsk");
    Driver driver1(-1, "ivanov_ivan", "Ivan Ivanov", "A", DatabaseHelper::dateToSec(1990, 1, 1), 1990, "Moscow, Lenina st., 15");
    Driver driver2(-1, "johnsmith", "John Smith", "BE", DatabaseHelper::dateToSec(1990, 1, 1), 1995, "New York, 10th Avenue, 30");
    Driver driver3(-1, "petrov_petr", "Petr Petrov", "C", DatabaseHelper::dateToSec(1990, 1, 1), 1985, "London, Oxford st., 5");
    Driver driver4(-1, "sidorov_sidr", "Sidor Sidorov", "D", DatabaseHelper::dateToSec(1990, 1, 1), 1980, "Paris, Champs-Elysees st., 10");
    Driver driver5(-1, "smith_john", "John Smith", "A", DatabaseHelper::dateToSec(1990, 1, 1), 1990, "Berlin, Alexanderplatz st., 20");

    driverStorer.addDriver(driver0);
    driverStorer.addDriver(driver1);
    driverStorer.addDriver(driver2);
    driverStorer.addDriver(driver3);
    driverStorer.addDriver(driver4);
    driverStorer.addDriver(driver5);

    carStorer.addCar(Car("1234AB-7", "Volvo", "XC90", 2500,10000));
    carStorer.addCar(Car("5678KM-2", "BMW", "X5", 3000, 20000));
    carStorer.addCar(Car("9101HB-3", "Audi", "Q7", 35000, 30000));
    carStorer.addCar(Car("1213PP-4", "Mercedes", "GLE", 4000, 40000));
    carStorer.addCar(Car("1415XO-5", "Toyota", "Land Cruiser", 4500, 50000));

    Order order1(-1, DatabaseHelper::dateToSec(2000, 1, 15), 1, "1234AB-7", 100, 50, 1000);
    Order order2(-1, DatabaseHelper::dateToSec(2000, 2, 15), 1, "5678KM-2", 450, 100, 3500);
    Order order3(-1, DatabaseHelper::dateToSec(2000, 3, 15), 1, "5678KM-2", 100, 75, 300);
    Order order4(-1, DatabaseHelper::dateToSec(2000, 4, 15), 1, "1415XO-5", 500, 100, 4000);

    Order order5(-1, DatabaseHelper::dateToSec(2000, 5, 15), 2, "5678KM-2", 200, 100, 2000);
    Order order6(-1, DatabaseHelper::dateToSec(2000, 6, 15), 2, "9101HB-3", 300, 200, 3000);
    Order order7(-1, DatabaseHelper::dateToSec(2000, 7, 15), 2, "1213PP-4", 400, 500, 4000);

    Order order8(-1, DatabaseHelper::dateToSec(2000, 8, 15), 3, "9101HB-3", 300, 20, 3000);
    Order order9(-1, DatabaseHelper::dateToSec(2000, 9, 15), 3, "1213PP-4", 400, 50, 4000);
    Order order10(-1, DatabaseHelper::dateToSec(2000, 10, 15), 3, "1415XO-5", 500, 30, 5000);

    Order order11(-1, DatabaseHelper::dateToSec(2000, 11, 15), 4, "1213PP-4", 400, 100, 4000);
    Order order12(-1, DatabaseHelper::dateToSec(2000, 12, 15), 4, "1415XO-5", 500, 100, 5000);

    Order order13(-1, DatabaseHelper::dateToSec(2000, 1, 15), 5, "1415XO-5", 500, 100, 5000);

    orderStorer.addOrder(order1);
    orderStorer.addOrder(order2);
    orderStorer.addOrder(order3);
    orderStorer.addOrder(order4);
    orderStorer.addOrder(order5);
    orderStorer.addOrder(order6);
    orderStorer.addOrder(order7);
    orderStorer.addOrder(order8);
    orderStorer.addOrder(order9);
    orderStorer.addOrder(order10);
    orderStorer.addOrder(order11);
    orderStorer.addOrder(order12);
    orderStorer.addOrder(order13);
}

int main()
{
    addTestData();

    MenuInterface menuInterface;
    menuInterface.run();

    return 0;
}
