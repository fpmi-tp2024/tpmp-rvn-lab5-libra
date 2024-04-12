#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include <climits>
#include "../include/interface.h"

class AdminInterface : public Interface
{
public:
    AdminInterface();

    void run() override;

    ~AdminInterface();

private:
    std::map<int, void (AdminInterface::*)()> commands;

    bool authorize();

    void getTotalOrdersByDriver();
    void getTotalWeightByDriver();
    void getTotalMoneyByDriver();
    void getTotalMileageAndWeightByCar();
    void getOrdersListByDriver();
    void getAllInfoByDriverWithLeastOrders();
    void getMoneyByEachDriver();
    void getAllInfoByCarWithHighestMileage();
    void addDriver();
    void addCar();
    void addOrder();
};

#endif