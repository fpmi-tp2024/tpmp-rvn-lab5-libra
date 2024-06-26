#include "../include/car.h"
#include <iostream>

Car::Car() : number(""), brand(""), model(""), purchaseMileage(0), carryingCapacity(0) {}

Car::Car(const std::string &number, const std::string &brand, const std::string &model, int carryingCapacity, int mileage)
{
    setNumber(number);
    setBrand(brand);
    setModel(model);
    setCarryingCapacity(carryingCapacity);
    setMileage(mileage);
}

Car::Car(sqlite3_stmt *statement)
    : Car(
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 0))),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1))),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 2))),
          sqlite3_column_int(statement, 3),
          sqlite3_column_int(statement, 4))
{
}

std::string Car::getNumber() const
{
    return number;
}

std::string Car::getBrand() const
{
    return brand;
}

std::string Car::getModel() const
{
    return model;
}

int Car::getPurchaseMileage() const
{
    return purchaseMileage;
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

void Car::setMileage(int purchaseMileage)
{
    if (Validator::isValidMileage(purchaseMileage))
    {
        this->purchaseMileage = purchaseMileage;
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

void Car::setModel(const std::string &model)
{
    this->model = model;
}

std::string Car::toString() const
{
    std::stringstream ss;
    ss << "||\tNumber: " << number << std::endl;
    ss << "||\tBrand: " << brand << std::endl;
    ss << "||\tModel: " << model << std::endl;
    ss << "||\tPurchase mileage: " << purchaseMileage << std::endl;
    ss << "||\tCarrying capacity: " << carryingCapacity << std::endl;
    return ss.str();
}