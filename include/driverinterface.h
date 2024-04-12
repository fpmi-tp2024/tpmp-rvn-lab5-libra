#ifndef DRIVERINTERFACE_H
#define DRIVERINTERFACE_H

#include "../include/interface.h"

class DriverInterface : public Interface
{
public:
    DriverInterface();

    void run() override;

    ~DriverInterface();

private:
    std::map<int, void (DriverInterface::*)()> commands;
    Driver *driver;

    bool authorize();

    void getListOfCompletedOrdersByTime();
    void getTotalOrdersCount();
    void getTotalWeightOfTransportedGoods();
    void getMoneyEarnedByTime();
    void getMoneyEarned();
    void changeAddress();
    void changeLogin();
    void changePassword();
};

#endif