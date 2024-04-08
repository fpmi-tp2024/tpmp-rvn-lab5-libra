#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/validator.h"
#include "../include/carstorer.h"
#include "../include/driverstorer.h"
#include "../include/orderstorer.h"
#include "../config/config.hpp"

TEST_CASE("Validator tests", "[Validator]")
{
    SECTION("isValidNumberPlate")
    {
        REQUIRE(Validator::isValidNumberPlate("1123FD-4"));
        REQUIRE(Validator::isValidNumberPlate("1234AB-7"));
        REQUIRE_FALSE(Validator::isValidNumberPlate("123AB-7"));
        REQUIRE_FALSE(Validator::isValidNumberPlate("1234AB7"));
        REQUIRE_FALSE(Validator::isValidNumberPlate("1234AB-8"));
        REQUIRE_FALSE(Validator::isValidNumberPlate("1234ab-7"));
    }

    SECTION("isValidBrand")
    {
        REQUIRE(Validator::isValidBrand("Toyota"));
        REQUIRE(Validator::isValidBrand("Mercedes-Benz"));
        REQUIRE_FALSE(Validator::isValidBrand("Toyota123"));
        REQUIRE_FALSE(Validator::isValidBrand("123Toyota"));
        REQUIRE_FALSE(Validator::isValidBrand("Toyota@#"));
    }

    SECTION("isValidName")
    {
        REQUIRE(Validator::isValidName("Ivan Ivanov"));
        REQUIRE(Validator::isValidName("John Smith"));
        REQUIRE_FALSE(Validator::isValidName("Ivan1 Ivanov"));
        REQUIRE_FALSE(Validator::isValidName("1Ivan Ivanov"));
        REQUIRE_FALSE(Validator::isValidName("Ivan@# Ivanov"));
    }

    SECTION("isValidLogin")
    {
        REQUIRE(Validator::isValidLogin("Ivanov_Ivan"));
        REQUIRE(Validator::isValidLogin("johnsmith123"));
        REQUIRE_FALSE(Validator::isValidLogin("Ivanov Ivan"));
        REQUIRE_FALSE(Validator::isValidLogin("Ivanov_Ivan@#"));
        REQUIRE_FALSE(Validator::isValidLogin(""));
    }

    SECTION("isValidCategory")
    {
        REQUIRE(Validator::isValidCategory("A"));
        REQUIRE(Validator::isValidCategory("BE"));
        REQUIRE_FALSE(Validator::isValidCategory("AB"));
        REQUIRE_FALSE(Validator::isValidCategory("A1"));
        REQUIRE_FALSE(Validator::isValidCategory(""));
    }

    SECTION("isValidAddress")
    {
        REQUIRE(Validator::isValidAddress("Moscow, Lenina st., 15"));
        REQUIRE(Validator::isValidAddress("New York, 10th Avenue, 30"));
        REQUIRE_FALSE(Validator::isValidAddress("Moscow, Lenina st., 15@#"));
        REQUIRE_FALSE(Validator::isValidAddress("New York, 10th Avenue, 30!"));
        REQUIRE_FALSE(Validator::isValidAddress(""));
    }

    SECTION("isValidMileage")
    {
        int minMileage = Config::getInt("MIN_MILEAGE");
        int maxMileage = Config::getInt("MAX_MILEAGE");

        REQUIRE(Validator::isValidMileage(minMileage + 1));
        REQUIRE(Validator::isValidMileage(maxMileage - 1));
        REQUIRE_FALSE(Validator::isValidMileage(minMileage - 1));
        REQUIRE_FALSE(Validator::isValidMileage(maxMileage + 1));
    }

    SECTION("isValidCarryingCapacity")
    {
        int minCarryingCapacity = Config::getInt("MIN_CARRYING_CAPACITY");
        int maxCarryingCapacity = Config::getInt("MAX_CARRYING_CAPACITY");

        REQUIRE(Validator::isValidCarryingCapacity(minCarryingCapacity + 1));
        REQUIRE(Validator::isValidCarryingCapacity(maxCarryingCapacity - 1));
        REQUIRE_FALSE(Validator::isValidCarryingCapacity(minCarryingCapacity - 1));
        REQUIRE_FALSE(Validator::isValidCarryingCapacity(maxCarryingCapacity + 1));
    }

    SECTION("isValidCargoMass")
    {
        int minCargoMass = Config::getInt("MIN_CARGO_MASS");
        int maxCargoMass = Config::getInt("MAX_CARGO_MASS");

        REQUIRE(Validator::isValidCargoMass(minCargoMass + 1));
        REQUIRE(Validator::isValidCargoMass(maxCargoMass - 1));
        REQUIRE_FALSE(Validator::isValidCargoMass(minCargoMass - 1));
        REQUIRE_FALSE(Validator::isValidCargoMass(maxCargoMass + 1));
    }

    SECTION("isValidCost")
    {
        int minCost = Config::getInt("MIN_COST");
        int maxCost = Config::getInt("MAX_COST");

        REQUIRE(Validator::isValidCost(minCost + 1));
        REQUIRE(Validator::isValidCost(maxCost - 1));
        REQUIRE_FALSE(Validator::isValidCost(minCost - 1));
        REQUIRE_FALSE(Validator::isValidCost(maxCost + 1));
    }
}

TEST_CASE("Make dataset")
{
    CarStorer carStorer("data/test.db");
    DriverStorer driverStorer("data/test.db");
    OrderStorer orderStorer("data/test.db");

    SECTION("Add drivers")
    {
        Driver driver1(-1, "ivanov_ivan", "Ivan Ivanov", "A", 0, 1990, "Moscow, Lenina st., 15");
        Driver driver2(-1, "johnsmith123", "John Smith", "BE", 0, 1995, "New York, 10th Avenue, 30");
        Driver driver3(-1, "petrov_petr", "Petr Petrov", "C", 0, 1985, "London, Oxford st., 5");
        Driver driver4(-1, "sidorov_sidr", "Sidor Sidorov", "D", 0, 1980, "Paris, Champs-Elysees st., 10");
        Driver driver5(-1, "smith_john", "John Smith", "A", 0, 1990, "Berlin, Alexanderplatz st., 20");

        driverStorer.addDriver(driver1, "12345");
        driverStorer.addDriver(driver2, "qwerty");
        driverStorer.addDriver(driver3, "password");
        driverStorer.addDriver(driver4, "word");
        driverStorer.addDriver(driver5, "1234");

        REQUIRE(driver1.getId() == 1);
        REQUIRE(driver2.getId() == 2);
        REQUIRE(driver3.getId() == 3);
        REQUIRE(driver4.getId() == 4);
        REQUIRE(driver5.getId() == 5);
    }

    SECTION("Add cars")
    {
        carStorer.addCar(Car("1234AB-7", "Volvo", "XC90", 2500, 10000));
        carStorer.addCar(Car("5678KM-2", "BMW", "X5", 3000, 20000));
        carStorer.addCar(Car("9101HB-3", "Audi", "Q7", 35000, 30000));
        carStorer.addCar(Car("1213PP-4", "Mercedes", "GLE", 4000, 40000));
        carStorer.addCar(Car("1415XO-5", "Toyota", "Land Cruiser", 4500, 50000));
    }

    SECTION("Add orders")
    {
        Order order1(-1, 0, 1, "1234AB-7", 100, 50, 1000);
        Order order2(-1, 0, 1, "5678KM-2", 450, 100, 3500);
        Order order3(-1, 0, 1, "5678KM-2", 100, 75, 300);
        Order order4(-1, 0, 1, "1415XO-5", 500, 100, 4000);

        Order order5(-1, 0, 2, "5678KM-2", 200, 100, 2000);
        Order order6(-1, 0, 2, "9101HB-3", 300, 200, 3000);
        Order order7(-1, 0, 2, "1213PP-4", 400, 500, 4000);

        Order order8(-1, 0, 3, "9101HB-3", 300, 20, 3000);
        Order order9(-1, 0, 3, "1213PP-4", 400, 50, 4000);
        Order order10(-1, 0, 3, "1415XO-5", 500, 30, 5000);

        Order order11(-1, 0, 4, "1213PP-4", 400, 100, 4000);
        Order order12(-1, 0, 4, "1415XO-5", 500, 100, 5000);

        Order order13(-1, 0, 5, "1415XO-5", 500, 100, 5000);

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

        REQUIRE(order1.getId() == 1);
        REQUIRE(order2.getId() == 2);
        REQUIRE(order3.getId() == 3);
        REQUIRE(order4.getId() == 4);
        REQUIRE(order5.getId() == 5);
        REQUIRE(order6.getId() == 6);
        REQUIRE(order7.getId() == 7);
        REQUIRE(order8.getId() == 8);
        REQUIRE(order9.getId() == 9);
        REQUIRE(order10.getId() == 10);
        REQUIRE(order11.getId() == 11);
        REQUIRE(order12.getId() == 12);
        REQUIRE(order13.getId() == 13);
    }
}

TEST_CASE("CarStorer")
{
    CarStorer carStorer("data/test.db");

    // SECTION("getCarTotalMileageAndMass")
    // {
    //     std::pair<int, int> result = carStorer.getCarTotalMileageAndMass("1234AB-7");
    //     REQUIRE(result.first == 49000);
    //     REQUIRE(result.second == 150000);
    // }

    // SECTION("getCarWithMaximumMileage")
    // {
    //     Car result = carStorer.getCarWithMaximumMileage();
    //     REQUIRE(result.getNumber() == "9101HB-3");
    //     REQUIRE(result.getBrand() == "Audi");
    //     REQUIRE(result.getModel() == "Q7");
    //     REQUIRE(result.getMileage() == 35000);
    //     REQUIRE(result.getCarryingCapacity() == 30000);
    // }

    SECTION("getAllCars")
    {
        std::vector<Car> result = carStorer.getAllCars();
        REQUIRE(result.size() == 5);

        REQUIRE(result[0].getNumber() == "1234AB-7");
        REQUIRE(result[0].getBrand() == "Volvo");
        REQUIRE(result[0].getModel() == "XC90");
        REQUIRE(result[0].getCarryingCapacity() == 2500);
        REQUIRE(result[0].getPurchaseMileage() == 10000);

        REQUIRE(result[1].getNumber() == "5678KM-2");
        REQUIRE(result[1].getBrand() == "BMW");
        REQUIRE(result[1].getModel() == "X5");
        REQUIRE(result[1].getCarryingCapacity() == 3000);
        REQUIRE(result[1].getPurchaseMileage() == 20000);

        REQUIRE(result[2].getNumber() == "9101HB-3");
        REQUIRE(result[2].getBrand() == "Audi");
        REQUIRE(result[2].getModel() == "Q7");
        REQUIRE(result[2].getCarryingCapacity() == 35000);
        REQUIRE(result[2].getPurchaseMileage() == 30000);

        REQUIRE(result[3].getNumber() == "1213PP-4");
        REQUIRE(result[3].getBrand() == "Mercedes");
        REQUIRE(result[3].getModel() == "GLE");
        REQUIRE(result[3].getCarryingCapacity() == 4000);
        REQUIRE(result[3].getPurchaseMileage() == 40000);

        REQUIRE(result[4].getNumber() == "1415XO-5");
        REQUIRE(result[4].getBrand() == "Toyota");
        REQUIRE(result[4].getModel() == "Land Cruiser");
        REQUIRE(result[4].getCarryingCapacity() == 4500);
        REQUIRE(result[4].getPurchaseMileage() == 50000);
    }

    // SECTION("updateCar")
    // {
    //     carStorer.updateCar("1234AB-7", Car("1234AB-7", "Volvo", "XC90", 2500, 11000));

    //     Car result = carStorer.getCarWithMaximumMileage();
    //     REQUIRE(result.getNumber() == "1234AB-7");
    //     REQUIRE(result.getBrand() == "Volvo");
    //     REQUIRE(result.getModel() == "XC90");
    //     REQUIRE(result.getCarryingCapacity() == 2500);
    //     REQUIRE(result.getMileage() == 11000);
    // }

    SECTION("removeCar")
    {
        carStorer.removeCar("1234AB-7");

        std::vector<Car> result = carStorer.getAllCars();
        REQUIRE(result.size() == 4);

        REQUIRE(result[0].getNumber() == "5678KM-2");
        REQUIRE(result[0].getBrand() == "BMW");
        REQUIRE(result[0].getModel() == "X5");
        REQUIRE(result[0].getCarryingCapacity() == 3000);
        REQUIRE(result[0].getPurchaseMileage() == 20000);

        REQUIRE(result[1].getNumber() == "9101HB-3");
        REQUIRE(result[1].getBrand() == "Audi");
        REQUIRE(result[1].getModel() == "Q7");
        REQUIRE(result[1].getCarryingCapacity() == 35000);
        REQUIRE(result[1].getPurchaseMileage() == 30000);

        REQUIRE(result[2].getNumber() == "1213PP-4");
        REQUIRE(result[2].getBrand() == "Mercedes");
        REQUIRE(result[2].getModel() == "GLE");
        REQUIRE(result[2].getCarryingCapacity() == 4000);
        REQUIRE(result[2].getPurchaseMileage() == 40000);

        REQUIRE(result[3].getNumber() == "1415XO-5");
        REQUIRE(result[3].getBrand() == "Toyota");
        REQUIRE(result[3].getModel() == "Land Cruiser");
        REQUIRE(result[3].getCarryingCapacity() == 4500);
        REQUIRE(result[3].getPurchaseMileage() == 50000);
    }
}