#include "../include/carstorer.h"
#include<iostream>

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
        "('A123BC','Volvo','XC90',2500,10000),"
        "('B456CD','BMW','X5',3000,20000),"
        "('C789EF','Audi','Q7',35000,30000),"
        "('D012GH','Mercedes','GLE',4000,40000),"
        "('E345IJ','Toyota','Land Cruiser',4500,50000);";

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

