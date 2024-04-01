#ifndef CAR_H
#define CAR_H

#include <string>
#include <sqlite3.h>
#include "validator.h"

class Car
{
private:
    std::string number;
    std::string brand;
    std::string model;
    int mileage;
    int carryingCapacity;

public:
    Car(const std::string &number, const std::string &brand, int mileage, int carryingCapacity);
    Car(sqlite3_stmt *statement);

    std::string getNumber() const;
    std::string getBrand() const;
    int getMileage() const;
    int getCarryingCapacity() const;

    void setNumber(const std::string &number);
    void setBrand(const std::string &brand);
    void setMileage(int mileage);
    void setCarryingCapacity(int carryingCapacity);
};

#endif // CAR_H
