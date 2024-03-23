#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
private:
    long date;
    int driverId;
    std::string carNumber;
    int mileage;
    int cargoMass;
    int cost;

public:
    Order(long date, int driverId, const std::string& carNumber, int mileage, int cargoMass, int cost);

    long getDate() const;
    int getDriverId() const;
    std::string getCarNumber() const;
    int getMileage() const;
    int getCargoMass() const;
    int getCost() const;
};

#endif // ORDER_H
