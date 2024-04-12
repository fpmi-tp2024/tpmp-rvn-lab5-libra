#ifndef DRIVERSTORER_H
#define DRIVERSTORER_H

#include <string>
#include <sqlite3.h>
#include <vector>
#include "order.h"
#include "driver.h"
#include "../include/databaseHelper.h"

class DriverStorer
{
private:
    sqlite3 *db;

public:
    DriverStorer(const std::string &dbName);

    // Получить водителя по его ID
    Driver getDriverById(const int driverId);

    // Получить водителя по его логину
    Driver getDriverByLogin(const std::string &login);

    // Получить перечень выполненных заказов водителем за указанный период
    std::vector<Order> getOrdersByDriverAndPeriod(int driverId, long startDate = -1, long endDate = -1);

    // Получить все сведения о водителе, выполнившем наименьшее количество поездок, и количество полученных денег
    std::pair<Driver, double> getDriverWithMinimumTripsAndMoney();

    // Получить всех водителей
    std::vector<Driver> getDrivers();

    // Обновить адрес водителя
    void updateAddress(int driverId, const std::string &address);

    // Добавить нового водителя
    void addDriver(Driver &driver);

    // Удалить водителя
    void removeDriver(int driverId);

    ~DriverStorer();
};

#endif // DRIVERSTORER_H