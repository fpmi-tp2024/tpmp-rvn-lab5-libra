#include "../include/car.h"

Car::Car(const std::string &number, const std::string &brand, int mileage, int carryingCapacity)
    : number(number), brand(brand), mileage(mileage), carryingCapacity(carryingCapacity) {}

Car::Car(sqlite3_stmt *statement)
{
    number = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 0)));
    brand = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1)));
    mileage = sqlite3_column_int(statement, 2);
    carryingCapacity = sqlite3_column_int(statement, 3);
}

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
