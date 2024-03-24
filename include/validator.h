#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <regex>
#include <string>

class Validator
{
public:
    static const std::regex NUMBER_PLATE_REGEX;
    static const std::regex BRAND_REGEX;
    static const std::regex NAME_REGEX;
    static const std::regex LOGIN_REGEX;
    static const std::regex CATEGORY_REGEX;
    static const std::regex ADDRESS_REGEX;

    static bool isValidNumberPlate(const std::string &numberPlate);
    static bool isValidBrand(const std::string &brand);
    static bool isValidName(const std::string &name);
    static bool isValidLogin(const std::string &login);
    static bool isValidCategory(const std::string &category);
    static bool isValidAddress(const std::string &address);
    static bool isValidMileage(int mileage);
    static bool isValidCarryingCapacity(int carryingCapacity);
    static bool isValidCargoMass(int cargoMass);
    static bool isValidCost(int cost);
};

#endif // VALIDATOR_H
