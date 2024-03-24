#ifndef CAR_H
#define CAR_H

#include <string>
#include <sqlite3.h>

class Car
{
private:
    std::string number;
    std::string brand;
    int mileage;
    int carryingCapacity;

public:
    Car(const std::string &number, const std::string &brand, int mileage, int carryingCapacity);
    Car(sqlite3_stmt *statement);

    std::string getNumber() const;
    std::string getBrand() const;
    int getMileage() const;
    int getCarryingCapacity() const;
};

#endif // CAR_H
