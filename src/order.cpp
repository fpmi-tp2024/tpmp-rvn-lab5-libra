#include "../include/order.h"

Order::Order(int id, long date, int driverId, const std::string &carNumber, int mileage, int cargoWeight, int cost)
    : id(id)
{
    setDate(date);
    setDriverId(driverId);
    setCarNumber(carNumber);
    setMileage(mileage);
    setCargoWeight(cargoWeight);
    setCost(cost);
}

Order::Order(sqlite3_stmt *statement)
{
    date = sqlite3_column_int64(statement, 0);
    driverId = sqlite3_column_int(statement, 1);
    carNumber = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 2)));
    mileage = sqlite3_column_int(statement, 3);
    cargoWeight = sqlite3_column_int(statement, 4);
    cost = sqlite3_column_int(statement, 5);
}

int Order::getId() const
{
    return id;
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

int Order::getCargoWeight() const
{
    return cargoWeight;
}

int Order::getCost() const
{
    return cost;
}

void Order::setDate(long date)
{
    this->date = date;
}

void Order::setDriverId(int driverId)
{
    this->driverId = driverId;
}

void Order::setID(int id)
{
    if (this->id != -1){
        throw std::invalid_argument("Invalid id value.");
    }
    this->id = id;
}

void Order::setCarNumber(const std::string &carNumber)
{
    if (Validator::isValidNumberPlate(carNumber))
    {
        this->carNumber = carNumber;
    }
    else
    {
        throw std::invalid_argument("Invalid car number plate format.");
    }
}

void Order::setMileage(int mileage)
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

void Order::setCargoWeight(int cargoWeight)
{
    if (Validator::isValidCargoMass(cargoWeight))
    {
        this->cargoWeight = cargoWeight;
    }
    else
    {
        throw std::invalid_argument("Invalid cargo mass value.");
    }
}

void Order::setCost(int cost)
{
    if (Validator::isValidCost(cost))
    {
        this->cost = cost;
    }
    else
    {
        throw std::invalid_argument("Invalid cost value.");
    }
}

std::string Order::toString() const
{
    std::stringstream ss;
    ss << "||\tOrder ID: " << id << std::endl;
    ss << "||\tDate: " << date << std::endl;
    ss << "||\tDriver ID: " << driverId << std::endl;
    ss << "||\tCar number: " << carNumber << std::endl;
    ss << "||\tMileage: " << mileage << std::endl;
    ss << "||\tCargo weight: " << cargoWeight << std::endl;
    ss << "||\tCost: " << cost << std::endl;
    return ss.str();
}