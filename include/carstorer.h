#ifndef CARSTORER_H
#define CARSTORER_H

#include <string>
#include <sqlite3.h>
#include "car.h"
#include "databaseHelper.h"
#include <vector>

class CarStorer
{
private:
    sqlite3 *db;

    static int callbackForTotalMileageAndMass(void *, int, char **, char **);

    static int callbackForMaxMileage(void *, int, char **, char **);

public:
    CarStorer(const std::string &dbName);

    // Получить машину по ее номеру
    Car getCarByNumber(std::string carNumber);

    // Получить общий пробег и общую массу перевезенных грузов для указанной машины
    std::pair<int, int> getCarTotalMileageAndMass(std::string carNumber);

    // Получить все сведения о машине с наибольшим общим пробегом
    Car getCarWithMaximumMileage();

    // Получить все машины
    std::vector<Car> getAllCars();

    // Обновить информацию о машине
    void updateCar(std::string carNumber, const Car &car);

    // Добавить новую машину
    void addCar(const Car &car);

    // Удалить машину
    void removeCar(std::string carNumber);

    ~CarStorer();
};

#endif // CARSTORER_H