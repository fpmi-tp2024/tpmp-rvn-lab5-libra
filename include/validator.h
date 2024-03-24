#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <regex>
#include <string>
#include <stdexcept>

class Validator
{
public:
    static const std::regex NUMBER_PLATE_REGEX;
    static const std::regex BRAND_REGEX;
    static const std::regex NAME_REGEX;
    static const std::regex LOGIN_REGEX;
    static const std::regex CATEGORY_REGEX;
    static const std::regex ADDRESS_REGEX;

    static void validateNumberPlate(const std::string &numberPlate);
    static void validateBrand(const std::string &brand);
    static void validateName(const std::string &name);
    static void validateLogin(const std::string &login);
    static void validateCategory(const std::string &category);
    static void validateAddress(const std::string &address);
    static void validateMileage(int mileage);
    static void validateCarryingCapacity(int carryingCapacity);
    static void validateCargoMass(int cargoMass);
    static void validateCost(int cost);
};

#endif // VALIDATOR_H
