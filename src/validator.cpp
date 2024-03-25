#include "../include/validator.h"

const std::regex Validator::NUMBER_PLATE_REGEX("^[0-9]{4}[A-Z]{2}-[1-7]$");
const std::regex Validator::BRAND_REGEX("^[A-Za-z\\s-]{1,}$");
const std::regex Validator::NAME_REGEX("^[A-Za-z\\s]{1,}$");
const std::regex Validator::LOGIN_REGEX("^[A-Za-z0-9_]{1,}$");
const std::regex Validator::CATEGORY_REGEX("^(?:A|B|C|D|BE|CE|DE)$");
const std::regex Validator::ADDRESS_REGEX("^[A-Za-z0-9\\s,./-]{1,}$");

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
    return mileage >= 0;
}

bool Validator::isValidCarryingCapacity(int carryingCapacity)
{
    return carryingCapacity > 0;
}

bool Validator::isValidCargoMass(int cargoMass)
{
    return cargoMass >= 0;
}

bool Validator::isValidCost(int cost)
{
    return cost > 0;
}
