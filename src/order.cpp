#include "../include/order.h"

Order::Order(long date, int driverId, const std::string &carNumber, int mileage, int cargoMass, int cost)
    : date(date), driverId(driverId), carNumber(carNumber), mileage(mileage), cargoMass(cargoMass),
      cost(cost) {}

long Order::getDate() const
{
    return date;
}

int Order::getDriverId() const
{
    return driverId;
}

std::string Order::getCarNumber() const
{
    return carNumber;
}

int Order::getMileage() const
{
    return mileage;
}

int Order::getCargoMass() const
{
    return cargoMass;
}

int Order::getCost() const
{
    return cost;
}
