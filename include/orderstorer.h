#ifndef ORDERSTORER_H
#define ORDERSTORER_H

#include <string>
#include <sqlite3.h>
#include "order.h"
#include "databaseHelper.h"

class OrderStorer
{
private:
    sqlite3 *db;

public:
    OrderStorer(const std::string &dbName);

    // TODO : различный get
    int getTotalNumberOfOrders(const int driverID);
    int getTotalCargoMass(const int driverID);
    // Получить общую сумму денег, заработанную водителем за определенный период
    int getTotalMoney(const int driverID,long start = -1,long end = -1);

    // Добавить новый заказ
    void addOrder(const Order &order);

    // Удалить заказ
    void removeOrder(int orderId);

    ~OrderStorer();
};

#endif //  ORDERSTORER_H