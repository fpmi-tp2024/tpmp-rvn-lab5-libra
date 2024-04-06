#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/validator.h"

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