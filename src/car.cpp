#include "../include/car.h"

Car::Car(const std::string &number, const std::string &brand, int mileage, int carryingCapacity)
    : number(number), brand(brand), mileage(mileage), carryingCapacity(carryingCapacity) {}

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
