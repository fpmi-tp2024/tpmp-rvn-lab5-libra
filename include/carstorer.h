#ifndef CARSTORER_H
#define CARSTORER_H

#include <string>
#include <sqlite3.h>
#include "car.h"

class CarStorer
{
private:
    sqlite3 *db;

public:
    CarStorer(std::string dbName);

    // TODO : различный get

    // Получить общий пробег и общую массу перевезенных грузов для указанной машины
    std::pair<int, int> getCarTotalMileageAndMass(int carId);

    // Получить все сведения о машине с наибольшим общим пробегом
    Car getCarWithMaximumMileage();

    // Обновить информацию о машине
    void updateCar(int carId, const Car &car);

    // Добавить новую машину
    void addCar(const Car &car);

    // Удалить машину
    void removeCar(int carId);
    void removeCar(const Car &car);
};

#endif // CARSTORER_H