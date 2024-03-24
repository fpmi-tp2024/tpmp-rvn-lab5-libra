#include "../include/order.h"

Order::Order(long date, int driverId, const std::string &carNumber, int mileage, int cargoMass, int cost)
    : date(date), driverId(driverId), carNumber(carNumber), mileage(mileage), cargoMass(cargoMass),
      cost(cost) {}

Order::Order(sqlite3_stmt *statement)
{
    date = sqlite3_column_int64(statement, 0);
    driverId = sqlite3_column_int(statement, 1);
    carNumber = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 2)));
    mileage = sqlite3_column_int(statement, 3);
    cargoMass = sqlite3_column_int(statement, 4);
    cost = sqlite3_column_int(statement, 5);
}

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
