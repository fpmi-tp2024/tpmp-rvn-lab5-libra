#include "Validator.h"

const std::regex Validator::NUMBER_PLATE_REGEX("^[0-9]{4}[A-Z]{2}-[1-7]$");
const std::regex Validator::BRAND_REGEX("^[A-Za-z\\s]{1,}$");
const std::regex Validator::NAME_REGEX("^[A-Za-z\\s]{1,}$");
const std::regex Validator::LOGIN_REGEX("^[A-Za-z0-9_]{1,}$");
const std::regex Validator::CATEGORY_REGEX("^(?:A|B|C|D|BE|CE|DE)$");
const std::regex Validator::ADDRESS_REGEX("^[A-Za-z0-9\\s,./-]{1,}$");

void Validator::validateNumberPlate(const std::string &numberPlate)
{
    if (!std::regex_match(numberPlate, NUMBER_PLATE_REGEX))
    {
        throw std::invalid_argument("Invalid number plate format");
    }
}

void Validator::validateBrand(const std::string &brand)
{
    if (!std::regex_match(brand, BRAND_REGEX))
    {
        throw std::invalid_argument("Invalid brand format");
    }
}

void Validator::validateName(const std::string &name)
{
    if (!std::regex_match(name, NAME_REGEX))
    {
        throw std::invalid_argument("Invalid name format");
    }
}

void Validator::validateLogin(const std::string &login)
{
    if (!std::regex_match(login, LOGIN_REGEX))
    {
        throw std::invalid_argument("Invalid login format");
    }
}

void Validator::validateCategory(const std::string &category)
{
    if (!std::regex_match(category, CATEGORY_REGEX))
    {
        throw std::invalid_argument("Invalid category format");
    }
}

void Validator::validateAddress(const std::string &address)
{
    if (!std::regex_match(address, ADDRESS_REGEX))
    {
        throw std::invalid_argument("Invalid address format");
    }
}

void Validator::validateMileage(int mileage)
{
    if (mileage < 0)
    {
        throw std::invalid_argument("Invalid mileage value");
    }
}

void Validator::validateCarryingCapacity(int carryingCapacity)
{
    if (carryingCapacity < 0)
    {
        throw std::invalid_argument("Invalid carrying capacity value");
    }
}

void Validator::validateCargoMass(int cargoMass)
{
    if (cargoMass < 0)
    {
        throw std::invalid_argument("Invalid cargo mass value");
    }
}

void Validator::validateCost(int cost)
{
    if (cost < 0)
    {
        throw std::invalid_argument("Invalid cost value");
    }
}
