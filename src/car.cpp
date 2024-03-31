#include "../include/car.h"

Car::Car(const std::string &number, const std::string &brand, int mileage, int carryingCapacity)
{
    setNumber(number);
    setBrand(brand);
    setMileage(mileage);
    setCarryingCapacity(carryingCapacity);
}

Car::Car(sqlite3_stmt *statement)
    : Car(
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 0))),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1))),
          sqlite3_column_int(statement, 2),
          sqlite3_column_int(statement, 3)) {}

std::string Car::getNumber() const
{
    return number;
}

std::string Car::getBrand() const
{
    return brand;
}

int Car::getMileage() const
{
    return mileage;
}

int Car::getCarryingCapacity() const
{
    return carryingCapacity;
}

void Car::setNumber(const std::string &number)
{
    if (Validator::isValidNumberPlate(number))
    {
        this->number = number;
    }
    else
    {
        throw std::invalid_argument("Invalid number plate format.");
    }
}

void Car::setBrand(const std::string &brand)
{
    if (Validator::isValidBrand(brand))
    {
        this->brand = brand;
    }
    else
    {
        throw std::invalid_argument("Invalid brand format.");
    }
}

void Car::setMileage(int mileage)
{
    if (Validator::isValidMileage(mileage))
    {
        this->mileage = mileage;
    }
    else
    {
        throw std::invalid_argument("Invalid mileage value.");
    }
}

void Car::setCarryingCapacity(int carryingCapacity)
{
    if (Validator::isValidCarryingCapacity(carryingCapacity))
    {
        this->carryingCapacity = carryingCapacity;
    }
    else
    {
        throw std::invalid_argument("Invalid carrying capacity value.");
    }
}