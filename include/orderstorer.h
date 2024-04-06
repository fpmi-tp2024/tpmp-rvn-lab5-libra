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

    // Получить общее количество поездок, общую массу перевезенных грузов и сумму заработанных денег для указанного водителя
    std::tuple<int, int, int> getDriverTotalTripsAndMassAndMoney(int driverId);

    // Обновить информацию о заказе
    void updateOrder(int orderId, const Order &order);

    // Добавить новый заказ
    void addOrder(const Order &order);

    // Удалить заказ
    void removeOrder(int orderId);
    void removeOrder(const Order &order);
};

#endif //  ORDERSTORER_H