#include "../include/carstorer.h"
#include<iostream>
#include<string>

CarStorer::CarStorer(const std::string& dbName)
{
    char* err_msg = nullptr;

    // Открываем базу данных 
    int result = sqlite3_open(dbName.c_str(), &this->db);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        throw std::runtime_error("Can't open database,try to restart application " + std::string(sqlite3_errmsg(db)));
    }

    const char* SQLQuery =
        "CREATE TABLE IF NOT EXISTS Cars ("
        "number varchar(10) NOT NULL PRIMARY KEY,"
        "brand varchar(15) NOT NULL,"
        "model varchar(15) NOT NULL,"
        "capacity integer NOT NULL,"
        "purchase_mileage integer NOT NULL"
        ");";

    // Создаем таблицу Cars
    result = sqlite3_exec(this->db, SQLQuery, 0, 0, &err_msg);
    if (result != SQLITE_OK) {
        std::string error_message = "Can't create table Cars: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    SQLQuery =
        "INSERT INTO Cars(number,brand,model,capacity,purchase_mileage)"
        "VALUES"
        "('1234AB-7','Volvo','XC90',2500,10000),"
        "('5678KM-2','BMW','X5',3000,20000),"
        "('9101HB-3','Audi','Q7',35000,30000),"
        "('1213PP-4','Mercedes','GLE',4000,40000),"
        "('1415XO-5','Toyota','Land Cruiser',4500,50000);";

    // Заполняем таблицу Cars первоначальными данными
    if(DatabaseHelper::isTableEmpty(this->db, "Cars")) {
        result = sqlite3_exec(this->db, SQLQuery, 0, 0, &err_msg);
        if (result != SQLITE_OK) {
            std::string error_message = "Can't insert data into Cars: " + std::string(err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            throw std::runtime_error(error_message);
        }
    }


}

std::pair <int, int> CarStorer::getCarTotalMileageAndMass(std::string carNumber)
{
    std::pair <int, int> result;
    char* err_msg = nullptr;
    std::string SQLQuery = "SELECT SUM(kilometrage), SUM(cargo_weight) FROM Orders WHERE car_number = '" + carNumber + "';";

    int resultSQL = sqlite3_exec(this->db, SQLQuery.c_str(), &CarStorer::callbackForTotalMileageAndMass, &result, &err_msg);
    if (resultSQL != SQLITE_OK) {
        std::string error_message = "Can't get car total kilometrage and cargo_weight: " + std::string(err_msg);
        sqlite3_free(err_msg);
        throw std::runtime_error(error_message);
    }   

    return result;                  
}

int CarStorer::callbackForTotalMileageAndMass(void* data, int colCount, char** columns, char** colNames)
{
    auto result = static_cast<std::pair<int, int>*>(data);
    // Первоначально задаем пару {0,0}, которая будет возращаться, если на машине не выполнялись заказы
    result->first = 0;
    result->second = 0;
    if (columns[0]!=nullptr && columns[1]!=nullptr){
        result->first = std::stoi(columns[0]);
        result->second = std::stoi(columns[1]);
    }
    return 0;
}

Car CarStorer::getCarWithMaximumMileage()
{
    Car result = Car();
    std::string SQLQuery =
        "SELECT number,brand,model,capacity,purchase_mileage FROM Cars "
        "WHERE number = (SELECT car_number FROM Orders "
        "GROUP BY car_number "
        "ORDER BY SUM(kilometrage) DESC "
        "LIMIT 1);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = Car(stmt); 
        }
    } else {
        std::string error_message = "Can't get car with maximum mileage: " + std::string(sqlite3_errmsg(this->db));
        throw std::runtime_error(error_message);
    }

    sqlite3_finalize(stmt);

    return result;
}

void CarStorer::updateCar(std::string carNumber,const Car& car){
    std::string SQLQuery =
        "UPDATE Cars SET brand = '" + car.getBrand() + "',"
        "model='" + car.getModel() + "',capacity='" + std::to_string(car.getCarryingCapacity()) +"',"
        "purchase_mileage='" + std::to_string(car.getMileage()) + "'WHERE number='" + carNumber +"';";

    char* err_msg = nullptr;

    int result = sqlite3_exec(db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK )
    {
        std::string error_message = "Cannot update data in Cars: " + std::string(err_msg);
        sqlite3_free(err_msg);
        throw std::runtime_error(error_message);
    }
}

void CarStorer::addCar(const Car& car){
    std::string SQLQuery =
        "INSERT INTO Cars(number,brand,model,capacity,purchase_mileage)"
        "VALUES('" + car.getNumber() + "','" + car.getBrand() + "','" + car.getModel() + "',"
        + std::to_string(car.getCarryingCapacity()) + "," + std::to_string(car.getMileage()) + ");";

    char* err_msg = nullptr;

    int result = sqlite3_exec(db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK )
    {
        std::string error_message = "Cannot insert data into Cars: " + std::string(err_msg);
        sqlite3_free(err_msg);
        throw std::runtime_error(error_message);
    }
}

void CarStorer::removeCar(std::string carNumber)
{
    std::string SQLQuery = "DELETE FROM Cars WHERE number = '" + carNumber + "';";

    char* err_msg = nullptr;

    int result = sqlite3_exec(db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK )   
    {
        std::string error_message = "Cannot delete data from Cars: " + std::string(err_msg);
        sqlite3_free(err_msg);
        throw std::runtime_error(error_message);
    }
}