#include "../include/validator.h"

const std::regex Validator::NUMBER_PLATE_REGEX(Config::getString("NUMBER_PLATE_REGEX"));
const std::regex Validator::BRAND_REGEX(Config::getString("BRAND_REGEX"));
const std::regex Validator::NAME_REGEX(Config::getString("NAME_REGEX"));
const std::regex Validator::LOGIN_REGEX(Config::getString("LOGIN_REGEX"));
const std::regex Validator::CATEGORY_REGEX(Config::getString("CATEGORY_REGEX"));
const std::regex Validator::ADDRESS_REGEX(Config::getString("ADDRESS_REGEX"));

bool Validator::isValidNumberPlate(const std::string &numberPlate)
{
    return std::regex_match(numberPlate, NUMBER_PLATE_REGEX);
}

bool Validator::isValidBrand(const std::string &brand)
{
    return std::regex_match(brand, BRAND_REGEX);
}

bool Validator::isValidName(const std::string &name)
{
    return std::regex_match(name, NAME_REGEX);
}

bool Validator::isValidLogin(const std::string &login)
{
    return std::regex_match(login, LOGIN_REGEX);
}

bool Validator::isValidCategory(const std::string &category)
{
    return std::regex_match(category, CATEGORY_REGEX);
}

bool Validator::isValidAddress(const std::string &address)
{
    return std::regex_match(address, ADDRESS_REGEX);
}

bool Validator::isValidMileage(int mileage)
{
    return mileage >= Config::getInt("MIN_MILEAGE") && mileage <= Config::getInt("MAX_MILEAGE");
}

bool Validator::isValidCarryingCapacity(int carryingCapacity)
{
    return carryingCapacity >= Config::getInt("MIN_CARRYING_CAPACITY") && carryingCapacity <= Config::getInt("MAX_CARRYING_CAPACITY");
}

bool Validator::isValidCargoMass(int cargoMass)
{
    return cargoMass >= Config::getInt("MIN_CARGO_MASS") && cargoMass <= Config::getInt("MAX_CARGO_MASS");
}

bool Validator::isValidCost(int cost)
{
    return cost >= Config::getInt("MIN_COST") && cost <= Config::getInt("MAX_COST");
}