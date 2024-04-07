#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/validator.h"
#include "../include/carstorer.h"
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

TEST_CASE("CarStorer")
{
    CarStorer carStorer("data/test.db");

    SECTION("Init")
    {
        carStorer.addCar(Car("1234AB-7", "Volvo", "XC90", 2500, 10000));
        carStorer.addCar(Car("5678KM-2", "BMW", "X5", 3000, 20000));
        carStorer.addCar(Car("9101HB-3", "Audi", "Q7", 35000, 30000));
        carStorer.addCar(Car("1213PP-4", "Mercedes", "GLE", 4000, 40000));
        carStorer.addCar(Car("1415XO-5", "Toyota", "Land Cruiser", 4500, 50000));
    }

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
        REQUIRE(result[0].getMileage() == 10000);

        REQUIRE(result[1].getNumber() == "5678KM-2");
        REQUIRE(result[1].getBrand() == "BMW");
        REQUIRE(result[1].getModel() == "X5");
        REQUIRE(result[1].getCarryingCapacity() == 3000);
        REQUIRE(result[1].getMileage() == 20000);

        REQUIRE(result[2].getNumber() == "9101HB-3");
        REQUIRE(result[2].getBrand() == "Audi");
        REQUIRE(result[2].getModel() == "Q7");
        REQUIRE(result[2].getCarryingCapacity() == 35000);
        REQUIRE(result[2].getMileage() == 30000);

        REQUIRE(result[3].getNumber() == "1213PP-4");
        REQUIRE(result[3].getBrand() == "Mercedes");
        REQUIRE(result[3].getModel() == "GLE");
        REQUIRE(result[3].getCarryingCapacity() == 4000);
        REQUIRE(result[3].getMileage() == 40000);

        REQUIRE(result[4].getNumber() == "1415XO-5");
        REQUIRE(result[4].getBrand() == "Toyota");
        REQUIRE(result[4].getModel() == "Land Cruiser");
        REQUIRE(result[4].getCarryingCapacity() == 4500);
        REQUIRE(result[4].getMileage() == 50000);
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
        REQUIRE(result[0].getMileage() == 20000);

        REQUIRE(result[1].getNumber() == "9101HB-3");
        REQUIRE(result[1].getBrand() == "Audi");
        REQUIRE(result[1].getModel() == "Q7");
        REQUIRE(result[1].getCarryingCapacity() == 35000);
        REQUIRE(result[1].getMileage() == 30000);

        REQUIRE(result[2].getNumber() == "1213PP-4");
        REQUIRE(result[2].getBrand() == "Mercedes");
        REQUIRE(result[2].getModel() == "GLE");
        REQUIRE(result[2].getCarryingCapacity() == 4000);
        REQUIRE(result[2].getMileage() == 40000);

        REQUIRE(result[3].getNumber() == "1415XO-5");
        REQUIRE(result[3].getBrand() == "Toyota");
        REQUIRE(result[3].getModel() == "Land Cruiser");
        REQUIRE(result[3].getCarryingCapacity() == 4500);
        REQUIRE(result[3].getMileage() == 50000);
    }
}