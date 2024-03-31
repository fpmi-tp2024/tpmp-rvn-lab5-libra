#ifndef DRIVERSTORER_H
#define DRIVERSTORER_H

#include <string>
#include <sqlite3.h>
#include <vector>
#include "order.h"
#include "driver.h"

class DriverStorer
{
private:
    sqlite3 *db;

public:
    DriverStorer(std::string dbName);

    // TODO : различный get

    // Получить перечень выполненных заказов водителем за указанный период
    std::vector<Order> getOrdersByDriverAndPeriod(int driverId, long startDate, long endDate);

    // Получить все сведения о водителе, выполнившем наименьшее количество поездок, и количество полученных денег
    Driver getDriverWithMinimumTrips();

    // Обновить информацию о водителе
    void updateDriver(int driverId, const Driver &driver);

    // Добавить нового водителя
    void addDriver(const Driver &driver);

    // Удалить водителя
    void removeDriver(int driverId);
    void removeDriver(const Driver &driver);
};

#endif // DRIVERSTORER_H