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
    int cargoMass;
    int cost;

public:
    Order(int id, long date, int driverId, const std::string &carNumber, int mileage, int cargoMass, int cost);
    Order(sqlite3_stmt *statement);

    int getId() const;
    long getDate() const;
    int getDriverId() const;
    std::string getCarNumber() const;
    int getMileage() const;
    int getCargoMass() const;
    int getCost() const;

    void setDate(long date);
    void setDriverId(int driverId);
    void setCarNumber(const std::string &carNumber);
    void setMileage(int mileage);
    void setCargoMass(int cargoMass);
    void setCost(int cost);

    std::string toString() const;
};

#endif // ORDER_H
