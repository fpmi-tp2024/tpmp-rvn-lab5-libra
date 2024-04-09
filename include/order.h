#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <sqlite3.h>
#include "validator.h"

class Order
{
private:
    int id;
    long date;
    int driverId;
    std::string carNumber;
    int mileage;
    int cargoWeight;
    int cost;

public:
    Order(int id, long date, int driverId, const std::string &carNumber, int mileage, int cargoWeight, int cost);
    Order(sqlite3_stmt *statement);

    int getId() const;
    long getDate() const;
    int getDriverId() const;
    std::string getCarNumber() const;
    int getMileage() const;
    int getCargoWeight() const;
    int getCost() const;

    void setID(int id);
    void setDate(long date);
    void setDriverId(int driverId);
    void setCarNumber(const std::string &carNumber);
    void setMileage(int mileage);
    void setCargoWeight(int cargoMass);
    void setCost(int cost);

    std::string toString() const;
};

#endif // ORDER_H
