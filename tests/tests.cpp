#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/park.h"
#include "../include/validator.h"

TEST_CASE("sum")
{
    REQUIRE(sum(1, 2) == 3);
    REQUIRE(sum(2, 3) == 5);
    REQUIRE(sum(3, 4) == 7);
}

TEST_CASE("Validator tests", "[Validator]")
{
    SECTION("isValidNumberPlate")
    {
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
        REQUIRE(Validator::isValidMileage(10000));
        REQUIRE(Validator::isValidMileage(0));
        REQUIRE_FALSE(Validator::isValidMileage(-1));
    }

    SECTION("isValidCarryingCapacity")
    {
        REQUIRE(Validator::isValidCarryingCapacity(1500));
        REQUIRE_FALSE(Validator::isValidCarryingCapacity(0));
        REQUIRE_FALSE(Validator::isValidCarryingCapacity(-1));
    }

    SECTION("isValidCargoMass")
    {
        REQUIRE(Validator::isValidCargoMass(1000));
        REQUIRE(Validator::isValidCargoMass(0));
        REQUIRE_FALSE(Validator::isValidCargoMass(-1));
    }

    SECTION("isValidCost")
    {
        REQUIRE(Validator::isValidCost(10000));
        REQUIRE_FALSE(Validator::isValidCost(0));
        REQUIRE_FALSE(Validator::isValidCost(-1));
    }
}